#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101;

vector<int> suf_arr(vector<int> &s) {
    vector<int> tmp[MAXN], sor, cls(s.size());
    for (int i = 0; i < s.size(); ++i) {
        tmp[s[i]].push_back(i);
    }
    int cls_now = 0;
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
    while ((1 << len) < s.size()) {
        vector<int> cls_pos(cls_now), new_pos(s.size()), new_cls(s.size());
        for (int i = 1; i < s.size(); ++i) {
            if (cls[sor[i]] != cls[sor[i - 1]]) {
                cls_pos[cls[sor[i]]] = i;
            }
        }
        for (int i = 0; i < s.size(); ++i) {
            int mate = ((sor[i] - (1 << len) + s.size() + s.size()) % s.size());
            new_pos[mate] = cls_pos[cls[mate]]++;
        }
        for (int i = 0; i < s.size(); ++i) {
            sor[new_pos[i]] = i;
        }
        for (int i = 1; i < s.size(); ++i) {
            int matei = (sor[i] + (1 << len)) % s.size();
            int matei1 = (sor[i - 1] + (1 << len)) % s.size();
            if (cls[sor[i]] != cls[sor[i - 1]] || cls[matei] != cls[matei1]) {
                new_cls[sor[i]] = new_cls[sor[i - 1]] + 1;
                cls_now = new_cls[sor[i]] + 1;
            } else{
                new_cls[sor[i]] = new_cls[sor[i - 1]];
            }
        }
        cls = new_cls;
        ++len;
    }
    /*vector<pair<int, int>> imba(s.size());
    for (int i = 0; i < s.size(); ++i){
        imba[i] = {cls[sor[i]], sor[i]};
    }
    sort(imba.begin(), imba.end());
    for (int i = 0; i < s.size(); ++i){
        sor[i] = imba[i].second;
    }*/
    return sor;
}

int n;

void solve() {
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    /*if (cyclic){
        long long ans = v.size();

    }*/
    vector<int> p = suf_arr(v);
    vector<int> revp(n);
    for (int i = 0; i < n; ++i) {
        revp[p[i]] = i;
    }
    vector<int> lcp(n);
    int k = 0;
    long long ans = 0;
    bool was = false;
    /*for (int i = 0; i < p.size(); ++i){
        cout << i << " " << p[i] << ": ";
        for (int j = p[i]; j < p[i] + n; ++j){
            cout << v[j % n] << " ";
        }
        cout << endl;
    }*/
    for (int i = 0; i < n; ++i) {
        int x = revp[i];
        k = max(k - 1, 0);
        if (x == n - 1) {
            continue;
        }
        //cout << i << " " << x << " " << p[x + 1] << endl;
        while (v[(i + k) % n] == v[(p[x + 1] + k) % n] && k < n) {
            ++k;
        }
        //cout << k << endl;
        lcp[x] = k;
        if (!was && revp[i + 1] > revp[p[x + 1] + 1]) {
            k = 0;
            was = true;
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        ans += (long long)lcp[i];
    }
    cout << ans << endl;
}

int main() {
    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }
        solve();
    }
    return 0;
}

