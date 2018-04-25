#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<bool> taken;
vector<int> elements;
int n;

void write() {
  bool first = true;
  for (int i = 0; i < n; i++) {
    if (first)
      first = false;
    else
      cout << " ";
    cout << elements[i];
  }
  cout << endl;
}

void f(int i) {
  if (i == n)
    return write();

  for (int j = 0; j < n; j++) {
    if ((not taken[j]) and (i == 0 or abs(elements[i-1]-j) > 1)) {
      taken[j] = true;
      elements[i] = j;
      f(i+1);
      taken[j] = false;
    }
  }
}

int main() {
  while(cin >> n) {
    elements = vector<int>(n);
    taken = vector<bool>(n, false);
    f(0);
    cout << "********************" << endl;
  }
}
