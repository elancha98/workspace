#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<long> > perm(26, vector<long>(26, -1));
long n, m;

long f(int n, int m) {
  if (n % 2 == 0)
    return 0;
  if (n < 5)
    return m;
  long aux = f((n-5)/2, m);
  return f(n-2, m) + aux*aux;
}

int main() {
  while (cin >> n >> m) {
    cout << f(n, m) << endl;
  }
}
