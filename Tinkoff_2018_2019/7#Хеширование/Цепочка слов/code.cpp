#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250000;

const long long mod = 1e9 + 3, h = 27;

long long p[MAXN];

vector<vector<long long>> hashs;

bool check(int l, int n) {
    if (hashs[l].size() >= hashs[n].size() || hashs[l].back() != hashs[n][hashs[l].size() - 1]) {
        return false;
    }
    return true;
}

int main() {
    p[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        p[i] = (p[i - 1] * h) % mod;
    }
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    hashs.reserve(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        hashs.push_back(vector<long long>(s.size()));
        for (int j = 0; j < s.size(); ++j) {
            if (j == 0) {
               hashs[i][j] = s[j] - 'a';
            } else{
                long long add = s[j] - 'a';
                hashs[i][j] = (hashs[i][j - 1] * h + add) % mod;
            }
        }
    }
    cin >> n;
    int ans_l = 0, ans_r = 0;
    int last_id = 0;
    int last_str = -1;
    for (int i = 0; i < n; ++i) {
        int now;
        cin >> now;
        --now;
        if (i == 0) {
           last_str = now;
           continue;
        }
        if (!check(last_str, now)) {
            last_id = i;
        }
        last_str = now;
        if (i - last_id > ans_r - ans_l) {
           ans_l = last_id;
           ans_r = i;
        }
    }
    cout << ans_l + 1 << ' ' << ans_r + 1 << '\n';
    return 0;
}
