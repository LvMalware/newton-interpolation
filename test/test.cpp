#include <iostream>
#include "../src/newton.hpp"

using namespace std;

int
main(int argc, char *argv[])
{
    NewtonInterpolator<double> interp;
    interp.loadData("data.txt");
    interp.interpolate();
    cout << "+-----------------------+" << endl;
    cout << "|   YEAR  |  ACCIDENTS  |" << endl;
    cout << "+-----------------------+" << endl;
    for (int year = 2008; year < 2018; year++)
    {
        cout << "|  " << year << "   |\t" <<
            interp.evaluate(year) << "\t|" << endl;
    }
    cout << "+-----------------------+" << endl;
    return 0;
}