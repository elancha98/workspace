#include "matrices.hh"
#include <iostream>
#include <iomanip>

int lu(vector<vector<double> > &a, int n, vector<int> &perm, double tol) {
    int impar = 0;
    for (int i = 0; i < n; i++) {
        int pivot;
        double val = -1.;
        for (int j = i; j < n; j++) {
            double maxim = 0.;
            for (int k = i; k < n; k++)
                if (abs(a[j][k]) > maxim)
                    maxim = abs(a[j][k]);
            if (maxim < tol) return 0;
            double cand = abs(a[j][i])/maxim;
            if (val < cand) {
                val = cand;
                pivot = j;
            }
        }
        cout << pivot << endl;
        if (val < tol) return 0;
        impar ^= (i != pivot);
        swap(perm[i], perm[pivot]);
        swap(a[i], a[pivot]);

        for (int j = i+1; j < n; j++) {
            double m = a[j][i]/a[i][i];
            a[j][i] = m;
            for (int k = i+1; k < n; k++) {
                a[j][k] -= a[i][k]*m;
            }
        }
    }
    return (-2*impar + 1)/ 1;
}

void resol(const vector<vector<double> > &a, vector<double> &x, const vector<double> &b, int n, const vector<int> &perm) {
    vector<double> cp(n);
    x = vector<double> (n);
    for (int i = 0; i < n; ++i)
        cp[i] = b[perm[i]];
    for (int i = 0; i < n; ++i){
        double sum = 0.;
        for (int j = 0; j < i; ++j) sum += a[i][j]*x[j];
        x[i] = (cp[i] - sum);
    }
    
    for (int i = n - 1; i >= 0; i--){
        double sum = 0.;
        for (int j = n - 1; j > i; j--) sum += a[i][j]*x[j];
        x[i] = (x[i] - sum)/a[i][i];
    }    
}


int sproduct(const vector<double> &u, const vector<double> &v, double &res){
  if (u.size() == 0 or u.size() != v.size()){
    cerr << "Wrong or null dimensions in scalar product" << endl;
    return -1;
  }
  res = 0;
  for (int i = 0; i < u.size(); ++i) res += u[i]*v[i];
  return 0;
}

void mprint(const vector<vector<double> > &A){
  for (int i = 0; i < A.size(); ++i){
    for (int j = 0; j < A[i].size(); ++j){
      if (j) cout << setw(25) << A[i][j];
      else cout << A[i][j];
    }
    cout << endl;
  }
}

int mtranspose(const vector<vector<double> > &A, vector<vector<double> > &B){
  if (A.size() == 0 or A[0].size() == 0){
    cerr << "Null dimensions in matrix transposition" << endl;
    return -1;
  }
  B = vector<vector<double> >(A[0].size(), vector<double>(A.size()));
  for (int i = 0; i < A.size(); ++i){
    for (int j = 0; j < A[i].size(); ++j){
      B[j][i] = A[i][j];
    }
  }
}

int mproduct(const vector<vector<double> > &A, const vector<vector<double> > &B, vector<vector<double> > &C){
  if (A.size() == 0 or A[0].size() == 0 or A[0].size() != B.size() or B.size() == 0){
    cerr << "Wrong or null dimensions in matrix multiplication" << endl;
    return -1;
  }
  C = vector<vector<double> >(A.size(), vector<double>(B[0].size()));
  for (int j = 0; j < B[0].size(); ++j){
    vector<double> column(B.size());
    for (int i = 0; i < B.size(); ++i) column[i] = B[i][j]; 
    for (int i = 0; i < A.size(); ++i) sproduct(column, A[i], C[i][j]);
  }
  return 0;
}

int sistema(vector<vector<double> > &a, vector<double> &x, const vector<double> &b, int n, double tol){
    vector<int> p(n);
    for (int i = 0; i < n; ++i) p[i] = i;
    vector<vector<double> > copA = a;
    int r = lu(a, n, p, tol);    
    
    if (r != 0) resol(a, x, b, n, p);
    return r;
}


int mtrace(const vector<vector<double> > &A, double &res){
  if (A.size() == 0 or A.size() != A[0].size()){
    cerr << "Null or non-square dimensions in matrix trace" << endl;
    return -1;
  }
  res = 0;
  for (int i = 0; i < A.size(); ++i) res += A[i][i];
}

int mdet(const vector<vector<double> > &A, double &res, double tol){
  if (A.size() == 0 or A.size() != A[0].size()){
    cerr << "Null or non-square dimensions in matrix determinant" << endl;
    return -1;
  }
  vector<vector<double> > copA = A;
  vector<int> perm(copA.size());
  for (int i = 0; i < perm.size(); ++i) perm[i] = i;
  int r = lu(copA, copA.size(), perm, tol);
  res = 0;
  if (r == 0) return -1;
  res = r;
  for (int i = 0; i < copA.size(); ++i) res *= copA[i][i];
  return 0;
}

int minv(const vector<vector<double> > &A, vector<vector<double> > &Ainv, const double tol){
  if (A.size() == 0 or A.size() != A[0].size()){
    cerr << "Null or non-square dimensions in matrix inversion" << endl;
    return -1;
  }
  int n = A.size();
  vector<vector<double> > copA = A;
  Ainv = vector<vector<double> >(n, vector<double>(n));
  vector<int> perm(copA.size());
  for (int i = 0; i < n; ++i) perm[i] = i;
  int r = lu(copA, n, perm, tol);
  if (r == 0) return -1;
  for (int j = 0; j < n; ++j){
    vector<double> b(n, 0), x;
    b[j] = 1;
    resol(copA, x, b, n, perm);
    for (int i = 0; i < n; ++i) Ainv[i][j] = x[i];
  }
  
  return 0;
}