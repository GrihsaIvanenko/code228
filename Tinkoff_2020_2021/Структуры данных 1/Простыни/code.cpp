#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1 << 19, MAXY = 1 << 30;

const int SZ = MAXN * 13;

vector<int> g[MAXN], my_balls[MAXN];

set<int> cash[MAXN];

int L[SZ], R[SZ], val[SZ], pos = 1, previ[MAXN], lef[MAXN], righ[MAXN], color[MAXN], y[MAXN], mem[MAXN], used[MAXN], ans[MAXN], timer = 0;

void make_push(int v) {
    if (!L[v])
        L[v] = pos++;
    if (!R[v])
        R[v] = pos++;
    assert(pos < SZ);
    if (val[v])
        val[L[v]] = val[R[v]] = val[v];
    val[v] = 0;
}

void col(int l, int r, int c, int lb = 0, int rb = MAXY, int v = 0) {
    if (l <= lb && rb <= r) {
        val[v] = c;
        return;
    }
    if (r <= lb || rb <= l) {
        return;
    }
    make_push(v);
    int mid = (lb + rb) >> 1;
    col(l, r, c, lb, mid, L[v]);
    col(l, r, c, mid, rb, R[v]);
}

int get(int pos, int lb = 0, int rb = MAXY, int v = 0) {
    if (val[v])
        return val[v];
    int mid = (lb + rb) >> 1;
    if (pos < mid)
        return get(pos, lb, mid, L[v]);
    return get(pos, mid, rb, R[v]);
}

void dfs(int v) {
    used[v] = 1;
    int cur = -1;
    for (auto x : g[v]) {
        if (!used[x])
            dfs(x);
        if (cur == -1 || cash[mem[cur]].size() < cash[mem[x]].size())
            cur = x;
    }
    if (cur == -1) {
        mem[v] = timer++;
    } else {
        mem[v] = mem[cur];
        for (auto x : g[v])
            if (x != cur)
                for (auto y : cash[mem[x]])
                    cash[mem[v]].insert(y);
    }
    for (auto x : my_balls[v])
        cash[mem[v]].insert(x);
    ans[v] = cash[mem[v]].size();
}

void solve() {
    val[0] = -1;
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> events;
    events.reserve(n + n + m);
    for (int i = 0; i < n; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        events.push_back({a, i + 1 - MAXN - MAXN});
        events.push_back({c, i + 1});
        lef[i] = b - 1;
        righ[i] = d;
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        events.push_back({a, i - MAXN});
        color[i] = c;
        y[i] = b - 1;
    }
    sort(events.begin(), events.end());
    for (auto x : events) {
        if (x.second > 0) {
            col(lef[x.second - 1], righ[x.second - 1], previ[x.second - 1]);
        }  else if (x.second + MAXN >= 0) {
            int id = x.second + MAXN;
            int in = get(y[id]);
            if (in != -1)
                my_balls[in - 1].push_back(color[id]);
        } else {
            int id = x.second + MAXN + MAXN;
            int col_now = get(lef[id - 1]);
            previ[id - 1] = col_now;
            if (col_now != -1)
                g[col_now - 1].push_back(id - 1);
            col(lef[id - 1], righ[id - 1], id);
        }
    }
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs(i);
    for (int i = 0; i < n; ++i)
        cout << ans[i] << '\n';
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
