#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 65536;

int sparce[MAXN][50], v[MAXN][3], d, pw[MAXN];

void build(int lvl, int lb = 0, int rb = MAXN, int deep = 15) {
    int mid = (lb + rb) >> 1;
    if (deep > lvl) {
        build(lvl, lb, mid, deep - 1);
        build(lvl, mid, rb, deep - 1);
        return;
    }
    for (int pos = lb; pos < rb; ++pos)
        for (int i = 0; i < d; ++i)
            sparce[pos][i] = sparce[pos][i] = -1;
    sparce[mid - 1][v[mid - 1][0] % d] = max(sparce[mid - 1][v[mid - 1][0] % d], v[mid - 1][0]);
    sparce[mid - 1][v[mid - 1][1] % d] = max(sparce[mid - 1][v[mid - 1][1] % d], v[mid - 1][1]);
    sparce[mid - 1][v[mid - 1][2] % d] = max(sparce[mid - 1][v[mid - 1][2] % d], v[mid - 1][2]);
    for (int i = mid - 1; i > lb; --i) {
        for (int j = 0; j < d; ++j)
            if (sparce[i][j] != -1) {
                sparce[i - 1][(v[i - 1][0] + j) % d] = max(sparce[i - 1][(v[i - 1][0] + j) % d], sparce[i][j] + v[i - 1][0]);
                sparce[i - 1][(v[i - 1][1] + j) % d] = max(sparce[i - 1][(v[i - 1][1] + j) % d], sparce[i][j] + v[i - 1][1]);
                sparce[i - 1][(v[i - 1][2] + j) % d] = max(sparce[i - 1][(v[i - 1][2] + j) % d], sparce[i][j] + v[i - 1][2]);
            }
    }
    sparce[mid][v[mid][0] % d] = max(sparce[mid][v[mid][0] % d], v[mid][0]);
    sparce[mid][v[mid][1] % d] = max(sparce[mid][v[mid][1] % d], v[mid][1]);
    sparce[mid][v[mid][2] % d] = max(sparce[mid][v[mid][2] % d], v[mid][2]);
    for (int i = mid; i + 1 < rb; ++i)
        for (int j = 0; j < d; ++j)
            if (sparce[i][j] != -1) {
                sparce[i + 1][(v[i + 1][0] + j) % d] = max(sparce[i + 1][(v[i + 1][0] + j) % d], sparce[i][j] + v[i + 1][0]);
                sparce[i + 1][(v[i + 1][1] + j) % d] = max(sparce[i + 1][(v[i + 1][1] + j) % d], sparce[i][j] + v[i + 1][1]);
                sparce[i + 1][(v[i + 1][2] + j) % d] = max(sparce[i + 1][(v[i + 1][2] + j) % d], sparce[i][j] + v[i + 1][2]);
            }
}

signed main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n >> d;
    for (int i = 0; i < n; ++i)
        cin >> v[i][0] >> v[i][1] >> v[i][2];
    pw[0] = -1;
    for (int i = 1; i < MAXN; ++i)
        pw[i] = pw[i - 1] + ((i & (i - 1)) == 0);
    int Q;
    cin >> Q;
    vector<pair<int, pair<int, int>>> QQ(Q);
    for (int q = 0; q < Q; ++q) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;
        QQ[q] = {pw[l ^ r], {l, r}};
        if (l == r) {
            vector<int> tmp = {v[l][0], v[l][1], v[l][2]};
            sort(tmp.rbegin(), tmp.rend());
            if (tmp[0] % d == 0) {
                QQ[q].second.first = tmp[0];
            } else if (tmp[1] % d == 0) {
                QQ[q].second.first = tmp[1];
            } else if (tmp[2] % d == 0) {
                QQ[q].second.first = tmp[2];
            } else {
                QQ[q].second.first = -1;
            }
        }
    }
    for (int i = 0; i < 16; ++i) {
        build(i);
        for (int j = 0; j < Q; ++j)
            if (QQ[j].first == i) {
                int ans = -1;
                for (int k = 0; k < d; ++k) {
                    int l = (d - k) % d;
                    if (sparce[QQ[j].second.first][k] != -1 && sparce[QQ[j].second.second][l] != -1)
                        ans = max(ans, sparce[QQ[j].second.first][k] + sparce[QQ[j].second.second][l]);
                }
                QQ[j].second.first = ans;
            }
    }
    for (int i = 0; i < Q; ++i)
        cout << QQ[i].second.first << '\n';
    cout << '\n';
    return 0;
}
