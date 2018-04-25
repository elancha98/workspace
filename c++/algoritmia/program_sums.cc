#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> elements;
vector<bool> taken;
int n, s;

bool escribir() {
    cout << "{";
    bool first = true;
    for (int i = 0; i < n; i++) {
        if (taken[i]) {
          if (first)
            first = false;
          else
            cout << ",";
          cout << elements[i];
        }
    }
    cout << "}" << endl;
    return true;
}

bool f(int i, int sum) {
    if (sum > s or sum+(n-i)*elements[n-1] < s)
      return false;
    if (i == n) {
        if (sum == s)
          return escribir();
        return false;
    }
    taken[i] = true;
    f(i+1, sum+elements[i]);
    taken[i] = false;
    f(i+1, sum);
    return false;
}

int main() {
    cin >> s >> n;
    taken = vector<bool>(n, 0);
    elements = vector<int>(n, 0);
    for (int i = 0; i < n; i++)
      cin >> elements[i];
    sort(elements.begin(), elements.end());
    f(0, 0);
    return 0;
}
