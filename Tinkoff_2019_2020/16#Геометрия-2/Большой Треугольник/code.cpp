#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    long long S;
    cin >> n >> S;
    S += S;
    vector<long long> X(n), Y(n);
    for (int i = 0; i < n; ++i) {
        cin >> X[i] >> Y[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long dx = X[j] - X[i], dy = Y[j] - Y[i];
            for (int k = j + 1; k < n; ++k) {
                long long cur = (X[k] - X[i]) * dy - (Y[k] - Y[i]) * dx;
                if (cur < 0)
                    cur = -cur;
                if (cur == S) {
                    cout << "Yes\n";
                    cout << X[i] << ' ' << Y[i] << '\n' << X[j] << ' ' << Y[j] << '\n' << X[k] << ' ' << Y[k] << '\n';
                    exit(0);
                }
            }
        }
    }
    cout << "No\n";
    return 0;
}
