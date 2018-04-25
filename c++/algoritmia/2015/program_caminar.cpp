#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

string a, b;
vector<vector<int> > cost;

int f(int i, int j) {
  if (i == -1)
    return (j+1)*3;
  if (j == -1)
    return (i+1)*3;
  if (cost[i][j] >= 0)
    return cost[i][j];
  if (a[i] == b[j]) {
    int x = i-1, y = j-1;
    while (x >= 0 and a[x] == a[i])
      x--;
    while (y >= 0 and b[y] == b[i])
      y--;
    cost[i][j] = abs(i-j+y-x)*2 + f(x, y);
  } else {
    cost[i][j] = 3 + min(f(i-1, j), f(i, j-1));
  }
  return cost[i][j];
}

int main() {
  while (cin >> a >> b) {
    cost = vector<vector<int> >(a.size(), vector<int>(b.size(), -1));
    cout << f(a.size()-1, b.size()-1) << endl;
  }
}
