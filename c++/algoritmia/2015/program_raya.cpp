#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<int> table;
int n, m;

void write() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (table[i*m+j] == 1)
        cout << 'X';
      else if (table[i*m+j] == 0)
        cout << 'O';
      else
        cout << '.';
    }
    cout << endl;
  }
  cout << "----------" << endl;
}

pair<bool, bool> check(int i) {
  int fila = i/m;
  int col = i%m;
  bool valid_x = true, valid_o = true;
  if (fila > 1) {
    valid_x = valid_x and not (table[(fila-1)*m+col] and table[(fila-2)*m+col]);
    valid_o = valid_o and (table[(fila-1)*m+col] or table[(fila-2)*m+col]);
  }
  if (col > 1) {
    valid_x = valid_x and not (table[i-1] and table[i-2]);
    valid_o = valid_o and (table[i-1] or table[i-2]);
  }
  return make_pair(valid_o, valid_x);
}

void f(int i) {
  if (i == n*m)
    return write();

  pair<bool, bool> valid = check(i);

  if (table[i] >= 0) {
    if (table[i] and valid.second)
      return f(i+1);
    if ((not table[i]) and valid.first)
      return f(i+1);
      //cout << "DESCARTED:" << endl;
      //write();
    return;
  }

  if (valid.first) {
    table[i] = 0;
    f(i+1);
  }
  if (valid.second) {
    table[i] = 1;
    f(i+1);
  }

  table[i] = -1;
}

void read_table() {
  char c;
  int co = 0;
  while (co < n*m) {
    cin >> c;
    if (c == 'X')
      table[co++] = 1;
    if (c == 'O')
      table[co++] = 0;
    if (c == '.')
      table[co++] = -1;
  }
}

int main() {
  while (cin >> n >> m) {
    table = vector<int>(n*m);
    read_table();
    f(0);
    cout << "********************" << endl;
  }
}
