#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101;

vector<int> g[MAXN];

int mt[MAXN], is_ans[MAXN], ans, weights[MAXN][MAXN];

char used[MAXN], go[MAXN], used_L[MAXN], used_R[MAXN];

void dfs_color(int v, bool left = 1) {
    if (left) {
        if (used_L[v]) {
            return;
        }
        used_L[v] = 1;
        for (auto x : g[v]) {
            if (mt[x] != v) {
                dfs_color(x, 0);
            }
        }
    } else {
        if (used_R[v]) {
            return;
        }
        used_R[v] = 1;
        if (mt[v] != -1) {
            dfs_color(mt[v], 1);
        }
    }
}

bool dfs(int v) {
    if (used[v]) {
        return false;
    }
    used[v] = 1;
    for (auto x : g[v]) {
        if (mt[x] == -1 || dfs(mt[x])) {
            mt[x] = v;
            return true;
        }
    }
    return false;
}

void solve() {
    int n;
    cin >> n;
    ans = n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> weights[i][j];
        }
    }
    for (int k = 0; k < MAXN; ++k) {
        for (int i = 0; i < MAXN; ++i) {
            for (int j = 0; j < MAXN; ++j) {
                if (weights[i][k] && weights[k][j])
                    weights[i][j] = 1;
            }
        }
    }
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            if (weights[i][j]) {
                g[i].push_back(j);
            }
        }
    }
    for (int i = 0; i < MAXN; ++i) {
        mt[i] = -1;
        used_L[i] = used_R[i] = used[i] = 0;
        go[i] = is_ans[i] = 1;
    }
    for (int i = 0; i < MAXN; ++i) {
        dfs(i);
        for (int j = 0; j < MAXN; ++j) {
            used[j] = 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (mt[i] != -1) {
            go[mt[i]] = 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (go[i]) {
            dfs_color(i);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!used_L[i] || used_R[i]) {
            --ans;
            is_ans[i] = 0;
        }
    }
    for (int i = 0; i < n; ++i){
        if (is_ans[i]){
            for (int j = 0; j < n; ++j){
                if (weights[i][j]){
                    if (is_ans[j] == 1){
                        --ans;
                    }
                    is_ans[j] = 0;
                }
            }
        }
    }
    cout << ans << '\n';
    for (int i = 0; i < n; ++i) {
        if (is_ans[i]) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
}

int main() {
    freopen("hobbits.in", "r", stdin);
    freopen("hobbits.out", "w", stdout);
    solve();
    return 0;
}
