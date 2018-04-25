//
// Created by ernesto on 13/05/17.
//

#ifndef NUMERICA_MATRIX_HH
#define NUMERICA_MATRIX_HH

#include <vector>
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "Utils.hh"

using namespace std;

class Matrix {
public:

    Matrix(int rows, int columns) : coef(rows, vector<double>(columns, 0.0)) {};

    void print() const;
    void read();

    inline int rows() const { return coef.size();};
    inline int columns() const { return coef[0].size();};
    inline vector<double> get_column(int j) const {
        vector<double> c(rows());
        for (int i = 0; i < rows(); i++)
            c[i] = coef[i][j];
        return c;
    };

    static double norm_1(const Matrix &a);
    static double norm_inf(const Matrix &a);
    static double norm_2(const Matrix &a);
    template <typename Func> static double condition_number(Func norm, const Matrix &a) {
        return norm(a)*norm(a.inverse(0.001));
    }

    double trace() const;
    double det(double tol) const;
    double spectral_radius(double tol) const;

    Matrix transpose() const;
    Matrix inverse(double tol) const;

    int lu(vector<int> &perm, double tol);
    Matrix qr();

    static void resol(const Matrix &a, vector<double> &x, const vector<double> &b, const vector<int> &perm);
    static int sistema(Matrix &a, vector<double> &x, const vector<double> &b, double tol);

    static double norm(const vector<double> &v);
    static double norm_inf(const vector<double> &v);
    static double norm_inf_(const vector<double> &v);
    template <class T> static void print(const vector<T> &v) {
        for (int i = 0; i < v.size(); i++)
            cout << v[i] << " ";
        cout << endl;
    };

    static pair<Matrix, vector<double> > load(string file);

    Matrix operator*(const Matrix &b) const;
    vector<double> operator*(const vector<double> &v) const;

private:
    vector<vector<double> > coef;
};


#endif //NUMERICA_MATRIX_HH
