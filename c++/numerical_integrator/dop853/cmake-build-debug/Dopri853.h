//
// Created by ernesto on 19/06/17.
//

#ifndef DOP853_DOPRI853_H
#define DOP853_DOPRI853_H

#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

typedef vector<double> (*FcnEqDiff)(double x, vector<double> y);

typedef bool (*SolTrait)(long nr, double xold, double x, vector<double> y, ofstream *fileout, vector<unsigned> &indir);

class Dopri853 {

private:
    //TODO Add CLKernels and required functions here

    static int dopcor(FcnEqDiff fcn, double x, vector<double> &y, double xend, double hmax, double h,
                      vector<double> &rtoler, vector<double> &atoler, ofstream *fileout, SolTrait solout, int iout,
                      long nmax, double uround, long nstiff, double safe, double beta, double fac1, double fac2,
                      vector<unsigned> &icont, unsigned nrds, vector<unsigned> &indir);

    static double hinit(FcnEqDiff fcn, double x, vector<double> &y, double posneg, vector<double> &f0,
                        vector<double> & f1, vector<double> &yy1, int iord, double hmax, vector<double> atoler,
                        vector<double> rtoler);

    static double sign(double a, double b) {
        return (b < 0.0) ? -abs(a) : abs(a);
    }

public:
//    static int dop853(unsigned n, FcnEqDiff fcn, double x, vector<double> y, double xend, vector<double> rtoler,
//             vector<double> atoler, SolTrait solout, int iout = 2, ofstream fileout = stdout, double uround = 2.3E-16,
//             double safe = 0.9, double fac1 = 0.333, double fac2 = 6.0, double beta = 0, double hmax = xend - x,
//             double h, long nmax = 100000, long nstiff = 1000, unsigned nrdens, vector<unsigned> icont);


    static int dop853(FcnEqDiff fcn, double x, vector<double> &y, double xend, vector<double> &rtoler,
                      vector<double> &atoler, SolTrait solout, unsigned nrdens, vector<unsigned> &icont, double h = 0.0,
                      long nmax = 100000, long nstiff = 1000, int iout = 2, ofstream *fileout = stdout,
                      double uround = 2.3E-16, double safe = 0.9, double fac1 = 0.333, double fac2 = 6.0,
                      double beta = 0, double hmax = xend - x);

    static double contd8(unsigned ii, double x, ofstream *fileout, vector<unsigned> &indir);
};


#endif //DOP853_DOPRI853_H
