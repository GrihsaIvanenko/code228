#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200;

int used[MAXN], mt[MAXN];

vector<pair<int, int>> g[MAXN];

bool dfs(int v, int mid) {
    if (used[v] == 1) {
        return 0;
    }
    used[v] = 1;
    for (auto x : g[v]) {
        if (x.second < mid) {
           continue;
        }
        if (mt[x.first] == -1 || dfs(mt[x.first], mid)) {
            mt[x.first] = v;
            return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int k;
            cin >> k;
            g[i].push_back({j, k});
        }
    }
    for (int i = 0; i < MAXN; ++i) {
        mt[i] = -1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            used[j] = 0;
        }
        dfs(i, 0);
    }
    int max_p = 0;
    for (int i = 0; i < MAXN; ++i) {
        if (mt[i] != -1) {
           ++max_p;
        }
    }
    int lb = 0, rb = 1000000001;
    while (rb - lb > 1) {
        int mid = (lb + rb) >> 1;
        for (int i = 0; i < MAXN; ++i) {
            mt[i] = -1;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < MAXN; ++j) {
                used[j] = 0;
            }
            dfs(i, mid);
        }
        int now = 0;
        for (int i = 0; i < MAXN; ++i) {
            if (mt[i] != -1) {
                ++now;
            }
        }
        if (now == max_p) {
            lb = mid;
        } else {
            rb = mid;
        }
    }
    cout << lb << '\n';
    return 0;
}
