#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> elements;
vector<bool> taken;
int n, co = 0;

void chess_write() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < elements[i]; j++)
      cout << '.';
    cout << 'Q';
    for (int j = elements[i]+1; j < n; j++)
      cout << '.';
    cout << endl;
  }
  co++;
}

bool check_perm(int i, int j) {
  for (int k = 0; k < i; k++) {
    if (abs(elements[k]-j) == i-k)
      return false;
  }
  return true;
}

bool f(int i) {
    if (i == n-1) {
        for (int j = 0; j < n; j++) {
          if ((not taken[j]) and check_perm(i,j)) {
            elements[i] = j;
            chess_write();
            return true;
          }
        }
        return false;
    }

    for (int j = 0; j < n; j++) {
      if ((not taken[j]) and check_perm(i, j)) {
        taken[j] = true;
        elements[i] = j;
        if ( f(i+1) )
          return true;
        taken[j] = false;
      }
    }
    return false;
}

int main() {
    cin >> n;
    taken = vector<bool>(n, 0);
    elements = vector<int>(n, 0);
    if (n > 3)
      f(0);
    if (co == 0)
      cout << "NO SOLUTION" << endl;
    return 0;
}
