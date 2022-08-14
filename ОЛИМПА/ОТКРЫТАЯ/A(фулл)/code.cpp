#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n, a, x, m;
    cin >> n >> a >> x >> m;
    cout << max(0ll, ((n * a - x) / m)) << '\n';
    return 0;
}
