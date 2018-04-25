//
// Created by ernesto on 19/06/17.
//

#include <climits>
#include "Dopri853.h"
#include "constants.h"

int Dopri853::dop853(FcnEqDiff fcn, double x, vector<double> &y, double xend, vector<double> &rtoler,
                     vector<double> &atoler, SolTrait solout, unsigned nrdens, vector<unsigned> &icont, double h,
                     long nmax, long nstiff, int iout, ofstream *fileout, double uround, double safe, double fac1,
                     double fac2, double beta, double hmax) {
    unsigned n = y.size();
    /* ====== VERIFY INPUT ====== */
    if (n == UINT_MAX)
        throw invalid_argument("System too big, max. n = " + to_string(UINT_MAX - 1));
    if (nmax <= 0)
        throw invalid_argument("Wrong input, nmax = " + to_string(nmax));
    if (nstiff < 0.0)
        nstiff = nmax + 10;
    if (iout < 0 or iout > 2)
        throw invalid_argument("Wrong input, iout = " + to_string(iout));
    if ((uround <= 1.0E-35) || (uround >= 1.0))
        throw invalid_argument("Which machine do you have ? Your uround was : " + to_string(uround));
    if ((safe >= 1.0) || (safe <= 1.0E-4))
        throw invalid_argument("Curious input for safety factor, safe = " + to_string(safe));
    if (beta > 0.2)
        throw invalid_argument("Curious input for beta : beta = " + to_string(beta));

    if (nrdens > n)
        throw invalid_argument("Curious input, nrdens = " + to_string(nrdens));

    if (nrdens == n and icont.size() > 0 and fileout)
        (*fileout) << "Warning : when nrdens = n there is no need allocating memory for icont" << endl;
    else if (icont.size() < nrdens)
        throw invalid_argument("Insufficient storage for icont, min. licont = " + to_string(nrdens));

    /* === INITIALIZE INDIR === */
    vector<unsigned> indir(n);
    for (unsigned i = 0; i < n; i++)
        indir[i] = UINT_MAX;
    for (unsigned i = 0; i < nrdens; i++)
        indir[icont[i]] = i;

    return dopcor(fcn, x, y, xend, hmax, h, rtoler, atoler, fileout, solout, iout, nmax,
                  uround, nstiff, safe, beta, fac1, fac2, icont, nrdens, indir);
}

