#include <bits/stdc++.h>

using namespace std;

int pr(string &s) {
     int n = s.size();
     vector<int> p(n);
     for (int i = 1; i < n; ++i) {
        int cur = p[i - 1];
        while (cur != -1 && s[cur] != s[i])
            if (cur == 0)
                cur = -1;
            else
                cur = p[cur - 1];
        p[i] = cur + 1;
     }
     return p.back();
}

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    string s;
    cin >> s;
    int n = s.size();
    int t = n - pr(s);
    if (n % t == 0) {
        cout << n / t << '\n';
    } else {
        cout << 1 << '\n';
    }
    return 0;
}
