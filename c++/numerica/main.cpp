#include <iostream>
#include "Matrix.hh"

using namespace std;

int main() {
    pair<Matrix, vector<double> > p = Matrix::load("M1.DAT");
    double d = 0.1 * 100 * cos(0.01*100);
    p.second[0] += d;
    vector<double> x(p.first.rows());
    Matrix::sistema(p.first, x, p.second, 10e-10);
    cout << setprecision(15);
    cout << fixed;
    cout << Matrix::norm_inf(x) << endl;

    // Un simple cambio
}
