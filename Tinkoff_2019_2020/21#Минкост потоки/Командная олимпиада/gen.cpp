#include <bits/stdc++.h>

using namespace std;

int main() {
    srand(time(nullptr));
    freopen("input.txt", "w", stdout);
    int n = 5;
    vector<int> v(n + n);
    for (int i = 0; i < n + n; ++i)
        v[i] = i / 2;
    random_shuffle(v.begin(), v.end());
    cout << n << '\n';
    for (auto x : v)
        cout << x + 1 << ' ';
    cout << '\n';
}
