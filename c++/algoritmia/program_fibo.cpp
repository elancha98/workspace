#include <iostream>
#include <vector>

using namespace std;

vector<long long> fibo(1001, -1);
long long n, m;

long f(int i) {
  if (fibo[i] == -1) {
    fibo[i] = (f(i-1) + f(i-2));//%((long) 10e8);
  }
  return fibo[i];
}

int main() {
  fibo[0] = 0;
  fibo[1] = 1;
  while (cin >> n >> m) {
    cout << f(n) << endl;
  }
}
