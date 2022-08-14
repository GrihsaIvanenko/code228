#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300;

const long long  INF = 1e12 + 7;

vector<int>  p, num[MAXN + MAXN + 2], fins, sts, C, F, COST;

vector<long long> fi;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> v(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> v[i][j];
    int m = n * n + n + n;
    p.resize(n + n + 2);
    fins.resize(m + m);
    sts.resize(m + m);
    C.resize(m + m);
    F.resize(m + m);
    COST.resize(m + m);
    fi.resize(n + n + 2);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int pos = i * n + j;
            num[i].push_back(pos + pos);
            num[j + n].push_back(pos + pos + 1);
            fins[pos + pos] = j + n;
            fins[pos + pos + 1] = i;
            sts[pos + pos] = i;
            sts[pos + pos + 1] = j + n;
            C[pos + pos] = 1;
            COST[pos + pos] = v[i][j];
            COST[pos + pos + 1] = -v[i][j];
        }
        num[n + n].push_back(2 * n * n + i + i);
        num[i].push_back(2 * n * n + i + i + 1);
        fins[2 * n * n + i + i] = i;
        fins[2 * n * n + i + i + 1] = n + n;
        sts[2 * n * n + i + i] = n + n;
        sts[2 * n * n + i + i + 1] = i;
        C[2 * n * n + i + i] = 1;
        num[i + n].push_back(2 * n * n + n + n + i + i);
        num[n + n + 1].push_back(2 * n * n + n + n + i + i + 1);
        fins[2 * n * n + n + n + i + i] = n + n + 1;
        fins[2 * n * n + n + n + i + i + 1] = i + n;
        sts[2 * n * n + n + n + i + i] = i + n;
        sts[2 * n * n + n + n + i + i + 1] = n + n + 1;
        C[2 * n * n + n + n + i + i] = 1;
    }
    int st = n + n, fin = n + n + 1;
    while (true) {
        p[st] = st;
        for (int i = 0; i < n + n + 2; ++i)
            fi[i] = INF;
        fi[st] = 0;
        set<int> s;
        s.insert(st);
        while (!s.empty()) {
            int v = *s.begin();
            s.erase(v);
            for (auto x : num[v]) {
                if (fi[sts[x]] != INF && C[x] - F[x] > 0 && fi[fins[x]] > fi[sts[x]] + COST[x]) {
                    p[fins[x]] = x;
                    fi[fins[x]] = fi[sts[x]] + COST[x];
                    s.insert(fins[x]);
                }
            }
        }
        if (fi[fin] == INF)
            break;
        vector<int> way;
        int v = fin;
        while (v != st) {
            way.push_back(p[v]);
            v = sts[p[v]];
        }
        for (auto x : way) {
            ++F[x];
            --F[x ^ 1];
        }
    }
    long long ans = 0;
    for (int i = 0; i < n * n * 2; ++i) {
        if (F[i] > 0)
            ans += (long long)COST[i];
    }
    cout << ans << '\n';
    for (int i = 0; i < n * n * 2; ++i)
        if (F[i] > 0)
            cout << (i / 2) / n + 1 << ' ' << (i / 2) % n + 1 << '\n';
}

int main() {
    //freopen("A.txt", "r", stdin);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
