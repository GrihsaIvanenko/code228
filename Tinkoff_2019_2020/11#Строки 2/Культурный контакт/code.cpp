#include <bits/stdc++.h>

using namespace std;

int MAXN = 5 * 1e6 + 1;

vector<vector<int>> pr_sm(26);

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

string s;

int ans = 1;

void work_with_del(int del) {
    int good[26];
    int step = 0;
    for (int i = 0; i < 26; ++i) {
        good[i] = pr_sm[i].size() / del;
        step += good[i];
    }
    bool goode = true;
    vector<int>last_ask(26, 0);
    for (int i = 0; goode && i < 26; ++i) {
        if (good[i] == 0)
            continue;
        for (int pos = 1; goode && pos * step <= s.size(); ++pos) {
            if (pr_sm[i][good[i] * pos - 1] > pos * step)
                goode = false;
        }
    }
    if (goode) {
        ans = max(ans, (int)s.size() / step);
    }
}

vector<int> dels;

void perebor_deleters(vector<pair<int, int>>& pr, int was = 1, int pos = 0) {
    if (pos == pr.size()) {
        dels.push_back(was);
        return;
    }
    perebor_deleters(pr, was, pos + 1);
    for (int i = 0; i < pr[pos].second; ++i) {
        was *= pr[pos].first;
        perebor_deleters(pr, was, pos + 1);
    }
}

void do_dich_with_it(int k) {
    vector<pair<int, int>> raschlenenie;
    for (int i = 2; i * i <= k; ++i) {
        if (k % i == 0) {
            raschlenenie.push_back({i, 0});
            while (k % i == 0) {
                ++raschlenenie.back().second;
                k /= i;
            }
        }
    }
    if (k != 1)
        raschlenenie.push_back({k, 1});
    perebor_deleters(raschlenenie);
}

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        pr_sm[s[i] - 'a'].push_back(i + 1);
    }
    int cur_t = s.size();
    for (int i = 0; i < 26; ++i)
        cur_t = gcd(cur_t, pr_sm[i].size());
    if (cur_t == s.size()) {
        cout << cur_t << '\n';
        return 0;
    }
    do_dich_with_it(cur_t);
    sort(dels.rbegin(), dels.rend());
    for (auto x : dels) {
        work_with_del(x);
        if (ans != 1) {
            cout << ans << '\n';
            return 0;
        }
    }
    cout << "1\n";
    return 0;
}
