#include <iostream>
#include <functional>

using namespace std;

double test(function<double(int)> f, double a) {
    return f(a);
}

int main() {
    double x = 0.0;
    function<double(int)> f = [=](double a) { return x + a; };
    cout << test(f, 1) << " | " << x << endl;
    x = 15;
cout << test(f, 2) << " | " << x << endl;
    return 0;
}
