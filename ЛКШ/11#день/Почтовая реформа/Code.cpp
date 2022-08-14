#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50000;

int path_id[MAXN], path_num[MAXN], sz[MAXN], h[MAXN], d[MAXN], anc[MAXN];

vector<int> g[MAXN];

vector<vector<int>> ways;

vector<int> top;

struct segtree {
    int lb, rb, mid, val;
    segtree *l, *r;
    segtree(int lb_, int rb_) {
        lb = lb_;
        rb = rb_;
        val = 1;
        mid = (lb + rb) >> 1;
        if (rb - lb != 1) {
            l = new segtree(lb, mid);
            r = new segtree(mid, rb);
        }
    }
    void upd(int pos, int x) {
        if (lb + 1 == rb) {
            val = x;
            return;
        }
        if (pos < mid) {
            l->upd(pos, x);
        } else {
            r->upd(pos, x);
        }
        val = max(l->val, r->val);
    }
    int mx(int ll, int rr) {
        if (ll >= rb || rr <= lb) {
            return 1;
        }
        if (ll <= lb && rb <= rr) {
            return val;
        }
        return max(l->mx(ll, rr), r->mx(ll, rr));
    }
};

vector<segtree*> segtres;

void dfs(int v, int p = -1, int deep = 0) {
    d[v] = deep;
    sz[v] = 1;
    anc[v] = p;
    pair<int, int> umax = {-1, -1};
    for (auto x : g[v]) {
        if (x == p) {
            continue;
        }
        dfs(x, v, deep + 1);
        sz[v] += sz[x];
        umax = max(umax, {sz[x], x});
    }
    if (umax.first == -1) {
        path_num[v] = ways.size();
        path_id[v] = 0;
        top.push_back(v);
        vector<int> tmp = {v};
        ways.push_back(tmp);
    } else {
        path_num[v] = path_num[umax.second];
        path_id[v] = path_id[umax.second] + 1;
        ways[path_num[v]].push_back(v);
        top[path_num[v]] = v;
    }
}

int max_on_way(int a, int b) {
    int ans = 1;
    while (path_num[a] != path_num[b]) {
        int pa = top[path_num[a]], pb = top[path_num[b]];
        if (d[pa] < d[pb]) {
            swap(a, b);
            swap(pa, pb);
        }
        int way_num = path_num[a];
        int local = segtres[way_num]->mx(path_id[a], ways[way_num].size());
        ans = max(ans, local);
        a = top[way_num];
        a = anc[a];
    }
    if (d[a] < d[b]) {
        swap(a, b);
    }
    int local = segtres[path_num[a]]->mx(path_id[a], path_id[b] + 1);
    return max(local, ans);
}

int f(int v) {
    if (v == 1) {
        return v;
    }
    return f((v + 1) >> 1) << 1;
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0);
    for (int i = 0; i < ways.size(); ++i) {
        segtree *tmp = new segtree(0, f(ways[i].size()));
        for (int j = 0; j < ways[i].size(); ++j) {
            tmp->upd(path_id[ways[i][j]], h[ways[i][j]]);
        }
        segtres.push_back(tmp);
    }
    int m;
    cin >> m;
    for (int ch = 0; ch < m; ++ch) {
        char type;
        cin >> type;
        if (type == '?') {
            int a, b;
            cin >> a >> b;
            --a;
            --b;
            cout << max_on_way(a, b) << '\n';
        } else {
            int i, higth;
            cin >> i >> higth;
            --i;
            h[i] = higth;
            segtres[path_num[i]]->upd(path_id[i], h[i]);
        }
    }
    return 0;
}