int Dopri853::dopcor(FcnEqDiff fcn, double x, vector<double> &y, double xend, double hmax, double h,
                     vector<double> &rtoler, vector<double> &atoler, ofstream *fileout, SolTrait solout, int iout,
                     long nmax, double uround, long nstiff, double safe, double beta, double fac1, double fac2,
                     vector<unsigned> &icont, unsigned nrds, vector<unsigned> &indir) {
    unsigned n = y.size();
    vector<double> yy1(n), k1, k2, k3, k4, k5, k6, k7, k8, k9, k10;

    double facold = 1.0E-4;
    double expo1 = 1.0 / 8.0 - beta * 0.2;
    double facc1 = 1.0 / fac1;
    double facc2 = 1.0 / fac2;
    double posneg = sign(1.0, xend - x);

    double atoli = atoler[0];
    double rtoli = rtoler[0];
    int last = 0;
    double hlamb = 0.0;
    int iasti = 0;
    k1 = fcn(x, y);
    hmax = abs(hmax);
    int iord = 8;
    if (h == 0.0)
        h = hinit(fcn, x, y, posneg, k1, k2, k3, iord, hmax, atoler, rtoler);
    long nfcn = 2;
    int reject = 0;
    double xold = x;

    double xout, hout;

    long nstep = 0, naccpt = 0, nrejct = 0;

    /* === INITIALIZE RCONT === */
    vector<double> rcont1(nrds);
    vector<double> rcont2(nrds);
    vector<double> rcont3(nrds);
    vector<double> rcont4(nrds);
    vector<double> rcont5(nrds);
    vector<double> rcont6(nrds);
    vector<double> rcont7(nrds);
    vector<double> rcont8(nrds);

    if (iout) {
        hout = 1.0;
        xout = x;
        bool irtrn = solout(naccpt + 1, xold, x, y, fileout, indir);
        if (!irtrn) {
            if (fileout)
                (*fileout) << "Exit of dop853 at x = " << x << endl;
            return 2;
        }
    }

    /* basic integration step */
    while (true) {
        if (nstep > nmax) {
            if (fileout) {
                (*fileout) << "Exit of dop853 at x = " << x << ", more than nmax = " << nmax << "staps are needed"
                           << endl;
                xout = x;
                hout = h;
                return -2;
            }
        }
        if (0.1 * fabs(h) <= fabs(x) * uround) {
            if (fileout)
                (*fileout) << "Exit of dop853 at x = " << x << ", step size too small h = " << h << endl;
            xout = x;
            hout = h;
            return -3;
        }

        if ((x + 1.01 * h - xend) * posneg > 0.0) {
            h = xend - x;
            last = 1;
        }

        nstep++;
        for (unsigned i = 0; i < n; i++)
            yy1[i] = y[i] + h * cts::a21 * k1[i];
        k2 = fcn(x + cts::c2 * h, yy1);
        for (unsigned i = 0; i < n; i++)
            yy1[i] = y[i] + h * (cts::a31 * k1[i] + cts::a32 * k2[i]);
        k3 = fcn(x + cts::c3 * h, yy1);
        for (unsigned i = 0; i < n; i++)
            yy1[i] = y[i] + h * (cts::a41 * k1[i] + cts::a43 * k3[i]);
        k4 = fcn(x + cts::c4 * h, yy1);
        for (unsigned i = 0; i < n; i++)
            yy1[i] = y[i] + h * (cts::a51 * k1[i] + cts::a53 * k3[i] + cts::a54 * k4[i]);
        k5 = fcn(x + cts::c5 * h, yy1);
        for (unsigned i = 0; i < n; i++)
            yy1[i] = y[i] + h * (cts::a61 * k1[i] + cts::a64 * k4[i] + cts::a65 * k5[i]);
        k6 = fcn(x + cts::c6 * h, yy1);
        for (unsigned i = 0; i < n; i++)
            yy1[i] = y[i] + h * (cts::a71 * k1[i] + cts::a74 * k4[i] + cts::a75 * k5[i] + cts::a76 * k6[i]);
        k7 = fcn(x + cts::c7 * h, yy1);
        for (unsigned i = 0; i < n; i++)
            yy1[i] = y[i] + h * (cts::a81 * k1[i] + cts::a84 * k4[i] + cts::a85 * k5[i] + cts::a86 * k6[i] +
                                 cts::a87 * k7[i]);
        k8 = fcn(x + cts::c8 * h, yy1);
        for (unsigned i = 0; i < n; i++)
            yy1[i] = y[i] + h * (cts::a91 * k1[i] + cts::a94 * k4[i] + cts::a95 * k5[i] + cts::a96 * k6[i] +
                                 cts::a97 * k7[i] + cts::a98 * k8[i]);
        k9 = fcn(x + cts::c9 * h, yy1);
        for (unsigned i = 0; i < n; i++)
            yy1[i] = y[i] + h * (cts::a101 * k1[i] + cts::a104 * k4[i] + cts::a105 * k5[i] + cts::a106 * k6[i] +
                                 cts::a107 * k7[i] + cts::a108 * k8[i] + cts::a109 * k9[i]);
        k10 = fcn(x + cts::c10 * h, yy1);
        for (unsigned i = 0; i < n; i++)
            yy1[i] = y[i] + h * (cts::a111 * k1[i] + cts::a114 * k4[i] + cts::a115 * k5[i] + cts::a116 * k6[i] +
                                 cts::a117 * k7[i] + cts::a118 * k8[i] + cts::a119 * k9[i] + cts::a1110 * k10[i]);
        k2 = fcn(x + cts::c11 * h, yy1);
        //xph = x + h;
        for (unsigned i = 0; i < n; i++)
            yy1[i] = y[i] + h * (cts::a121 * k1[i] + cts::a124 * k4[i] + cts::a125 * k5[i] + cts::a126 * k6[i] +
                                 cts::a127 * k7[i] + cts::a128 * k8[i] + cts::a129 * k9[i] + cts::a1210 * k10[i] +
                                 cts::a1211 * k2[i]);
        k3 = fcn(x + h, yy1);
        nfcn += 11;
        for (unsigned i = 0; i < n; i++) {
            k4[i] = cts::b1 * k1[i] + cts::b6 * k6[i] + cts::b7 * k7[i] + cts::b8 * k8[i] + cts::b9 * k9[i] +
                    cts::b10 * k10[i] + cts::b11 * k2[i] + cts::b12 * k3[i];
            k5[i] = y[i] + h * k4[i];
        }

        /* error estimation */
        double err = 0.0;
        double err2 = 0.0;
        if (atoler.size() == 1) {
            for (unsigned i = 0; i < n; i++) {
                double sk = atoli + rtoli * max(abs(y[i]), abs(k5[i]));
                double erri = k4[i] - cts::bhh1 * k1[i] - cts::bhh2 * k9[i] - cts::bhh3 * k3[i];
                double sqr = erri / sk;
                err2 += sqr * sqr;
                erri = cts::er1 * k1[i] + cts::er6 * k6[i] + cts::er7 * k7[i] + cts::er8 * k8[i] + cts::er9 * k9[i] +
                       cts::er10 * k10[i] + cts::er11 * k2[i] + cts::er12 * k3[i];
                sqr = erri / sk;
                err += sqr * sqr;
            }
        } else {
            for (unsigned i = 0; i < n; i++) {
                double sk = atoler[i] + rtoler[i] * max(abs(y[i]), abs(k5[i]));
                double erri = k4[i] - cts::bhh1 * k1[i] - cts::bhh2 * k9[i] - cts::bhh3 * k3[i];
                double sqr = erri / sk;
                err2 += sqr * sqr;
                erri = cts::er1 * k1[i] + cts::er6 * k6[i] + cts::er7 * k7[i] + cts::er8 * k8[i] + cts::er9 * k9[i] +
                       cts::er10 * k10[i] + cts::er11 * k2[i] + cts::er12 * k3[i];
                sqr = erri / sk;
                err += sqr * sqr;
            }
        }

        double deno = err + 0.01 * err2;
        if (deno <= 0.0)
            deno = 1.0;
        err = abs(h) * err * sqrt(1.0 / (deno * (double) n));

        /* computation of hnew */
        double fac11 = pow(err, expo1);
        /* Lund-stabilization */
        double fac = fac11 / pow(facold, beta);
        /* we require fac1 <= hnew/h <= fac2 */
        fac = max(facc2, min(facc1, fac / safe));
        double hnew = h / fac;

        if (err <= 1.0) {
            facold = max(err, 1.0E-4);
            naccpt++;
            k4 = fcn(x + h, k5);
            nfcn++;

            int nonsti;
            /* stiffness detection */
            if (!(naccpt % nstiff) or iasti > 0) {
                double stnum = 0.0;
                double stden = 0.0;
                for (unsigned i = 0; i < n; i++) {
                    double sqr = k4[i] - k3[i];
                    stnum += sqr * sqr;
                    sqr = k5[i] - yy1[i];
                    stden += sqr * sqr;
                }
                if (stden > 0.0)
                    hlamb = h * sqrt(stnum / stden);
                if (hlamb > 6.1) {
                    nonsti = 0;
                    iasti++;
                    if (iasti == 15)
                        if (fileout)
                            (*fileout) << "The problem seems to become stiff at x = " << x << endl;
                        else {
                            xout = x;
                            hout = h;
                            return -4;
                        }
                } else {
                    nonsti++;
                    if (nonsti == 6)
                        iasti = 0;
                }
            }

            if (iout == 2) {
                if (nrds == n) {
                    for (unsigned i = 0; i < n; i++) {
                        rcont1[i] = y[i];
                        double ydiff = k5[i] - y[i];
                        rcont2[i] = ydiff;
                        double bspl = h * k1[i] - ydiff;
                        rcont3[i] = bspl;
                        rcont4[i] = ydiff - h * k4[i] - bspl;
                        rcont5[i] = cts::d41 * k1[i] + cts::d46 * k6[i] + cts::d47 * k7[i] + cts::d48 * k8[i] +
                                cts::d49 * k9[i] + cts::d410 * k10[i] + cts::d411 * k2[i] + cts::d412 * k3[i];
                        rcont6[i] = cts::d51 * k1[i] + cts::d56 * k6[i] + cts::d57 * k7[i] + cts::d58 * k8[i] +
                                cts::d59 * k9[i] + cts::d510 * k10[i] + cts::d511 * k2[i] + cts::d512 * k3[i];
                        rcont7[i] = cts::d61 * k1[i] + cts::d66 * k6[i] + cts::d67 * k7[i] + cts::d68 * k8[i] +
                                cts::d69 * k9[i] + cts::d610 * k10[i] + cts::d611 * k2[i] + cts::d612 * k3[i];
                        rcont8[i] = cts::d71 * k1[i] + cts::d76 * k6[i] + cts::d77 * k7[i] + cts::d78 * k8[i] +
                                cts::d79 * k9[i] + cts::d710 * k10[i] + cts::d711 * k2[i] + cts::d712 * k3[i];
                    }
                } else {
                    for (unsigned j = 0; j < nrds; j++) {
                        unsigned i = icont[j];
                        rcont1[j] = y[i];
                        double ydiff = k5[i] - y[i];
                        rcont2[j] = ydiff;
                        double bspl = h * k1[i] - ydiff;
                        rcont3[j] = bspl;
                        rcont4[j] = ydiff - h * k4[i] - bspl;
                        rcont5[j] = cts::d41 * k1[i] + cts::d46 * k6[i] + cts::d47 * k7[i] + cts::d48 * k8[i] +
                                cts::d49 * k9[i] + cts::d410 * k10[i] + cts::d411 * k2[i] + cts::d412 * k3[i];
                        rcont6[j] = cts::d51 * k1[i] + cts::d56 * k6[i] + cts::d57 * k7[i] + cts::d58 * k8[i] +
                                cts::d59 * k9[i] + cts::d510 * k10[i] + cts::d511 * k2[i] + cts::d512 * k3[i];
                        rcont7[j] = cts::d61 * k1[i] + cts::d66 * k6[i] + cts::d67 * k7[i] + cts::d68 * k8[i] +
                                cts::d69 * k9[i] + cts::d610 * k10[i] + cts::d611 * k2[i] + cts::d612 * k3[i];
                        rcont8[j] = cts::d71 * k1[i] + cts::d76 * k6[i] + cts::d77 * k7[i] + cts::d78 * k8[i] +
                                cts::d79 * k9[i] + cts::d710 * k10[i] + cts::d711 * k2[i] + cts::d712 * k3[i];
                    }
                }


                /* the next three function evaluations */
                for (unsigned i = 0; i < n; i++)
                    yy1[i] = y[i] + h * (cts::a141 * k1[i] + cts::a147 * k7[i] + cts::a148 * k8[i] +
                            cts::a149 * k9[i] + cts::a1410 * k10[i] + cts::a1411 * k2[i] + cts::a1412 * k3[i] +
                            cts::a1413 * k4[i]);
                k10 = fcn(x + cts::c14 * h, yy1);
                for (unsigned i = 0; i < n; i++)
                    yy1[i] = y[i] + h * (cts::a151 * k1[i] + cts::a156 * k6[i] + cts::a157 * k7[i] + cts::a158 * k8[i] +
                            cts::a1511 * k2[i] + cts::a1512 * k3[i] + cts::a1513 * k4[i] + cts::a1514 * k10[i]);
                k2 = fcn(x + cts::c15 * h, yy1);
                for (unsigned i = 0; i < n; i++)
                    yy1[i] = y[i] + h * (cts::a161 * k1[i] + cts::a166 * k6[i] + cts::a167 * k7[i] + cts::a168 * k8[i] +
                            cts::a169 * k9[i] + cts::a1613 * k4[i] + cts::a1614 * k10[i] + cts::a1615 * k2[i]);
                k3 = fcn(x + cts::c16 * h, yy1);
                nfcn += 3;

                /* final preparation */
                if (nrds == n) {
                    for (unsigned i = 0; i < n; i++) {
                        rcont5[i] = h * (rcont5[i] + cts::d413 * k4[i] + cts::d414 * k10[i] + cts::d415 * k2[i] +
                                cts::d416 * k3[i]);
                        rcont6[i] = h * (rcont6[i] + cts::d513 * k4[i] + cts::d514 * k10[i] + cts::d515 * k2[i] +
                                cts::d516 * k3[i]);
                        rcont7[i] = h * (rcont7[i] + cts::d613 * k4[i] + cts::d614 * k10[i] + cts::d615 * k2[i] +
                                cts::d616 * k3[i]);
                        rcont8[i] = h * (rcont8[i] + cts::d713 * k4[i] + cts::d714 * k10[i] + cts::d715 * k2[i] +
                                cts::d716 * k3[i]);
                    }
                } else {
                    for (unsigned j = 0; j < nrds; j++) {
                        unsigned i = icont[j];
                        rcont5[j] = h * (rcont5[j] + cts::d413 * k4[i] + cts::d414 * k10[i] + cts::d415 * k2[i] +
                                cts::d416 * k3[i]);
                        rcont6[j] = h * (rcont6[j] + cts::d513 * k4[i] + cts::d514 * k10[i] + cts::d515 * k2[i] +
                                cts::d516 * k3[i]);
                        rcont7[j] = h * (rcont7[j] + cts::d613 * k4[i] + cts::d614 * k10[i] + cts::d615 * k2[i] +
                                cts::d616 * k3[i]);
                        rcont8[j] = h * (rcont8[j] + cts::d713 * k4[i] + cts::d714 * k10[i] + cts::d715 * k2[i] +
                                cts::d716 * k3[i]);
                    }
                }
            }

            k1 = k4;
            y = k5;
            xold = x;
            x += h;

            if (iout) {
                hout = h;
                xout = x;
                bool irtrn = solout(naccpt + 1, xold, x, y, fileout, indir);
                if (!irtrn) {
                    if (fileout)
                        (*fileout) << "Exit of dop853 at x = " << x << endl;
                    return 2;
                }
            }

            /* normal exit */
            if (last) {
                hout = hnew;
                xout = x;
                return 1;
            }

            if (abs(hnew) > hmax)
                hnew = posneg * hmax;
            if (reject)
                hnew = posneg * min(abs(hnew), abs(h));

            reject = 0;
        } else {
            /* step rejected */
            hnew = h / min(facc1, fac11 / safe);
            reject = 1;
            if (naccpt >= 1)
                nrejct++;
            last = 0;
        }
        h = hnew;
    }
    return 0;
}

