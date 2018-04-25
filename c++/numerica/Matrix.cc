//
// Created by ernesto on 13/05/17.
//

#include "Matrix.hh"

vector<double> operator*(const vector<double> &u, double v) {
    vector<double> r = u;
    for (int i = 0; i < u.size(); i++)
        r[i] *= v;
    return r;
}
vector<double> operator+(const vector<double> &u, const vector<double> &v) {
    if (u.size() != v.size())
        throw length_error("wrong dimensions in vector addition");
    vector<double> r(u.size());
    for (int i = 0; i < u.size(); i++)
        r[i] = u[i]+v[i];
    return r;
}

void Matrix::print() const {
    for (int i = 0; i < rows(); ++i){
        for (int j = 0; j < columns(); ++j){
            if (j)
                cout << setw(25) << coef[i][j];
            else
                cout << coef[i][j];
        }
        cout << endl;
    }
}

void Matrix::read() {
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < columns(); j++)
            cin >> coef[i][j];
    }
}

double Matrix::norm_1(const Matrix &a)  {
    double max = -1;
    for (int i = 0; i < a.columns(); i++) {
        double sum = 0;
        for (int j = 0; j < a.rows(); j++)
            sum += abs(a.coef[j][i]);
        if (sum > max)
            max = sum;
    }
    return max;
}

double Matrix::norm_inf(const Matrix &a) {
    double max = -1;
    for (int i = 0; i < a.rows(); i++) {
        double sum = 0;
        for (int j = 0; j < a.columns(); j++)
            sum += abs(a.coef[i][j]);
        if (sum > max)
            max = sum;
    }
    return max;
}

double Matrix::norm_2(const Matrix &b) {
    Matrix a = b.transpose()*b;
    return sqrt(a.spectral_radius(1000));
}

double Matrix::trace() const {
    if (rows() == 0 or rows() != columns())
        throw length_error("Null or non-square dimensions in matrix trace");
    double res = 0;
    for (int i = 0; i < rows(); ++i)
        res += coef[i][i];
    return res;
}

double Matrix::det(double tol) const {
    if (rows() == 0 or rows() != columns())
        throw length_error("Null or non-square dimensions in matrix determinant");
    Matrix copA = *this;
    vector<int> perm(rows());
    for (int i = 0; i < perm.size(); ++i)
        perm[i] = i;
    int r = copA.lu(perm, tol);
    double res = 0;
    if (r == 0)
        return -1;
    res = r;
    for (int i = 0; i < copA.rows(); ++i)
        res *= copA.coef[i][i];
    return 0;
}

double Matrix::spectral_radius(double tol) const {
    if (rows() == 0 or rows() != columns())
        throw length_error("Null or non-square dimensions in matrix spectral radius");
    vector<double> y(rows(), 1.0), z;

    double vap, max_it =10000;
    z = (*this)*y;
    for (int i = 0; i < max_it and norm_inf(z + (y*-vap)) > tol; i++) {
        y = z*(1/norm_inf(z));
        z = (*this)*y;
        vap = norm_inf_(z)/norm_inf_(y);
    }
    return abs(vap);
}

Matrix Matrix::transpose() const {
    if (rows() == 0 or columns() == 0)
        throw length_error("Null dimensions in matrix transposition");
    Matrix B(columns(), rows());
    for (int i = 0; i < rows(); ++i){
        for (int j = 0; j < columns(); ++j){
            B.coef[j][i] = coef[i][j];
        }
    }
    return B;
}

Matrix Matrix::inverse(double tol) const {
    if (rows() == 0 or columns() == 0 or rows() != columns())
        throw length_error("Null or non-square dimensions in matrix inversion");
    int n = rows();
    Matrix copA = *this;
    Matrix inverse = *this;
    vector<int> perm(rows());
    for (int i = 0; i < n; ++i)
        perm[i] = i;
    int r = copA.lu(perm, tol);
    if (r == 0)
        throw invalid_argument("No inverse in requested inversion");
    for (int j = 0; j < n; ++j){
        vector<double> b(n, 0), x;
        b[j] = 1;
        resol(copA, x, b, perm);
        for (int i = 0; i < n; ++i)
            inverse.coef[i][j] = x[i];
    }
    return inverse;
}

