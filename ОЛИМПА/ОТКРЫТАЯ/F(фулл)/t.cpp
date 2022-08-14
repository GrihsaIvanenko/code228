#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 500;

vector<int> g[MAXN + MAXN + 2];

const int MAXM = (MAXN * MAXN + MAXN + MAXN) << 1;

ll xx1[MAXN], yy1[MAXN], xx2[MAXN], yy2[MAXN], dists[MAXN * MAXN];

int Cc[MAXN], timer_dists = 0, C[MAXM], F[MAXM], st[MAXM], fin[MAXM], ST, FIN, dist[MAXN + MAXN + 2], n, m;

int first[MAXN + MAXN + 2], timer = 0;

void add1(int a, int b, int c) {
    st[timer] = a;
    fin[timer] = b;
    C[timer] = c;
    F[timer] = 0;
    g[a].push_back(timer);
    ++timer;
}

void add(int a, int b, int c) {
    add1(a, b, c);
    add1(b, a, 0);
}

bool bfs() {
    memset(dist, 0, sizeof(dist));
    dist[ST] = 1;
    queue<int> q;
    q.push(ST);
    while(q.size()) {
        int v = q.front();
        q.pop();
        for (auto x : g[v])
            if (C[x] - F[x] && !dist[fin[x]]) {
                dist[fin[x]] = dist[v] + 1;
                q.push(fin[x]);
            }
    }
    return dist[FIN];
}

bool dfs(int v = ST) {
    if (v == FIN)
        return true;
    while (first[v] != g[v].size()) {
        int id = g[v][first[v]];
        if (C[id] - F[id] == 0) {
            ++first[v];
            continue;
        }
        int to = fin[id];
        if (dist[to] != dist[v] + 1) {
            ++first[v];
            continue;
        }
        bool gg = dfs(to);
        if (!gg) {
            ++first[v];
        } else {
            ++F[id];
            --F[id ^ 1];
            return true;
        }
    }
    return false;
}

bool hvat(ll mid) {
    timer = 0;
    ST = n + m, FIN = n + m + 1;
    for (int i = 0; i <= FIN; ++i)
        g[i].clear();
    for (int i = 0; i < n; ++i) {
        add(ST, i, 1);
        for (int j = 0; j < m; ++j)
            if ((xx1[i] - xx2[j]) * (xx1[i] - xx2[j]) + (yy1[i] - yy2[j]) * (yy1[i] - yy2[j]) <= mid)
                add(i, n + j, 1);
    }
    for (int i = 0; i < m; ++i)
        add(i + n, FIN, Cc[i]);
    while (bfs()) {
        memset(first, 0, sizeof(first));
        while (dfs());
    }
    int tmp_ans = 0;
    for (auto x : g[ST])
        tmp_ans += F[x];
    return tmp_ans == n;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> xx1[i] >> yy1[i];
    for (int i = 0; i < m; ++i)
        cin >> xx2[i] >> yy2[i] >> Cc[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            dists[timer_dists++] = (xx1[i] - xx2[j]) * (xx1[i] - xx2[j]) + (yy1[i] - yy2[j]) * (yy1[i] - yy2[j]);
    sort(dists, dists + timer_dists);
    timer_dists = unique(dists, dists + timer_dists) - dists;
    int lb = -1, rb = timer_dists - 1;
    while (rb - lb > 1) {
        int mid = (lb + rb) / 2;
        if (hvat(dists[mid]))
            rb = mid;
        else
            lb = mid;
    }
    cout << setprecision(20) << fixed << sqrt(dists[rb]) << '\n';
}

int main() {
    srand(time(nullptr));
    //  freopen("input.txt", "r", stdin);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}

