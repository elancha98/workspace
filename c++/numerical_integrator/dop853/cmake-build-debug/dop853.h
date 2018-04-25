//
// Created by ernesto on 19/06/17.
//

#ifndef DOP853_DOP853_H
#define DOP853_DOP853_H

#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>
#include <climits>
#include <string>
#include <functional>

using namespace std;

typedef vector<double> (*FcnEqDiff)(double x, const vector<double> &y);
typedef bool (*SolTrait)(long nr, double xold, double x, const vector<double> &y, function<double(unsigned, double)> contd);

class Dop853 {
private:
    static int dopcore(FcnEqDiff fcn, double x, vector<double> &y, double xend, double hmax, double h,
                        const vector<double> &rtoler, const vector<double> &atoler, ostream *fileout, SolTrait solout,
                       int iout, long nmax, double uround, long nstiff, double safe, double beta, double fac1,
                       double fac2, const vector<unsigned> &icont, unsigned nrds);

    static double hinit(FcnEqDiff fcn, double x, const vector<double> &y, double posneg, const vector<double> &f0,
                     vector<double> &f1, vector<double> &yy1, int iord, double hmax, const vector<double> &atoler,
                     const vector<double> &rtoler);

    static double sign(double a, double b) {
        return (b < 0.0) ? -abs(a) : abs(a);
    }
public:
    static int dop853(FcnEqDiff fcn, double x, double xend, vector<double> &y, const vector<double> &rtoler,
                      const vector<double> &atoler, SolTrait solout, unsigned nrdens, const vector<unsigned> &icont,

                      int iout = 2, ostream *fileout = &cout, double uround = 2.3E-16, double safe = 0.9,
                      double fac1 = 0.333, double fac2 = 6.0, double beta = 0, double hmax = -1, double h = 0.0,
                      long nmax = 100000, long nstiff = 1000);
};


#endif //DOP853_DOP853_H
