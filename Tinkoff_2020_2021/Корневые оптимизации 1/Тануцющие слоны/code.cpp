#include <bits/stdc++.h>

using namespace std;

const int SZ = 400;

const int MAXN = 560000;

int INF = 1e9 + 7, L;

int cash[MAXN], inp[(MAXN << 1) + 1], kuda[MAXN << 1], kolvo[(MAXN << 1) + 1], SZe, has_slon[MAXN];

pair<int, int> tasks[MAXN];

void build(int id) {
    int lb = id * SZ, rb = id * SZ + SZ;
    int prev_slon = rb;
    int uk = SZe;
    if (rb != SZe)
        uk = lower_bound(inp, inp + SZe, inp[rb] + L) - inp;
    for (int i = rb - 1; i >= lb; --i) {
        if (!has_slon[i]) {
            if (prev_slon == rb) {
                kuda[i] = rb;
                kolvo[i] = 0;
            } else {
                kuda[i] = kuda[prev_slon];
                kolvo[i] = kolvo[prev_slon];
            }
            continue;
        }
        prev_slon = i;
        int pos_to = inp[i] + L;
        while (inp[uk - 1] >= pos_to)
            --uk;
        if (uk == SZe) {
            kuda[i] = SZe;
            kolvo[i] = 1;
        } else {
            if (uk >= rb) {
                kuda[i] = uk;
                kolvo[i] = 1;
            } else {
                kuda[i] = kuda[uk];
                kolvo[i] = kolvo[uk] + 1;
            }
        }
    }
}

int ask() {
    int pos = 0;
    int ans = 0;
    while (pos != SZe) {
        ans += kolvo[pos];
        pos = kuda[pos];
    }
    return ans;
}

void solve() {
    inp[MAXN + MAXN] = INF + INF;
    int n, m;
    cin >> n >> m >> L;
    SZe = n + m;
    ++L;
    for (int i = 0; i < n; ++i) {
        cin >> cash[i];
        inp[i] = cash[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> tasks[i].first >> tasks[i].second;
        inp[i + n] = tasks[i].second;
    }
    sort(inp, inp + SZe);
    SZe = unique(inp, inp + n + m) - inp;
    while (SZe % SZ > 0)
        inp[SZe++] = INF;
    int KOLVO = SZe / SZ;
    for (int i = 0; i < n; ++i)
        cash[i] = lower_bound(inp, inp + SZe, cash[i]) - inp;
    for (int i = 0; i < m; ++i)
        tasks[i].second = lower_bound(inp, inp + SZe, tasks[i].second) - inp;
    for (int i = 0; i < n; ++i)
        ++has_slon[cash[i]];
    for (int i = 0; i < KOLVO; ++i)
        build(i);
    int prev = 0;
    for (int i = 0; i < m; ++i) {
        int id = (prev + tasks[i].first) % n;
        --has_slon[cash[id]];
        if (cash[id] / SZ != tasks[i].second / SZ)
            build(cash[id] / SZ);
        cash[id] = tasks[i].second;
        ++has_slon[cash[id]];
        build(cash[id] / SZ);
        prev = ask();
        cout << prev << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
