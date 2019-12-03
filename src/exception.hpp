#include <exception>
#include <string>

#ifndef  _EXCEPTION_H
#define  _EXCEPTION_H 1


class GeneralException : public std::exception
{
private:
    
    unsigned    line;
    std::string filename;
    std::string description;

public:

    GeneralException(const char *errDescription,
                     const char *srcFilename,
                     unsigned    srcLine
                     )
    {
        line        = srcLine;
        filename    = srcFilename;
        description = errDescription;
        
    }
    
    virtual
    ~GeneralException()
    {
    
    }
    
    virtual
    const char *
    what() const throw()
    {
        char *errMessage = new char[filename.size() + description.size() + 50];
        sprintf(errMessage, "%s:%u: %s", filename.c_str(),
                line, description.c_str()
                );
        return errMessage;
    }
    
};

#endif /*_EXCEPTION_H*/