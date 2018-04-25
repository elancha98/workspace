#ifndef MATRICES_HH
#define MATRICES_HH
#include <vector>
#include <cmath>

using namespace std;

//fa la descomposicio lu de la matriu a sobre ella mateixa
int lu(vector<vector<double> > &a, int n, vector<int> &perm, double tol);

//resol una matriu a que conte els termes de lu de forma compacta amb termes independents b
void resol(const vector<vector<double> > &a, vector<double> &x, const vector<double> &b, int n, const vector<int> &perm);

//resol el sistema ax = b, modificant a
int sistema(vector<vector<double> > &a, vector<double> &x, const vector<double> &b, int n, double tol);

//escriu per cout la matriu A
void mprint(const vector<vector<double> > &A);

//producte escalar d'un vector u amb un vector v
int sproduct(const vector<double> &u, const vector<double> &v, double &res);

//Fa B=At
int mtranspose(const vector<vector<double> > &A, vector<vector<double> > &B);

//Fa C = AB
int mproduct(const vector<vector<double> > &A, const vector<vector<double> > &B, vector<vector<double> > &C);

//Fa res = tr(A)
int mtrace(const vector<vector<double> > &A, double &res);

//Fa res = det(A), res = 0 si fent gauss es troba un pivot < tol
int mdet(const vector<vector<double> > &A, double &res, double tol);

//Fa Ainv = A^-1, retorna -1 si fent gauss es troba un pivot < tol
int minv(const vector<vector<double> > &A, vector<vector<double> > &Ainv, double tol);

#endif