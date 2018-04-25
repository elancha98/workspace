#include <iostream>
#include <vector>
#include "cmake-build-debug/dop853.h"

#define  ndgl      2
#define  nrdens    2

using namespace std;

vector<double> fvpol(double x, const vector<double> &y) {
    const double eps = 1.0E-3;
    vector<double> f(2);
    f[0] = y[1];
    f[1] = ((1.0 - y[0] * y[0]) * y[1] - y[0]) / eps;
    return f;
}

bool solout(long nr, double xold, double x, const vector<double> &y, function<double(unsigned, double)> contd) {
    static double xout;
    if (nr == 1) {
        cout << "x=" << x << " y=" << y[0] << " " << y[1] << " nstep=" << nr-1 << endl;
        xout = x + 0.1;
    } else {
        while (x >= xout) {
            cout << "x=" << xout << " y=" << contd(0, xout) << " " << contd(1, xout) << " nstep=" << nr - 1 << endl;
            xout += 0.1;
        }
    }
    return true;
}

int main() {
    vector<double> y(ndgl);
    int res, iout, itoler;
    double x, xend;
    vector<double> atoler, rtoler(1);

    iout = 2;
    x = 0.0;
    y[0] = 2.0;
    y[1] = 0.0;
    xend = 2.0;
    itoler = 0;
    rtoler[0] = 1.0E-6;
    atoler = rtoler;

    res = Dop853::dop853(fvpol, x, xend, y, rtoler, atoler, solout, ndgl, vector<unsigned>(0),
            iout, &cout, 2.3E-16, 0.9, 0.333, 6.0, 0.0, -1, 0.0, 100000, 1);
    //res = Dop853::dop853(ndgl, fvpol, x, y, xend, &rtoler, &atoler, itoler, solout, iout,
                 //stdout, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 1, ndgl, NULL, 0);

    cout << "x=xend  y=" << y[0] << " " << y[1] << endl;

    return 0;
}