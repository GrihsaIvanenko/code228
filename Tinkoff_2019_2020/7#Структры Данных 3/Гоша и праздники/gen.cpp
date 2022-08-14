#include <bits/stdc++.h>

using namespace std;

int main() {
    srand(time(nullptr));
    int n = rand() % 5000 + 1;
    cout << n << endl;
    for (int i = 1; i < n; ++i) {
        cout << rand() % (i) + 1 << " " << i + 1 << " " << rand() << endl;
    }
    int m = rand() % 5000 + 1;
    cout << m << endl;
    for (int i = 0; i < m; ++i) {
        cout << rand() % n + 1 << " " << rand() << endl;
    }
}
