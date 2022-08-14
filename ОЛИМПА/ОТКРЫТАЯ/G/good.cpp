#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXM = 131072 * 2;
const int MAXN = 800000;
const int MAXX = 200000;

#define x first
#define y second

set<int> X[MAXX], Y[MAXX];

int go[MAXX][4], sum[MAXN], ANS = 0, p[MAXN], sz[MAXN], q;

vector<pair<int, int>> rebs[MAXM << 1];

int le, re, a, b;

void add_reb(int v = 1, int lb = 0, int rb = MAXM) {
    if (le <= lb && rb <= re) {
        rebs[v].push_back({a, b});
        return;
    }
    if (lb + 1 == rb || le >= rb || lb >= re)
        return;
    add_reb(v + v, lb, (lb + rb) >> 1);
    add_reb(v + v + 1, (lb + rb) >> 1, rb);
}

ll f(ll a, ll b) {
    if (a < b)
        return a * MAXN + b;
    return b * MAXN + a;
}

int get(int x) {
    if (p[x] == x)
        return x;
    return get(p[x]);
}

vector<pair<pair<int, int>, pair<int, int>>> cash;//B, A, sz[a], sum[a]

void dfs(int v) {
    for (auto x : rebs[v]) {
        int A = x.x, B = x.y;
        while (p[A] != A)
            A = p[A];
        while (p[B] != B)
            B = p[B];
        if (A == B) {
            cash.push_back({{A, B}, {sz[B], sum[B]}});
        } else {
            if (sz[A] < sz[B])
                swap(A, B);
            cash.push_back({{B, A}, {sz[A], sum[A]}});
            p[B] = A;
            int prev = sum[A];
            sum[A] += sum[B];
            if (sum[A] == 11 && prev != 11) {
                ++ANS;
            }
            sz[A] = max(sz[A], sz[B] + 1);
        }
    }
    if (v < MAXM) {
        dfs(v + v);
        dfs(v + v + 1);
    } else {
        if (v - MAXM < q)
            cout << ANS << '\n';
        else
            exit(0);
    }
    for (auto x : rebs[v]) {
        int B = cash.back().x.x, A = cash.back().x.y, SZ = cash.back().y.x, SUM = cash.back().y.y;
        p[B] = B;
        sz[A] = SZ;
        int prev = sum[A];
        sum[A] = SUM;
        if (sum[A] != 11 && prev == 11) {
            --ANS;
        }
        cash.pop_back();
    }
}

void solve() {
    int n, m;
    cin >> n >> m >> q;
    vector<pair<int, pair<int, int>>> tasks(q);
    map<pair<int, int>, int> pt;
    for (int i = 0; i < q; ++i) {
        cin >> tasks[i].x >> tasks[i].y.x >> tasks[i].y.y;
        --tasks[i].y.x;
        --tasks[i].y.y;
        X[tasks[i].y.x].insert(tasks[i].y.y);
        Y[tasks[i].y.y].insert(tasks[i].y.x);
        pt[{tasks[i].y.x, tasks[i].y.y}] = -1;
    }
    int timer_pt = 0, timer_block = 0;
    for (auto x : pt)
        pt[x.first] = timer_pt++;
    for (int i = 0; i < m; ++i)
        if (Y[i].size()) {
            sum[timer_block] = 10;
            go[pt[{*Y[i].begin(), i}]][0] = timer_block++;
            auto it = Y[i].begin(), it1 = Y[i].begin();
            ++it1;
            while (it1 != Y[i].end()) {
                int ID1 = pt[{*it, i}];
                int ID2 = pt[{*it1, i}];
                go[ID1][2] = timer_block;
                go[ID2][0] = timer_block++;
                ++it;
                ++it1;
            }
            sum[timer_block] = 1;
            go[pt[{*Y[i].rbegin(), i}]][2] = timer_block++;
        } else {
            ++ANS;
        }
    for (int i = 0; i < n; ++i)
        if (X[i].size()) {
            go[pt[{i, *X[i].begin()}]][3] = timer_block++;
            auto it = X[i].begin(), it1 = X[i].begin();
            ++it1;
            while (it1 != X[i].end()) {
                int ID1 = pt[{i, *it}];
                int ID2 = pt[{i, *it1}];
                go[ID1][1] = timer_block;
                go[ID2][3] = timer_block++;
                ++it;
                ++it1;
            }
            go[pt[{i, *X[i].rbegin()}]][1] = timer_block++;
        }
    unordered_map<ll, vector<int>> mm;
    int timer_event = 0, timer_task = 0;
    for (auto x : pt) {
        int A = go[x.y][0];
        int B = go[x.y][1];
        int C = go[x.y][2];
        int D = go[x.y][3];
        mm[f(A, C)].push_back(timer_event);
        mm[f(B, D)].push_back(timer_event);
    }
    vector<int> prev(timer_pt);
    for (auto x : tasks) {
        if (x.x == 0) {
            int id = pt[x.y];
            int A = go[id][0];
            int B = go[id][1];
            int C = go[id][2];
            int D = go[id][3];
            if (prev[id] == 1) {
                mm[f(A, B)].push_back(timer_event);
                mm[f(C, D)].push_back(timer_event);
            } else {
                mm[f(A, D)].push_back(timer_event);
                mm[f(B, C)].push_back(timer_event);
            }
            mm[f(A, C)].push_back(timer_event);
            mm[f(B, D)].push_back(timer_event);
            prev[id] = 0;
        } else if (x.x == 1) {
            int id = pt[x.y];
            int A = go[id][0];
            int B = go[id][1];
            int C = go[id][2];
            int D = go[id][3];
            prev[id] = 1;
            mm[f(A, C)].push_back(timer_event);
            mm[f(B, D)].push_back(timer_event);
            mm[f(A, B)].push_back(timer_event);
            mm[f(C, D)].push_back(timer_event);
        } else {
            int id = pt[x.y];
            int A = go[id][0];
            int B = go[id][1];
            int C = go[id][2];
            int D = go[id][3];
            prev[id] = 2;
            mm[f(A, C)].push_back(timer_event);
            mm[f(B, D)].push_back(timer_event);
            mm[f(A, D)].push_back(timer_event);
            mm[f(B, C)].push_back(timer_event);
        }
        ++timer_event;
    }
    for (auto x : mm)
        if (x.y.size() % 2)
            mm[x.x].push_back(timer_event);
    for (auto x : mm) {
        for (int i = 0; i < x.y.size(); i += 2)
            if (x.y[i] != x.y[i + 1]) {
                le = x.y[i];
                re = x.y[i + 1];
                a = x.x / MAXN;
                b = x.x % MAXN;
                add_reb();
            }
    }
    dfs(1);
}

int main() {
    cash.reserve(MAXN);
    for (int i = 0; i < MAXN; ++i) {
        p[i] = i;
        sz[i] = 1;
    }
    //  freopen("t.cpp", "r", stdin);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
