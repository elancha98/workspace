#include <iostream>
#include <vector>

using namespace std;

vector<vector<long> > ocu(501, vector<long>(501, -1));
long n, d;



long ocupied(long n) {
  if (n <= 0)
    return 0;
  if (n <= 2)
    return 1;
  return 1 + ocupied((n-3)/2);
}

long ocupied() {
  ocu[1][0] = 1;
  ocu[2][0] = 1;
  for (int i = 3; i < 501; i++) {
    ocu[i][0] = 2 + ocupied(i-4);
  }
}

long ocupied(long n, int wall) {
  if (wall >= n-1)
    return n;
  if (ocu[n][wall] == -1) {
    long m = 0;
    for (int i = 1; i <= n/2; i++) {
      for (int j = 0; j < wall; j++) {
        long oc = ocupied(i, (wall-1)-j) + ocupied(n-i, j);
        if (oc > m)
          m = oc;
      }
    }
    ocu[n][wall] = m;
  }
  return ocu[n][wall];
}

int walls(long n, double d) {
  double m = 0.0;
  int wall = -1;
  while (m < d) {
    m = ocupied(n, ++wall)/ ((double) n);
  }
  return wall;
}

int main() {
  ocupied();
  while (cin >> n >> d) {
    cout << walls(n, d/100.0) << endl;
  }
}
