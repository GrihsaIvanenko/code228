#include <bits/stdc++.h>

using namespace std;

const int MAXN = 26;

vector<int> suf_arr(string s) {
    vector<int> tmp[MAXN], sor, cls(s.size() + 1);
    for (int i = 0; i < s.size(); ++i) {
        tmp[s[i] - 'a'].push_back(i);
    }
    sor.push_back(s.size());
    int cls_now = 1;
    for (int i = 0; i < MAXN; ++i) {
        if (tmp[i].size() != 0) {
            for (auto x : tmp[i]) {
                sor.push_back(x);
                cls[x] = cls_now;
            }
            tmp[i].clear();
            ++cls_now;
        }
    }

    int len = 0;
    while ((1 << len) < s.size() + 1) {
        vector<int> cls_pos(cls_now), new_pos(s.size() + 1), new_cls(s.size() + 1);
        for (int i = 1; i < s.size() + 1; ++i) {
            if (cls[sor[i]] != cls[sor[i - 1]]) {
                cls_pos[cls[sor[i]]] = i;
            }
        }
        for (int i = 0; i < s.size() + 1; ++i) {
            int mate = ((sor[i] - (1 << len) + s.size() + s.size() + 2) % (s.size() + 1));
            new_pos[mate] = cls_pos[cls[mate]]++;
        }
        for (int i = 0; i < s.size() + 1; ++i) {
            sor[new_pos[i]] = i;
        }
        for (int i = 1; i < s.size() + 1; ++i) {
            int matei = (sor[i] + (1 << len)) % (s.size() + 1);
            int matei1 = (sor[i - 1] + (1 << len)) % (s.size() + 1);
            if (cls[sor[i]] != cls[sor[i - 1]] || cls[matei] != cls[matei1]) {
                new_cls[sor[i]] = new_cls[sor[i - 1]] + 1;
                cls_now = new_cls[sor[i]] + 1;
            } else {
                new_cls[sor[i]] = new_cls[sor[i - 1]];
            }
        }
        cls = new_cls;
        ++len;
    }
    reverse(sor.begin(), sor.end());
    sor.pop_back();
    reverse(sor.begin(), sor.end());
    return sor;
}

void solve() {
    string s;
    cin >> s;
    vector<int> sf = suf_arr(s);
    vector<int> lcp(s.size()), revp(s.size());
    for (int i = 0; i < sf.size(); ++i) {
        revp[sf[i]] = i;
    }
    s.push_back('$');
    int k = 0;
    for (int i = 0; i < s.size() - 1; ++i) {
        int x = revp[i];
        k = max(k - 1, 0);
        if (x == s.size() - 2) {
            continue;
        }
        while (s[(i + k) % s.size()] == s[(sf[x + 1] + k) % s.size()]) {
            ++k;
        }
        lcp[x + 1] = k;
    }
    long long kk;
    cin >> kk;
    for (int i = 0; i < s.size() - 1; ++i) {
        if (s.size() - 1 - sf[i] - lcp[i] >= kk) {
            int st = sf[i];
            kk += lcp[i];
            for (; kk > 0; --kk) {
                cout << s[st++];
            }
            return;
        }
        kk -= s.size() - 1 - sf[i] - lcp[i];
    }
    int pose = sf.back();
    while (s[pose] != '$') {
        cout << s[pose++];
    }
}

int main() {
    solve();
    return 0;
}
