#include <bits/stdc++.h>

using namespace std;

const int MAXN = 131072 * 2;

int seg[MAXN + MAXN], push[MAXN + MAXN];

void make_push(int v) {
    push[v + v] += push[v];
    push[v + v + 1] += push[v];
    push[v] = 0;
}

void update(int v) {
    seg[v] = max(seg[v + v] + push[v + v], seg[v + v + 1] + push[v + v + 1]);
}

void add(int le, int re, int lb = 0, int rb = MAXN, int v = 1) {
    if (le >= re)
        return;
    if (le <= lb && rb <= re) {
        ++push[v];
        return;
    }
    if (re <= lb || rb <= le)
        return;
    make_push(v);
    int mid = (lb + rb) >> 1;
    add(le, re, lb, mid, v + v);
    add(le, re, mid, rb, v + v + 1);
    update(v);
}

pair<int, pair<int, int>> v1[MAXN + MAXN];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        v1[i].second = {0, i};
        cin >> v1[i].first;
    }
    for (int i = 0; i < n; ++i) {
        v1[i + n].second = {1, i};
        cin >> v1[i + n].first;
    }
    sort(v1, v1 + n + n);
    vector<int> ans(n);
    for (int i = n + n - 1; i >= 0; --i) {
        auto x = v1[i];
        if (x.second.first)
            add(0, x.second.second + 1);
        else
            add(x.second.second + 1, MAXN);
        int kolvo = seg[1] + push[1];
        if (kolvo <= n && kolvo > 0)
            ans[kolvo - 1] = max(ans[kolvo - 1], x.first);
    }
    for (auto x : ans)
        cout << x << ' ';
    cout << '\n';
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
