#include <iostream>
#include "newton.hpp"

using namespace std;

int
main(int argc, char *argv[])
{
    NewtonInterpolator<double> n;
    n.loadData("../data.txt");
    n.interpolate();
    cout << n.evaluate(2018) << endl;
    return 0;
}