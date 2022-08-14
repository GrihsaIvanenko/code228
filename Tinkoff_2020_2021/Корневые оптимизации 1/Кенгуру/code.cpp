#include <bits/stdc++.h>

using namespace std;

const int SZ = 400, INF = 1e9 + 7;

const int MAXN = 100000;

vector<pair<int, int>> g[MAXN];

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> vals(n + n);
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].second >> v[i].first;
        vals[i + i] = v[i].first;
        vals[i + i + 1] = v[i].second;
    }
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    for (int i = 0; i < n; ++i) {
        v[i].first = lower_bound(vals.begin(), vals.end(), v[i].first) - vals.begin();
        v[i].second = lower_bound(vals.begin(), vals.end(), v[i].second) - vals.begin();
    }
    vector<pair<pair<int, int>, int>> tasks(m);
    for (int i = 0; i < m; ++i) {
        cin >> tasks[i].first.first >> tasks[i].first.second;
        tasks[i].second = i;
        tasks[i].first.first = lower_bound(vals.begin(), vals.end(), tasks[i].first.first) - vals.begin();
        tasks[i].first.second = upper_bound(vals.begin(), vals.end(), tasks[i].first.second) - vals.begin() - 1;
    }
    sort(tasks.begin(), tasks.end());
    vector<int> ans(m);
    for (int l = 0; l < n; ++l) {
        int LL = v[l].first, RR = v[l].second;
        for (int len = 1; l + len <= n && len < SZ; ++len) {
            LL = min(LL, v[l + len - 1].first);
            RR = max(RR, v[l + len - 1].second);
            g[LL].push_back({RR, len});
        }
    }
    vector<int> pr_min(SZ + 1, INF);
    int uk = MAXN - 1;
    for (int i = m - 1; i >= 0; --i) {
        while (uk >= tasks[i].first.first) {
            for (auto x : g[uk])
                pr_min[x.second] = min(pr_min[x.second], x.first);
            --uk;
        }
        for (int j = 1; j <= SZ; ++j)
            if (tasks[i].first.second >= pr_min[j])
                ans[tasks[i].second] = max(ans[tasks[i].second], j);
    }
    for (int ser = 0; ser < n; ser += SZ) {
        vector<int> L(n), R(n);
        L[ser] = v[ser].first;
        R[ser] = v[ser].second;
        for (int i = ser - 1; i >= 0; --i) {
            L[i] = min(L[i + 1], v[i].first);
            R[i] = max(R[i + 1], v[i].second);
        }
        for (int i = ser + 1; i < n; ++i) {
            L[i] = min(L[i - 1], v[i].first);
            R[i] = max(R[i - 1], v[i].second);
        }
        for (int i = 0; i < m; ++i) {
            if (tasks[i].first.first > L[ser] || tasks[i].first.second < R[ser])
                continue;
            int lb = 0, rb = ser + 1;
            for (int mid = (lb + rb) >> 1; rb - lb > 1; mid = (lb + rb) >> 1)
                if ((tasks[i].first.first <= L[ser - mid]) && (R[ser - mid] <= tasks[i].first.second))
                    lb = mid;
                else
                    rb = mid;
            int LB = ser - lb;
            lb = 0, rb = n - ser;
            for (int mid = (lb + rb) >> 1; rb - lb > 1; mid = (lb + rb) >> 1)
                if ((tasks[i].first.first <= L[ser + mid]) && (R[ser + mid] <= tasks[i].first.second))
                    lb = mid;
                else
                    rb = mid;
            int RB = ser + rb;
            ans[tasks[i].second] = max(ans[tasks[i].second], RB - LB);
        }
    }
    for (auto x : ans)
        cout << x << '\n';
}

int main() {
    // freopen("input.txt", "r", stdin);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
