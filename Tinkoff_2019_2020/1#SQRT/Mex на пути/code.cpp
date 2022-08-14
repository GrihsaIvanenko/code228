#include <bits/stdc++.h>

using namespace std;

#define DEBUGs

const int MAXN = 1e5, MAXD = 20, BLOCK = 300;

int p[MAXN][MAXD], my_reb[MAXN], deep[MAXN], cnt[MAXN], mexer[MAXN + MAXN], kolvo[(MAXN + MAXN + BLOCK - 1) / BLOCK], timer = 0;

pair<pair<int, int>, int> rebs[MAXN - 1];

pair<int, int> timex[MAXN - 1];

vector<int> g[MAXN], poss;

int to(int &number, int &now) {
    if (rebs[number].first.first == now)
        return rebs[number].first.second;
    return rebs[number].first.first;
}

void dfs(int v, int par, int h = 0) {
    p[v][0] = par;
    deep[v] = h;
    for (auto x : g[v]) {
        if (to(x, v) == par)
            continue;
        timex[x].first = timer++;
        poss.push_back(x);
        my_reb[to(x, v)] = x;
        dfs(to(x, v), v, h + 1);
        timex[x].second = timer++;
        poss.push_back(x);
    }
}

int lca(int a, int b) {
    if (deep[a] < deep[b])
        swap(a, b);
    for (int i = MAXD - 1; i >= 0; --i)
        if (deep[a] - deep[b] >= (1 << i))
            a = p[a][i];
    if (a == b)
        return a;
    for (int i = MAXD - 1; i >= 0; --i)
        if (p[a][i] != p[b][i]) {
            a = p[a][i];
            b = p[b][i];
        }
    return p[a][0];
}

void make_op(int pos) {
    int chislo = rebs[pos].second;
    if (cnt[pos]) {
        --cnt[pos];
        --mexer[chislo];
        if (!mexer[chislo])
            ++kolvo[chislo / BLOCK];
        return;
    }
    ++cnt[pos];
    ++mexer[chislo];
    if (mexer[chislo] == 1)
        --kolvo[chislo / BLOCK];
}

void solve() {
    memset(cnt, 0, sizeof(cnt));
    memset(kolvo, 0, sizeof(kolvo));
    memset(mexer, 0, sizeof(mexer));
    for (int i = 0; i < MAXN; ++i) {
        my_reb[i] = -1;
        ++kolvo[i / BLOCK];
    }
    int n, q;
    cin >> n >> q;
    set<int> s;
    s.insert(0);
    map<int, int> mm;
    for (int i = 1; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        s.insert(c);
        s.insert(c + 1);
        --a;
        --b;
        rebs[i - 1] = {{a, b}, c};
        g[a].push_back(i - 1);
        g[b].push_back(i - 1);
    }
    int kaka = 0;
    for (auto x : s)
        mm[x] = kaka++;
    for (int i = 1; i < n; ++i)
        rebs[i - 1].second = mm[rebs[i - 1].second];
    poss.reserve((n - 1) << 1);
    dfs(0, 0);
    for (int j = 1; j < MAXD; ++j)
        for (int i = 0; i < n; ++i)
            p[i][j] = p[p[i][j - 1]][j - 1];
    vector<pair<pair<int, int>, pair<int, int>>> tasks(q);
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        if (a == b) {
            tasks[i] = {{0, 0}, {0, i}};
            continue;
        }
        if (deep[a] < deep[b])
            swap(a, b);
        int c = lca(a, b);
        if (c == b) {
            int L = my_reb[a];
            for (int i = MAXD - 1; i >= 0; --i)
                if (deep[a] - deep[b] > (1 << i))
                    a = p[a][i];
            int R = my_reb[a];
            tasks[i] = {{timex[L].second / BLOCK, timex[R].second + 1}, {timex[L].second, i}};
        } else {
            int L = my_reb[a];
            int R = my_reb[b];
            if (timex[L].first > timex[R].second)
                swap(L, R);
            tasks[i] = {{timex[L].second / BLOCK, timex[R].first + 1}, {timex[L].second, i}};
        }
    }
    sort(tasks.begin(), tasks.end());
    int L = 0, R = 0;
    vector<int> ans(q, -1);
    for (int nomer = 0; nomer < q; ++nomer) {
        int LL = tasks[nomer].second.first;
        int RR = tasks[nomer].first.second;
        int ID = tasks[nomer].second.second;
        while (R < RR) {
            int id = poss[R];
            make_op(id);
            ++R;
        }
        while (L > LL) {
            int id = poss[L - 1];
            make_op(id);
            --L;
        }
        while (R > RR) {
            int id = poss[R - 1];
            make_op(id);
            --R;
        }
        while (L < LL) {
            int id = poss[L];
            make_op(id);
            ++L;
        }
        for (int pos_bl = 0; pos_bl < (MAXN + MAXN + BLOCK - 1) / BLOCK; ++pos_bl) {
            if (kolvo[pos_bl]) {
                for (int i = pos_bl * BLOCK;;++i) {
                    if (!mexer[i]) {
                        ans[ID] = i;
                        break;
                    }
                }
                break;
            }
        }
    }
    for (auto x : ans)
        cout << x << '\n';
}

int main() {
    #ifdef DEBUG
        freopen("t.cpp", "r", stdin);
    #else
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #endif // DEBUG
    solve();
    return 0;
}
