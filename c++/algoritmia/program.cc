#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

vector<string> a;

vector<queue<string> > radix(26);
queue<string> proc;

void radix_it(int i) {
    while (!proc.empty()) {
        string s = proc.front();
        proc.pop();

        radix[s[i] - 'a'].push(s);
    }
    for (int i = 0; i < 26; i++) {
        while (!radix[i].empty()) {
            proc.push(radix[i].front());
            radix[i].pop();
        }
    }
}

void radix_f(int i) {
    for (int j = i; j >= 0; j--) {
        radix_it(j);
    }
}

int main() {
    string s, t;
    getline(cin, s);

    istringstream ss(s);
    while (ss >> t) {
        proc.push(t);
    }

    radix_f(2);

    bool first = true;
    while (!proc.empty()) {
        if (first)
            first = false;
        else
            cout << ' ';
        cout << proc.front();
        proc.pop();
    }
    cout << endl;
    return 0;
}
