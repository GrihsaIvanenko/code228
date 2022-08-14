#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4000;

bool used_L[MAXN], used_R[MAXN], start[MAXN];

int mt[MAXN];

vector<int> g[MAXN];

void dfs(int v, bool left = 1){
    if (left) {
        if (used_L[v]) {
            return;
        }
        used_L[v] = 1;
        for (auto x : g[v]) {
            if (mt[x] != v) {
                dfs(x, 0);
            }
        }
    } else {
        if (used_R[v]) {
            return;
        }
        used_R[v] = 1;
        if (mt[v] != -1) {
            dfs(mt[v], 1);
        }
    }
}

void solve() {
    for (int i = 0; i < MAXN; ++i) {
        used_L[i] = used_R[i] = 0;
        start[i] = 1;
        mt[i] = -1;
    }
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        for (int j = 0; j < t; ++j) {
            int k;
            cin >> k;
            --k;
            g[i].push_back(k);
        }
    }
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        if (t == 0) {
            continue;
        }
        mt[t - 1] = i;
        start[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        if (start[i]) {
            dfs(i);
        }
    }
    int ans_l = 0, ans_r = 0;
    for (int i = 0; i < n; ++i) {
        ans_l += !used_L[i];
    }
    for (int i = 0; i < m; ++i) {
        ans_r += used_R[i];
    }
    cout << ans_l + ans_r << endl << ans_l << " ";
    for (int i = 0; i < n; ++i) {
        if (used_L[i] == 0) {
            cout << i + 1 << " ";
        }
    }
    cout << endl << ans_r << " ";
    for (int i = 0; i < m; ++i) {
        if (used_R[i]) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    solve();
    return 0;
}
