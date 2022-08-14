#include <bits/stdc++.h>

using namespace std;

vector<int> z_function(string &s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (s[i + z[i]] == s[z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r + 1) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    z[0] = n;
    return z;
}

int main() {
    string s;
    cin >> s;
    vector<int> v = z_function(s);
    for (auto x : v) {
        cout << x << " ";
    }
}
