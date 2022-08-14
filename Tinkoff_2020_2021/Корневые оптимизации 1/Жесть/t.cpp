#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("output.txt", "w", stdout);
    int n = 500000;
    cout << n << "\n";
    for (int i = 0; i < n; ++i)
        cout << rand() * 1000 + rand() << ' ';
    cout << '\n';
    int q = n;
    cout << q << '\n';
    for (int i = 0; i < q; ++i) {
        cout << "get " << rand() << " " << n - rand() << " " << rand() * 1000 + rand() << '\n';
    }
    return 0;
}
