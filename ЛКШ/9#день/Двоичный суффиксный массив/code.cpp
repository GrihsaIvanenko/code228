#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2;

vector<int> suf_arr(vector<int> s) {
    vector<int> tmp[MAXN], sor, cls(s.size() + 1);
    for (int i = 0; i < s.size(); ++i) {
        tmp[s[i]].push_back(i);
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

int solve(int n, vector<int> &good) {
    vector<int> ans(n);
    bool was = 0, imba = 1;
    int lst = 0;
    for (int i = 0; i < n; ++i) {
        if (good[i] + i == n && imba) {
            lst = i + 1;
            continue;
        } else {
            imba = 0;
        }
        if (good[i] + lst == n) {
            was = 1;
        }
        ans[good[i] - 1] = was;
    }
    vector<int> better = suf_arr(ans);
    for (int i = 0; i < n; ++i) {
        if (good[i] - better[i] != 1) {
            cout << "Error\n";
            return 0;
        }
    }
    for (auto x : ans) {
        cout << x;
    }
    return 1;
}


int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    solve(n, v);
    return 0;
}
