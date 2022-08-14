#include <bits/stdc++.h>

using namespace std;

const int MAXN = 11;

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


int main() {
    int n, m;
    cin >> n >> m;
    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    if (n == 1) {
        cout << "1\n1\n";
        cout << s[0];
        cout << '\n';
        return 0;
    }
    vector<int> sf = suf_arr(s);
    vector<int> lcp(s.size() - 1), revp(s.size());
    s.push_back(0);
    for (int i = 0; i < sf.size(); ++i) {
        revp[sf[i]] = i;
    }
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
        lcp[x] = k;
    }
    vector<int> left(n), right(n);
    vector<pair<int, int>> tmp;
    for (int i = 0; i < n - 1; ++i) {
        while (!tmp.empty() && tmp.back().first > lcp[i]) {
            right[tmp.back().second] = i;
            tmp.pop_back();
        }
        tmp.push_back({lcp[i], i});
    }
    while (!tmp.empty()) {
        right[tmp.back().second] = n - 1;
        tmp.pop_back();
    }
    for (int i = n - 1; i > -1; --i) {
        while (!tmp.empty() && tmp.back().first > lcp[i]) {
            left[tmp.back().second] = i;
            tmp.pop_back();
        }
        tmp.push_back({lcp[i], i});
    }
    while (!tmp.empty()) {
        left[tmp.back().second] = -1;
        tmp.pop_back();
    }
    int in = 1, st = 0, len = n;
    for (int i = 0; i < n - 1; ++i) {
        if (((long long)right[i] - (long long)left[i]) * (long long)lcp[i] > (long long)len * (long long)in) {
            in = right[i] - left[i];
            len = lcp[i];
            st = sf[i];
        }
    }
    cout << (long long)in * (long long)len << '\n' << len << '\n';
    for (int i = st; i < st + len; ++i) {
        cout << s[i] << " ";
    }
    cout << endl;
    return 0;
}
