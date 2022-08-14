#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200000, MAXUP = 18;

int up[MAXN][MAXUP], h[MAXN], sz[MAXN], get_id[MAXN], get_pos[MAXN], get_p[MAXN], new_id = 1;

vector<int> g[MAXN];

map<pair<int, int>, int> get_c;

void up_h(int &a, int h) {
    for (int i = MAXUP - 1; i >= 0; --i)
        if (h >= (1 << i)) {
            a = up[a][i];
            h -= (1 << i);
        }
}

int lca(int a, int b) {
    up_h(a, h[a] - min(h[a], h[b]));
    up_h(b, h[b] - min(h[a], h[b]));
    if (a == b)
        return a;
    for (int i = MAXUP - 1; i >= 0; --i)
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    return up[a][0];
}

void dfs(int v = 0, int p = 0) {
    sz[v] = 1;
    h[v] = h[p] + 1;
    up[v][0] = p;
    int mx = -1, pid = -1;
    for (int i = 0; i < g[v].size(); ++i)
        if (g[v][i] == p)
            pid = i;
    if (v != 0) {
        swap(g[v][pid], g[v].back());
        g[v].pop_back();
    }
    for (int i = 0; i < g[v].size(); ++i) {
        dfs(g[v][i], v);
        if (mx == -1 || sz[g[v][mx]] < sz[g[v][i]])
            mx = i;
        sz[v] += sz[g[v][i]];
    }
    if (mx != -1)
        swap(g[v][mx], g[v][0]);
}

void build_ways(vector<vector<int>> &ways, int v = 0, int id = 0) {
    get_pos[v] = ways[id].size();
    get_id[v] = id;
    ways[id].push_back(v);
    get_p[v] = ways[id][0];
    if (g[v].size() > 0)
        build_ways(ways, g[v][0], id);
    for (int i = 1; i < g[v].size(); ++i) {
        ways.push_back({});
        build_ways(ways, g[v][i], new_id++);
    }
}

struct segtree {
    segtree *l, *r;
    vector<int> rebs;
    segtree (int lb, int rb, vector<int> &v) {
        if (lb + 1 == rb) {
            rebs = {v[lb]};
            return;
        }
        int mid = (lb + rb) >> 1;
        l = new segtree(lb, mid, v);
        r = new segtree(mid, rb, v);
        rebs.resize(l->rebs.size() + r->rebs.size());
        merge(l->rebs.begin(), l->rebs.end(), r->rebs.begin(), r->rebs.end(), rebs.begin());
    }
    void walk(vector<segtree*> &good_parts, int le, int re, int lb, int rb) {
        if (le <= lb && rb <= re) {
            good_parts.push_back(this);
            return;
        }
        if (le >= rb || re <= lb)
            return;
        int mid = (lb + rb) >> 1;
        l->walk(good_parts, le, re, lb, mid);
        r->walk(good_parts, le, re, mid, rb);
    }
    void print(int lb, int rb) {
        cout << lb << ' ' << rb << ": ";
        for (auto x : rebs)
            cout << x << " ";
        cout << '\n';
        if (lb + 1 == rb)
            return;
        int mid = (lb + rb) >> 1;
        l->print(lb, mid);
        r->print(mid, rb);
    }
};

int get_segtree_res(segtree *root, int le, int re, int lb, int rb, int x) {
    vector<segtree*> good_parts;
    root->walk(good_parts, le, re, lb, rb);
    int ans = 0;
    for (int i = 0; i < good_parts.size(); ++i) {
        ans += upper_bound(good_parts[i]->rebs.begin(), good_parts[i]->rebs.end(), x) - good_parts[i]->rebs.begin();
    }
    return ans;
}

segtree *work(vector<int> &good_ways) {
    int rb = good_ways.size();
    vector<int> rebs(good_ways.size() - 1);
    for (int i = 1; i < good_ways.size(); ++i)
        rebs[i - 1] = get_c[{min(good_ways[i - 1], good_ways[i]), max(good_ways[i - 1], good_ways[i])}];
    segtree *ans = new segtree(0, rb - 1, rebs);
    return ans;
}

int get_result (int v, int x, vector<segtree*> &parts, vector<int> &parts_sz) {
    int ans = 0;
    while (v != 0) {
        if (get_p[v] == v) {
            int to = up[v][0];
            if (get_c[{min(v, to), max(v, to)}] <= x)
                ++ans;
            v = to;
        } else {
            ans += get_segtree_res(parts[get_id[v]],0, get_pos[v], 0, parts_sz[get_id[v]], x);
            v = get_p[v];
        }
    }
    return ans;
}

int ask(int a, int b, int x, vector<segtree*> &parts, vector<int> &parts_sz) {
    return get_result(a, x, parts, parts_sz) + get_result(b, x, parts, parts_sz) - 2 * get_result(lca(a, b), x, parts, parts_sz);
}

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    h[0] = -1;
    for (int i = 1; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a;
        --b;
        if (a > b)
            swap(a, b);
        get_c[{a, b}] = c;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs();
    for (int i = 1; i < MAXUP; ++i)
        for (int j = 0; j < n; ++j)
            up[j][i] = up[up[j][i - 1]][i - 1];
    vector<vector<int>> ways, good_ways;
    good_ways.reserve(ways.size());
    map<int, int> replacer;
    ways.resize(1);
    build_ways(ways);
    int tmpi = 0, tmp_good = 0;
    for (auto x : ways) {
        if (x.size() > 1) {
            good_ways.push_back(x);
            replacer[tmpi++] = tmp_good++;
        } else
            replacer[tmpi++] = -1;
    }
    for (int i = 0; i < n; ++i)
        get_id[i] = replacer[get_id[i]];
    replacer.clear();
    ways.clear();
    ways.shrink_to_fit();
    vector<segtree*> parts;
    vector<int> parts_sz(good_ways.size());
    for (int i = 0; i < good_ways.size(); ++i)
        parts_sz[i] = good_ways[i].size() - 1;
    parts.reserve(good_ways.size());
    for (int i = 0; i < good_ways.size(); ++i)
        parts.push_back(work(good_ways[i]));
    for (int i = 0; i < q; ++i) {
        int a, b, x;
        cin >> a >> b >> x;
        --a;
        --b;
        cout << ask(a, b, x, parts, parts_sz) << '\n';
    }
    return 0;
}
