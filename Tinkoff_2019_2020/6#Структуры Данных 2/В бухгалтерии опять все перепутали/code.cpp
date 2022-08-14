#include <bits/stdc++.h>

using namespace std;

const int MAXN = 131072;

const long long INF = 1e9 + 7;

struct segtree {
    long long val = 0, push = 0;
    segtree *l, *r;
    segtree(int lb, int rb) {
        if (lb + 1 == rb)
            return;
        int mid = (lb + rb) >> 1;
        l = new segtree (lb, mid);
        r = new segtree (mid, rb);
    }
    void puch(int lb, int rb) {
        if (push == 0)
            return;
        if (lb + 1 == rb) {
            val += push;
            push = 0;
            return;
        }
        l->push += push;
        r->push += push;
        int mid = (lb + rb) >> 1;
        val = l->push * (long long)(rb - mid) + l->val + r->push * (long long)(mid - lb) + r->val;
        push = 0;
        return;
    }
    long long get_sum(int le, int re, int lb = 0, int rb = MAXN) {
        if (le >= rb || re <= lb)
            return 0;
        puch(lb, rb);
        if (le <= lb && rb <= re)
            return val;
        return l->get_sum(le, re, lb, (lb + rb) >> 1) + r->get_sum(le, re, (lb + rb) >> 1, rb);
    }
    void add(int le, int re, long long inc, int lb = 0, int rb = MAXN) {
        if (le >= rb || re <= lb)
            return;
        puch(lb, rb);
        if (le <= lb && rb <= re) {
            push += inc;
            return;
        }
        int mid = (lb + rb) >> 1;
        l->add(le, re, inc, lb, mid);
        r->add(le, re, inc, mid, rb);
        val = l->push * (long long)(rb - mid) + l->val + r->push * (long long)(mid - lb) + r->val;
    }
};

int anc[MAXN], in[MAXN], out[MAXN], boss[MAXN], sz[MAXN], timer = 0;

vector<int> g[MAXN];

void dfs_sz(int v = 0) {
    sz[v] = 1;
    for (int i = 0; i < (int)g[v].size(); ++i) {
        dfs_sz(g[v][i]);
        sz[v] += sz[g[v][i]];
        if (sz[g[v][i]] > sz[g[v][0]])
            swap(g[v][i], g[v][0]);
    }
}

void dfs_hld(int v = 0, int b = 0) {
    in[v] = timer++;
    boss[v] = b;
    for (int i = 0; i < (int)g[v].size(); ++i) {
        if (i == 0) {
            dfs_hld(g[v][i], b);
        } else {
            dfs_hld(g[v][i], g[v][i]);
        }
    }
    out[v] = timer;
}

segtree *root;

long long collect_sum(int v) {
    long long ans = root->get_sum(in[v], out[v]);
    v = anc[v];
    while (v != -1) {
        ans += root->get_sum(in[boss[v]], in[v] + 1);
        v = anc[boss[v]];
    }
    return ans;
}

void add_v_ad(int v, long long inc) {
    root->add(in[v], out[v], inc);
    v = anc[v];
    while (v != -1) {
        root->add(in[boss[v]], in[v] + 1, inc);
        v = anc[boss[v]];
    }
}

int main() {
    //freopen("Untitled1.cpp", "r", stdin);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    root = new segtree(0, MAXN);
    int n, q;
    cin >> n >> q;
    anc[0] = -1;
    for (int i = 1; i < n; ++i) {
        cin >> anc[i];
        g[anc[i]].push_back(i);
    }
    dfs_sz();
    dfs_hld();
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        root->add(in[i], in[i] + 1, t);
        if (i == n - 1) cout << t << ' ';
    }
    /*for (int i = 0; i < n; ++i) {
        cout << i <<": " << sz[i] << " " << in[i] << " " << out[i] << " " << boss[i] << endl;
    }*/
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        long long itt = collect_sum(a);
        itt %= INF;
        add_v_ad(b, itt);
        cout << root->get_sum(in[n - 1], in[n - 1] + 1) << ' ';
    }
    return 0;
}
