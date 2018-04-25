#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> elements;
vector<bool> taken;
int n, k;

void escribir() {
    cout << "(";
    bool first = true;
    for (int i = 0; i < n; i++) {
        if (first)
          first = false;
        else
          cout << ",";
        cout << elements[i]+1;
    }
    cout << ")" << endl;
    return;
}

void f(int i, int inv) {
    if (inv > k)
      return;
    if (i == n-1) {
        if (inv == k) {
          for (int j = 0; j < n; j++) {
            if (not taken[j]) {
              elements[i] = j;
              return escribir();
            }
          }
        }
        return;
    }

    for (int j = 0; j < n; j++) {
      if (not taken[j]) {
        int gen_inv = 0;
        for (int k = 0; k < j; k++) {
          if (not taken[k])
            gen_inv++;
        }
        taken[j] = true;
        elements[i] = j;
        f(i+1, inv + gen_inv);
        taken[j] = false;
      }
    }
}

int main() {
    cin >> n >> k;
    taken = vector<bool>(n, 0);
    elements = vector<int>(n, 0);
    f(0, 0);
    return 0;
}
