#include <iostream>

using namespace std;

int main() {
    int p = 10;
    int *p1 = &p;
    cout << p << " | " << *p1 << " | " << p1 << endl;
    delete p1;
    cout << (p1 == NULL) << endl;
    //cout << p1 << NULL << endl;
}
