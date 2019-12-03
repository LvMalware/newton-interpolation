/*
 * newton.hpp - Newton's Interpolating Polynomial
 *
 * Copyright (C) 2019 Lucas V. Araujo <lucas.vieira.ar@disroot.org> .
 *
 * This is free software: you are free to change and redistribute it under the
 * terms of GNU GPL license version 3 or, at your choice, any later version.
 * You should have received a copy of the license along with this software. If
 * not, you can read the full text at https://gnu.org/licenses/gpl.html.
 * This software is offered AS IT IS, in hope that it will be usefull, but there
 * is NO WARRANTY, to the extent permitted by law.
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>

#include "exception.hpp"

#ifndef  _NEWTON_HPP
#define  _NEWTON_HPP

template <typename numericType>
class NewtonInterpolator
{
private:

    /*  The struct point will hold the coordinates of known points */
    struct point
    {
        numericType x;
        numericType y;
    };

    std::vector<point>       data;
    std::vector<numericType> differences;

public:

    NewtonInterpolator()
    {

    }

    ~NewtonInterpolator()
    {

    }

    void
    loadData(const char *filename)
    {
        /*
         * Loads the data from a file given his name.
         * The file must contain only numeric data, where each ordered pair
         * (x, y), need to be separated by spacing.
         */

        std::ifstream file;
        /* Opens the file in read-only mode. */
        file.open(filename, std::ios_base::in);
        while (!file.eof())
        {
            point p;
            /*
             * For each pair of values, stores the first value on p.x and the
             * second on p.y . This continues until the end of the file.
             */
            file >> p.x >> p.y;
            data.push_back(p);
        }
        file.close();
    }

    void
    interpolate()
    {
        /*
         * Generates the divided differences table and stores the needed values
         * on the differences vector.
         */

        if (data.empty())
        {
            /* If there's no data yet, an exception will be thrown */
            throw GeneralException(
                "no data is avaiable to interpolate", __FILE__, __LINE__
                );
        }
        
        /* Allocates an array of pointers to numericType */
        numericType **table = (numericType **) calloc(
            data.size(), sizeof(numericType *)
            );
        
        /*
         * Now, allocates the arrays of numericType to store the lines of the
         * divided differences table. Note that the number of elements of the
         * array will be decreased on each iteration to avoid wasting memory.
         */
        for (int i = 0; i < data.size(); i++)
        {
            table[i] = (numericType *) calloc(
                data.size() - i, sizeof(numericType)
                );
            /*
             * The first column of the table is filled with the y coordinates of
             * the known points.
             */
            table[i][0] = data[i].y;
        }

        /*
         * The rest of the table will be filled with the divided differences,
         * that will be calculated next. For more info about this method, read
         * the file doc/maths.pdf . If you haven't received that file, you can
         * find the original version of this software at GitHub
         * <https://github.com/lvmalware/> .
         */
        for (int j = 1; j < data.size(); j++)
        {
            int k = j;
            for (int i = 0; i < (data.size() - j); i++)
            {
                table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) /
                              (data[k++].x - data[i].x);
            }
        }

        /*
         * Once the table is complete, we just need the first line. So, we add
         * each element from this line to the differences vector and delete the
         * table, avoiding memory waste.
         */
        for (int i = 0; i < data.size(); i++)
        {
            differences.push_back(table[0][i]);
            delete[] table[data.size() - 1 - i];
        }
                
        delete[] table;

    }

    numericType
    evaluate(numericType x)
    {
        /* Evaluates the generated polynomial using the value of x */

        if (differences.empty())
        {
            interpolate();
        }

        numericType result = 0;
        for (int i = 0; i < data.size(); i++)
        {
            numericType mul = 1;
            for (int j = 0; j < i; j++)
            {
                mul *= (x - data[j].x);
            }
            result += differences[i] * mul;
        }
        return result;
    }
};

#endif /*_NEWTON_HPP*/