double
Dopri853::hinit(FcnEqDiff fcn, double x, vector<double> &y, double posneg, vector<double> &f0, vector<double> &f1,
                vector<double> &yy1, int iord, double hmax, vector<double> atoler, vector<double> rtoler) {

    unsigned n = y.size();

    double dnf = 0.0;
    double dny = 0.0;
    double atoli = atoler[0];
    double rtoli = rtoler[0];

    if (atoler.size() == 1) {
        for (unsigned i = 0; i < n; i++) {
            double sk = atoli + rtoli + abs(y[i]);
            double sqr = f0[i]/sk;
            dnf += sqr*sqr;
            sqr = y[i] / sk;
            dny += sqr*sqr;
        }
    } else {
        for (unsigned i = 0; i < n; i++) {
            double sk = atoler[i] + rtoler[i] * fabs(y[i]);
            double sqr = f0[i] / sk;
            dnf += sqr * sqr;
            sqr = y[i] / sk;
            dny += sqr * sqr;
        }
    }

    double h;
    if (dnf <= 1.0E-10 or dny <= 1.0E-10)
        h = 1.0E-6;
    else
        h = sqrt(dny / dnf) * 0.01;

    h = min(h, hmax);
    h = sign(h, posneg);

    for (unsigned i = 0; i < n; i++)
        yy1[i] = y[i] + h * f0[i];
    f1 = fcn(x + h, yy1);

    double der2 = 0.0;
    if (atoler.size() == 1) {
        for (unsigned i = 0; i < n; i++) {
            double sk = atoli + rtoli * fabs(y[i]);
            double sqr = (f1[i] - f0[i]) / sk;
            der2 += sqr * sqr;
        }
    } else {
        for (unsigned i = 0; i < n; i++) {
            double sk = atoler[i] + rtoler[i] * fabs(y[i]);
            double sqr = (f1[i] - f0[i]) / sk;
            der2 += sqr * sqr;
        }
    }
    der2 = sqrt(der2) / h;

    double der12 = max(abs(der2), sqrt(dnf));
    double h1;
    if (der12 <= 1.0E-15)
        h1 = max(1.0E-6, fabs(h) * 1.0E-3);
    else
        h1 = pow(0.01 / der12, 1.0 / (double) iord);
    h = min(100.0 * abs(h), min(h1, hmax));
    return sign(h, posneg);
}

double Dopri853::contd8(unsigned ii, double x, ofstream *fileout, vector<unsigned> &indir) {
    unsigned i, j;
    double s, s1;

    i = UINT_MAX;

    if (indir.size() == 0)
        i = ii;
    else
        i = indir[ii];

    if (i == UINT_MAX) {
        (*fileout) << "No dense output available for " << ii << "th component" << endl;
        return 0.0;
    }

    s = (x - xold) / hout;
    s1 = 1.0 - s;

    return rcont1[i] + s * (rcont2[i] + s1 * (rcont3[i] + s * (rcont4[i] + s1 * (rcont5[i] +
                                                                                 s * (rcont6[i] + s1 * (rcont7[i] + s *
                                                                                                                    rcont8[i]))))));
    return 0;
}

