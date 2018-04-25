#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> sudoku(81);
vector<vector<bool> > fil;
vector<vector<bool> > col;
vector<vector<bool> > sam;
bool written;

void write() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int index = i*9+j;
      cout << sudoku[index];
      if (j != 8)
        cout << " ";
      if (j == 2 or j == 5)
        cout << "| ";
    }
    cout << endl;
    if (i == 2 or i == 5)
      cout << "------+-------+------" << endl;
  }
  cout << endl;
  written = true;
}

void f(int i) {
  int fila = i/9;
  int colu = i%9;
  int samp = (fila/3)*3+(colu/3);

  if (i == 80) {
    if (sudoku[i] == 0) {
      bool written = false;
      for (int j = 1; j <= 9; j++) {
        if (not (fil[fila][j-1] or col[colu][j-1] or sam[samp][j-1])) {
          sudoku[i] = j;
          write();
        }
      }
      return;
    }
    write();
    return;
  }

  if (sudoku[i] != 0) {
    f(i+1);
    return;
  }

  for (int j = 1; j <= 9; j++) {
    if (not (fil[fila][j-1] or col[colu][j-1] or sam[samp][j-1])) {
      fil[fila][j-1] = true;
      col[colu][j-1] = true;
      sam[samp][j-1] = true;
      sudoku[i] = j;
      f(i+1);
      sudoku[i] = 0;
      fil[fila][j-1] = false;
      col[colu][j-1] = false;
      sam[samp][j-1] = false;
    }
  }
}

void read_sudoku() {
  char t;
  int com, c = 0;
  while (c < 81) {
    cin >> t;
    com = t - '0';
    if (com > -1 and com < 10) {
      int fila = c/9;
      int colu = c%9;
      int samp = (fila/3)*3+(colu/3);
      if (com != 0) {
        fil[fila][com-1] = true;
        col[colu][com-1] = true;
        sam[samp][com-1] = true;
      }
      sudoku[c] = com;
      c++;
    }
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    fil = vector<vector<bool> >(9, vector<bool>(9, false));
    col = vector<vector<bool> >(9, vector<bool>(9, false));
    sam = vector<vector<bool> >(9, vector<bool>(9, false));
    read_sudoku();
    written = false;
    f(0);
    if (not written)
      cout << "no solution" << endl;
    cout << "******************************" << endl;
  }
}
