#include <iostream>
#include <vector>

using namespace std;

int main() {
  double d,v;
  
  char t;
  cout << "Holi" << endl;

  cout << "continue" << endl;
  return 0;
}

void moveTo(double x, double y, vector<double>& actual, vector<string>& eq, bool rel=false) {
  if (rel) {
    actual[0] += x;
    actual[1] += y;
  } else {
    actual[0] = x;
    actual[1] = y;
  }
}
