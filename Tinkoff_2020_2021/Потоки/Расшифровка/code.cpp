#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;

int get(char x) {
    if ('a' <= x && x <= 'z')
        return x - 'a';
    return x - 'A' + 26;
}

vector<int> F, C, COST, st, fin, p, d, num[106];

void add(int a, int b, int c, int d) {
    num[a].push_back(F.size());
    F.push_back(0);
    C.push_back(c);
    COST.push_back(d);
    st.push_back(a);
    fin.push_back(b);
}

void add_reb(int v, int to, int cost) {
    add(v, to, 1, cost);
    add(to, v, 0, -cost);
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    string a, b;
    cin >> a >> b;
    vector<vector<int>> gogo(k, vector<int> (k));
    for (int i = 0; i < n; ++i) {
        --gogo[get(a[i])][get(b[i])];
    }
    F.reserve(k * (k + 1) * 2);
    C.reserve(k * (k + 1) * 2);
    st.reserve(k * (k + 1) * 2);
    fin.reserve(k * (k + 1) * 2);
    for (int i = 0; i < k; ++i) {
        add_reb(k + k, i, 0);
        for (int j = 0; j < k; ++j)
            add_reb(i, j + k, gogo[i][j]);
        add_reb(i + k, k + k + 1, 0);
    }
    p.resize(k + k + 2);
    while (true) {
        d.assign(k + k + 2, INF);
        d[k + k] = 0;
        set<pair<int, int>> otr;
        otr.insert({0, k + k});
        while (otr.size()) {
            int v = (*otr.begin()).second;
            otr.erase(otr.begin());
            for (auto i : num[v])
                if (C[i] - F[i] && d[st[i]] != INF && d[st[i]] + COST[i] < d[fin[i]]) {
                    d[fin[i]] = d[st[i]] + COST[i];
                    p[fin[i]] = i;
                    otr.insert({0, fin[i]});
                }
        }
        if (d[k + k + 1] == INF)
            break;
        vector<int> a;
        int v = k + k + 1;
        while (v != k + k) {
            a.push_back(p[v]);
            v = st[a.back()];
        }
        for (auto x : a) {
            ++F[x];
            --F[x ^ 1];
        }
    }
    vector<int> ans(k);
    int answ = 0;
    for (int i = 0; i < fin.size(); ++i)
        if (st[i] < k + k && fin[i] < k + k && F[i] > 0)
            ans[st[i]] = fin[i] - k;
    for (int i = 0; i < k; ++i)
        answ -= gogo[i][ans[i]];
    cout << answ << '\n';
    for (int i = 0; i < k; ++i)
        if (ans[i] < 26)
            cout << char('a' + ans[i]);
        else
            cout << char('A' + ans[i] - 26);
    cout << '\n';
    return 0;
}
