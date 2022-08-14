#include <bits/stdc++.h>

using namespace std;

#define int long long

const int INF = 1e10 + 7;

int n, k;

vector<pair<pair<int, int>, int>> v;

struct Node {
    int y, val, key, sz, l, r, mn;
    Node(int val_, int key_) {
        y = rand();
        mn = val = val_;
        key = key_;
        sz = 1;
        l = r = -1;
    }
};

vector<Node> d;

int sz(int v) {
    if (v == -1)
        return 0;
    return d[v].sz;
}

int mn(int v) {
    if (v == -1)
        return INF;
    return d[v].mn;
}

void update(int a) {
    if (a == -1)
        return;
    d[a].sz = sz(d[a].l) + 1 + sz(d[a].r);
    d[a].mn = min(d[a].val, min(mn(d[a].l), mn(d[a].r)));
}

int merge(int a, int b) {
    if (a == -1 || b == -1)
        return max(a, b);
    if (d[a].y > d[b].y) {
        d[a].r = merge(d[a].r, b);
        update(a);
        return a;
    }
    d[b].l = merge(a, d[b].l);
    update(b);
    return b;
}

pair<int, int> split_by_kolvo(int v, int kolvo) {
    //  assert(kolvo >= 0);
    //  assert(kolvo <= sz(v));
    if (v == -1) {
        //  assert(kolvo == 0);
        return {-1, -1};
    }
    if (sz(d[v].l) >= kolvo) {
        pair<int, int> p = split_by_kolvo(d[v].l, kolvo);
        d[v].l = p.second;
        update(v);
        return {p.first, v};
    }
    pair<int, int> p = split_by_kolvo(d[v].r, kolvo - sz(d[v].l) - 1);
    d[v].r = p.first;
    update(v);
    return {v, p.second};
}

pair<int, int> split_by_key(int v, int key) {
    if (v == -1)
        return {-1, -1};
    if (key <= d[v].key) {
        pair<int, int> p = split_by_key(d[v].l, key);
        d[v].l = p.second;
        update(v);
        return {p.first, v};
    }
    pair<int, int> p = split_by_key(d[v].r, key);
    d[v].r = p.first;
    update(v);
    return {v, p.second};
}

int root;

void insert_(int rig, int w) {
    int id = d.size();
    d.push_back(Node(w, rig));
    pair<int, int> p = split_by_key(root, rig);
    root = merge(p.first, merge(id, p.second));
}

int get_zapros(int v, int able_weight) {
    //  assert(v != -1);
    if (mn(d[v].l) <= able_weight)
        return get_zapros(d[v].l, able_weight);
    if (d[v].val <= able_weight)
        return d[v].key;
    //  assert(mn(d[v].r) <= able_weight);
    return get_zapros(d[v].r, able_weight);
}

bool can(int mid) {
    root = -1;
    d.clear();
    set<pair<int, int>> op_by_right, wait_to_op;
    int r_prev = -1;
    for (unsigned i = 0; i < v.size(); ++i) {
        if (v[i].second > mid)
            continue;
        while (wait_to_op.size()) {
            pair<int, int> p = *wait_to_op.begin();
            if (p.first >= v[i].first.first)
                break;
            wait_to_op.erase(p);
            op_by_right.insert({v[p.second].first.second, p.second});
            insert_(v[p.second].first.second, v[p.second].second);
            assert(sz(root) == op_by_right.size());
        }
        while (op_by_right.size()) {
            pair<int, int> p = *op_by_right.begin();
            if (p.first >= v[i].first.first)
                break;
            //  assert(p.first >= r_prev);
            r_prev = p.first;
            op_by_right.erase(p);
            pair<int, int> p_ = split_by_kolvo(root, 1);
            root = p_.second;
            //  assert(sz(root) == op_by_right.size());
        }
        if (r_prev + 1 == v[i].first.first) {
            if (v[i].first.second == k)
                return true;
            op_by_right.insert({v[i].first.second, i});
            insert_(v[i].first.second, v[i].second);
            // assert(sz(root) == op_by_right.size());
            continue;
        }
        int able_weight = mid - v[i].second;
        if (op_by_right.size()) {
            if (d[root].mn <= able_weight) {
                if (v[i].first.second == k)
                    return true;
                wait_to_op.insert({get_zapros(root, able_weight), i});
            }
        }
    }
    return false;
}

void solve() {
    srand(time(nullptr));
    cin >> n >> k;
    --k;
    v.resize(n);
    for (int i = 0; i < n; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        --l;
        --r;
        v[i] = {{l, r}, x};
    }
    sort(v.begin(), v.end());
    unsigned int lb = 0, rb = 1e9 + 1e9 + 1;
    while (rb - lb > 1) {
        unsigned int mid = (lb + rb) >> 1;
        if (can(mid))
            rb = mid;
        else
            lb = mid;
    }
    if (rb == 1e9 + 1e9 + 1)
        cout << "-1\n";
    else
        cout << rb << '\n';
}

signed main() {
    //  freopen("t.cpp", "r", stdin);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int t = 1;
    while (t--)
        solve();
    return 0;
}
