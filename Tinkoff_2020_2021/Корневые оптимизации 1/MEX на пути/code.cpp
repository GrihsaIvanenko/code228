#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000, SZ_MO = 450, SZ_MEX = 300;

vector<int> g[MAXN];

int numb[MAXN], a[MAXN], b[MAXN], pos[MAXN], way[MAXN << 1], timer = 0, A[MAXN];
int B[MAXN], cnt[MAXN << 1], kolvo_v_bloke[MAXN], kolvo[MAXN + 1], ans[MAXN];

void dfs(int v, int p = -1) {
    pos[v] = timer;
    for (auto x : g[v]) {
        int to = a[x];
        if (to == v)
            to = b[x];
        if (to == p)
            continue;
        way[timer++] = x;
        dfs(to, v);
        way[timer++] = x;
    }
}

bool cmp(int a, int b) {
    int P1 = pos[A[a]] / SZ_MO, P2 = pos[A[b]] / SZ_MO;
    if (P1 != P2)
        return P1 < P2;
    if (P1 & 1)
        return pos[B[a]] > pos[B[b]];
    return pos[B[a]] < pos[B[b]];
}

void change(int id) {
    int add = 1 - 2 * cnt[id];
    cnt[id] ^= 1;
    int c = numb[id];
    kolvo[c] += add;
    if (kolvo[c] == 0 && add == -1)
        --kolvo_v_bloke[c / SZ_MEX];
    else if (kolvo[c] == 1 && add == 1)
        ++kolvo_v_bloke[c / SZ_MEX];
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<int> vals(n + n + 1);
    for (int i = 0; i + 1 < n; ++i) {
        int a1, b1, c;
        cin >> a1 >> b1 >> c;
        --a1;
        --b1;
        g[a1].push_back(i);
        g[b1].push_back(i);
        a[i] = a1;
        b[i] = b1;
        numb[i] = c;
        vals[i + i] = c;
        vals[i + i + 1] = c + 1;
    }
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    map<int, int> mm;
    for (auto x : vals)
        mm[x] = timer++;
    timer = 0;
    for (int i = 0; i + 1 < n; ++i)
        numb[i] = mm[numb[i]];
    dfs(0);
    vector<int> tasks(q);
    for (int i = 0; i < q; ++i) {
        cin >> A[i];
        cin >> B[i];
        --A[i];
        --B[i];
        if (pos[A[i]] > pos[B[i]])
            swap(A[i], B[i]);
        tasks[i] = i;
    }
    sort(tasks.begin(), tasks.end(), cmp);
    int L = 0, R = 0;
    for (int i = 0; i < q; ++i) {
        int id = tasks[i];
        int l = pos[A[id]], r = pos[B[id]];
        while (L > l)
            change(way[--L]);
        while (R < r)
            change(way[R++]);
        while (L < l)
            change(way[L++]);
        while (R > r)
            change(way[--R]);
        for (int j = 0; j < MAXN; ++j) {
            if (kolvo_v_bloke[j] != SZ_MEX) {
                for (int k = j * SZ_MEX; k < (j + 1) * SZ_MEX; ++k) {
                    if (!kolvo[k]) {
                        ans[id] = k;
                        break;
                    }
                }
                break;
            }
        }
    }
    for (int i = 0; i < q; ++i)
        cout << ans[i] << '\n';
    return 0;
}
