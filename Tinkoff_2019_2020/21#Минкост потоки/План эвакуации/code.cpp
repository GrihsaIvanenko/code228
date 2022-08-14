#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MAXN = 228, MAXM = 100000, INF = 5e18 + 7;

int FI[MAXN];
int dust[MAXN];
int P[MAXN];
int F[MAXM];
int C[MAXM];
int COST[MAXM];
int ST[MAXM];
int FIN[MAXM];
int XA[MAXN];
int YA[MAXN];
int IN[MAXN];
int timer = 0;
int plan[100][100];

vector<int> num[MAXN];

int dist(int x, int y) {
    return abs(XA[x] - XA[y]) + abs(YA[x] - YA[y]) + 1;
}

void add_r(int v, int u, int c, int cost, int id) {
    num[v].push_back(id);
    F[id] = 0;
    C[id] = c;
    COST[id] = cost;
    ST[id] = v;
    FIN[id] = u;
}

void add_reb (int v, int u, int c, int cost){
    add_r(v, u, c, cost, timer++);
    add_r(u, v, 0, -cost, timer++);
}

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    assert(n <= 100);
    assert(m <= 100);
    for (int i = 0; i < n; ++i)
        num[i].reserve(m + 1);
    for (int i = 0; i < m; ++i)
        num[i + n].reserve(n + 1);
    num[n + m].reserve(n);
    num[n + m + 1].reserve(m);
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        XA[i] = a;
        YA[i] = b;
        IN[i] = c;
        add_reb(n + m, i, c, 0);
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        XA[i + n] = a;
        YA[i + n] = b;
        IN[i + n] = c;
        add_reb(i + n, n + m + 1, c, 0);
        for (int j = 0; j < n; ++j)
            add_reb(j, i + n, min(IN[j], IN[i + n]), dist(j, i + n));
    }
    int fin = n + m + 1, st = n + m;
    for (int i = 0; i <= fin; ++i)
        FI[i] = INF;
    FI[st] = 0;
    set<int> s;
    s.insert(st);
    while (s.size()) {
        int v = *s.begin();
        s.erase(v);
        for (auto x : num[v])
            if (C[x] - F[x] > 0 && FI[FIN[x]] > FI[ST[x]] + COST[x]) {
                FI[FIN[x]] = FI[ST[x]] + COST[x];
                s.insert(FIN[x]);
            }
    }
    bitset<MAXN> used;
    while (true) {
        used.reset();
        for (int i = 0; i < MAXN; ++i)
            dust[i] = INF;
        dust[st] = 0;
        for (int iter = 0; iter < n + m + 2; ++iter) {
            int cur = -1;
            for (int i = 0; i < n + m + 2; ++i)
                if (!used[i] && dust[i] != INF && (cur == -1 || (dust[i] < dust[cur])))
                    cur = i;
            if (cur == -1)
                break;
            used[cur] = 1;
            for (auto x : num[cur])
                if (C[x] - F[x] && dust[FIN[x]] > dust[cur] + FI[cur] - FI[FIN[x]] + COST[x]) {
                    P[FIN[x]] = x;
                    dust[FIN[x]] = dust[cur] + FI[cur] - FI[FIN[x]] + COST[x];
                }
        }
        if (dust[fin] == INF)
            break;
        for (int i = 0; i < n + m + 2; ++i)
            FI[i] += dust[i];
        vector<int> way;
        int MAXF = INF;
        int v = fin;
        while (v != st) {
            way.push_back(P[v]);
            MAXF = min(MAXF, (int)(C[way.back()] - F[way.back()]));
            v = ST[P[v]];
        }
        for (auto x : way) {
            F[x] += MAXF;
            F[x ^ 1] -= MAXF;
        }
    }
    int cost = 0;
    for (int i = 0; i < timer; ++i) {
        if (ST[i] == st || FIN[i] == fin || COST[i] < 0)
            continue;
        cost += F[i] * COST[i];
    }
    int cur_c = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            cin >> x;
            cur_c += x * dist(i, j + n);
        }
    }
    assert(cur_c >= cost);
    if (cur_c == cost) {
        cout << "OPTIMAL\n";
        return 0;
    }
    cout << "SUBOPTIMAL\n";
    for (int i = 0; i < timer; ++i) {
        if (ST[i] == st || FIN[i] == fin || COST[i] < 0)
            continue;
        plan[ST[i]][FIN[i] - n] = F[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << plan[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}