int Matrix::lu(vector<int> &perm, double tol) {
    if (rows() == 0 or rows() != columns())
        throw length_error("Null or non-square dimensions in matrix lu");
    int n = rows();
    int impar = 0;
    for (int i = 0; i < n; i++) {
        int pivot = 0;
        double val = -1.;
        for (int j = i; j < n; j++) {
            double maxim = 0.;
            for (int k = i; k < n; k++) {
                if (abs(coef[j][k]) > maxim)
                    maxim = abs(coef[j][k]);
            }
            if (maxim < tol)
                return 0;
            double cand = abs(coef[j][i])/maxim;
            if (val < cand) {
                val = cand;
                pivot = j;
            }
        }
        if (val < tol)
            return 0;
        impar ^= (i != pivot);
        swap(perm[i], perm[pivot]);
        swap(coef[i], coef[pivot]);

        for (int j = i+1; j < n; j++) {
            double m = coef[j][i]/coef[i][i];
            coef[j][i] = m;
            for (int k = i+1; k < n; k++) {
                coef[j][k] -= coef[i][k]*m;
            }
        }
    }
    return (-2*impar + 1)/ 1;
}

void Matrix::resol(const Matrix &a, vector<double> &x, const vector<double> &b, const vector<int> &perm) {
    int n = a.rows();
    vector<double> cp(n);
    x = vector<double>(n);
    for (int i = 0; i < n; ++i)
        cp[i] = b[perm[i]];
    for (int i = 0; i < n; ++i){
        double sum = 0.;
        for (int j = 0; j < i; ++j)
            sum += a.coef[i][j]*x[j];
        x[i] = (cp[i] - sum);
    }

    for (int i = n - 1; i >= 0; i--){
        double sum = 0.;
        for (int j = n - 1; j > i; j--)
            sum += a.coef[i][j]*x[j];
        x[i] = (x[i] - sum)/a.coef[i][i];
    }
}

int Matrix::sistema(Matrix &a, vector<double> &x, const vector<double> &b, double tol) {
    if (a.rows() == 0 or a.columns() == 0)
        throw length_error("Null dimensions in matrix system");
    int n = a.rows();
    vector<int> p(n);
    for (int i = 0; i < n; ++i)
        p[i] = i;
    int r = a.lu(p, tol);
    if (r != 0)
        resol(a, x, b, p);
    return r;
}

double operator*(const vector<double> &u, const vector<double> &v) {
    if (u.size() == 0 or u.size() != v.size())
        throw length_error("Wrong or null dimensions in scalar product");
    double res = 0;
    for (int i = 0; i < u.size(); ++i)
        res += u[i]*v[i];
    return res;
}

Matrix Matrix::operator*(const Matrix &b) const {
    if (rows() == 0 or columns() == 0 or columns() != b.rows() or b.rows() == 0)
        throw  length_error("Wrong or null dimensions in matrix multiplication");
    Matrix res(b.columns(), rows());
    for (int j = 0; j < b.columns(); ++j){
        res.coef[j] = (*this)*b.get_column(j);
    }
    return res.transpose();
}

vector<double> Matrix::operator*(const vector<double> &v) const {
    if (rows() == 0 or columns() == 0 or columns() != v.size())
        throw  length_error("Wrong or null dimensions in vector multiplication");
    vector<double> res(rows(), 0);
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < columns(); j++) {
            res[i] += coef[i][j] * v[j];
        }
    }
    return res;
}

double Matrix::norm(const vector<double> &v) {
    return sqrt(v*v);
}

double Matrix::norm_inf(const vector<double> &v) {
    double d = -INFINITY;
    for (int i = 0; i < v.size(); i++)
        d = max(d, abs(v[i]));
    return d;
}

double Matrix::norm_inf_(const vector<double> &v) {
    double d = 0;
    for (int i = 0; i < v.size(); i++) {
        if (abs(v[i]) > abs(d))
            d = v[i];
    }
    return d;
}

pair<Matrix, vector<double> > Matrix::load(string file) {
    ifstream in(file);
    if (!in.is_open())
        throw invalid_argument("File " + file + " can't be opened");
    int r, m;
    in >> r >> m;
    Matrix ret(r, r);
    vector<double> ret_(r);
    for (int k = 0; k < m; k++) {
        int i, j;
        double v;
        in >> i >> j >> v;
        ret.coef[i][j] = v;
    }
    in >> m;
    for (int k = 0; k < m; k++) {
        int i;
        double v;
        in >> i >> v;
        ret_[i] = v;
    }
    in.close();
    return make_pair(ret, ret_);
}

Matrix Matrix::qr() {
    if (rows() == 0 or columns() == 0)
        throw length_error("Null dimensions in qr decomposition");
    Matrix R = Matrix(columns(), columns());
    for (int i = 0; i < columns(); i++) {
        double n = norm(get_column(i));
        R.coef[i][i] = n;
        for (int j = 0; j < rows(); j++)
            coef[j][i] /= n;
        vector<double> column = get_column(i);
        for (int j = i+1; j < columns(); j++) {
            R.coef[i][j] = column * get_column(j);
            for (int k = 0; k < rows(); k++)
                coef[k][j] -= R.coef[i][j] * coef[k][i];
        }
    }
    return R;
}