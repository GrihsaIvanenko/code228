#include <bits/stdc++.h>

using namespace std;

const int MAXL = 150;

vector<int> suff_arr(string s) {
    int n = s.size();
    vector<int> cls(n);
    vector<int> new_cls(n);
    vector<int> now(n);
    vector<int> become(n);
    vector<int> pos_cl(n);
    vector<vector<int>> beg(MAXL);
    for (int i = 0; i < n; ++i) {
        beg[s[i]].push_back(i);
    }
    int it = 0, cl = 0;
    for (int i = 0; i < MAXL; ++i) {
        for (auto x : beg[i]) {
            now[it++] = x;
            cls[x] = cl;
        }
        if (beg[i].size() != 0) {
            ++cl;
        }
    }
    int len = 0;
    vector<int> to_return;
    while ((1 << len) < n) {
        pos_cl[0] = 0;
        for (int i = 1; i < n; ++i) {
            if (cls[now[i]] != cls[now[i - 1]]) {
                pos_cl[cls[now[i]]] = i;
            }
        }
        for (int i = 0; i < n; ++i) {
            int mate = (now[i] - (1 << len) + n) % n;
            become[mate] = pos_cl[cls[mate]]++;
        }
        for (int i = 0; i < n; ++i) {
            now[become[i]] = i;
        }
        new_cls[now[0]] = 0;
        for (int i = 1; i < n; ++i) {
            int mate = (now[i] + (1 << len)) % n;
            int lmt = (now[i - 1] + (1 << len)) % n;
            if (cls[now[i]] != cls[now[i - 1]] || cls[mate] != cls[lmt]) {
                new_cls[now[i]] = new_cls[now[i - 1]] + 1;
            } else{
                new_cls[now[i]] = new_cls[now[i - 1]];
            }
        }
        if ((1 << len) * 2 >= s.size()) {
            to_return.push_back(now[0]);
            for (int i = 1; i < n; ++i) {
                if (new_cls[now[i]] != new_cls[to_return.back()]) {
                    to_return.push_back(now[i]);
                }
            }
            return to_return;
        }
        cls = new_cls;
        ++len;
    }
    return now;
}

void solve() {
    string s;
    cin >> s;
    vector<int> ans = suff_arr(s);
    int k;
    cin >> k;
    --k;
    if (k >= ans.size()) {
        cout << "IMPOSSIBLE";
        return;
    }
    for (int i = ans[k]; i < ans[k] + s.size(); ++i) {
        cout << s[i % s.size()];
    }
}

int main() {
    solve();
    return 0;
}
