#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 1, MAXUP = 21, INF = 1e9 + 7;

vector<int> g[MAXN];

int d[MAXN], pos[MAXN], len[(1 << MAXUP)];

int sparce[1 << MAXUP][MAXUP];

vector<int> euler;

void dfs(int v, int deep = 0) {
    euler.push_back(v);
    d[v] = deep;
    for (auto x : g[v]) {
        dfs(x, deep + 1);
        euler.push_back(v);
    }
    pos[v] = euler.size() - 1;
}

void solve() {
    for (int i = 0; i < (1 << MAXUP); ++i) {
        len[i] = -1;
    }
    for (int i = 0; i < MAXUP; ++i) {
        len[(1 << i)] = i;
    }
    for (int i = 1; i < (1 << MAXUP); ++i) {
        if (len[i] == -1) {
            len[i] = len[i - 1];
        }
    }
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int t;
        cin >> t;
        g[t].push_back(i);
    }
    dfs(0);
    for (int i = 0; i < euler.size(); ++i) {
        sparce[i][0] = i;
    }
    for (int i = 1; i < MAXUP; ++i) {
        for (int j = 0; j + (1 << i) < euler.size(); ++j) {
            if (d[euler[sparce[j][i - 1]]] > d[euler[sparce[j + (1 << (i - 1))][i - 1]]]) {
                sparce[j][i] = sparce[j + (1 << (i - 1))][i - 1];
            }
            else{
                sparce[j][i] = sparce[j][i - 1];
            }
        }
    }
    long long a1, a2, x, y, z, last_ans = 0, ans = 0;
    cin >> a1 >> a2 >> x >> y >> z;
    int v1, v2, k;
    for (int i = 0; i < m; ++i) {
        v1 = pos[(a1 + last_ans) % n];
        v2 = pos[a2];
        if (v1 > v2) {
            swap(v1, v2);
        }
        k = len[v2 - v1 + 1];
        if (d[euler[sparce[v1][k]]] > d[euler[sparce[v2 - (1 << k) + 1][k]]]) {
            last_ans = euler[sparce[v2 - (1 << k) + 1][k]];
        } else {
            last_ans = euler[sparce[v1][k]];
        }
        ans += last_ans;
        a1 = (a1 * x + a2 * y + z) % n;
        a2 = (a2 * x + a1 * y + z) % n;
    }
    cout << ans << '\n';
}

int main() {
    solve();
    return 0;
}
