#include <bits/stdc++.h>

using namespace std;

int main() {
    srand(time(nullptr));
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n = rand() % 3 + 3, m = rand() % 3 + 3;
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; ++i) {
        int a = rand() % 5, b = rand() % 5;
        cout << min(a, b) << " " << max(a, b) << '\n';
    }
    for (int i = 0; i < m; ++i) {
        int a = rand() % 5, b = rand() % 5;
        cout << min(a, b) << " " << max(a, b) << '\n';
    }
    return 0;
}
