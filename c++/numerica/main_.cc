#include <bits/stdc++.h>
#include "matrices.hh"

using namespace std;


const double tol = 1e-12;

int main(int argc, char *argv[]) {
    ifstream in;
    ofstream out;
    if (argc > 3) {
        cerr << "Usage is either " << argv[0] << " or " << " infile [ofile]" << endl;
        exit(5);
    }
    if (argc >= 2) in.open(argv[1]);
    else  in.open("lectura.dat");
    
    if (in.fail()) {
        cerr << "Error opening input file, expected either parameter or input file lectura.dat" << endl;
        exit(10);
    }
    
    if (argc == 3) out.open(argv[2]);
    else out.open("sortida.dat");

    if (out.fail()) {
        cerr << "Error opening output file" << endl;
        exit(20);
    }
    
    int m, n, k;
    in >> n >> m;
    vector<vector<double> > A(n, vector<double>(n, 0)), copA;
    vector<double> b(n), x;
    
    for (int i = 0; i < m; i++) {
        int f, c;
        in >> f >> c;
        in >> A[f][c];
    }
    
    copA = A;
    
    in >> k;
    for (int i = 0; i < k; ++i) {
        int f;
        in >> f;
        in >> b[f];
    }
    in.close();
    
    if (sistema(A, x, b, n, tol) == 0) {
        out << "Matriu singular" << endl;
    }
    else {
        out.setf(ios::fixed);
        out.precision(15);
        for (int i = 0; i < n; ++i) out << i << " " << x[i] << endl;
    
        double norma_dif = 0.;
        for (int i = 0; i < n; ++i){
            double res = -b[i];
            for (int j = 0; j < n; ++j) res += x[j]*copA[i][j];
            norma_dif += res*res;
        }
        
        cout.setf(ios::fixed);
        cout.precision(15);
        cout << "||Ax-b|| = " << sqrt(norma_dif) << endl;
    }
    out.close();
}
