#include <bits/stdc++.h>

using namespace std;

const int SZ = 230;

map<pair<int, int>, vector<int>> hashs;

int good(string s, int le, int re, int k) {
    vector<int> z(s.size());
    int l = 0, r = 0;
    int ans = 0;
    for (int i = 1; i < s.size(); ++i) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
        }
        while (s[z[i] + i] == s[z[i]])
            ++z[i];
        if (i + z[i] > r + 1) {
            r = i + z[i] - 1;
            l = i;
        }
        if (z[i] == k && le <= i - k - 1 && i - 1 <= re)
            ++ans;
    }
    return ans;
}

const long long MOD = 1e9 + 21, P = 31;

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    string text;
    cin >> text;
    for (int i = 0; i < text.size(); ++i) {
        long long has = 0;
        for (int j = 0; j + i < min((int)text.size(), i + SZ); ++j) {
            has = (has * P + (long long)(text[i + j] - 'a' + 1)) % MOD;
            hashs[{j + 1, has}].push_back(i);
        }
    }
    int n;
    cin >> n;
    for (int GG = 0; GG < n; ++GG) {
        int l, r;
        string t;
        cin >> l >> r >> t;
        --l;
        if (t.size() > SZ) {
            cout << good(t + '#' + text, l, r, t.size()) << '\n';
        } else {
            long long has = 0;
            for (auto x : t)
                has = (has * P + (long long)(x - 'a' + 1)) % MOD;
            auto beg = hashs[{t.size(), has}].begin(), endd = hashs[{t.size(), has}].end();
            auto it1 = lower_bound(beg, endd, l), it2 = lower_bound(beg, endd, r);
            cout << (int)(it2 - it1) << '\n';
        }
    }
    return 0;
}
