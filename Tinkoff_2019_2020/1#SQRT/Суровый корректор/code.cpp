#include <bits/stdc++.h>

using namespace std;

#define DEBUGs

const int MAXN = 1e5 + 1;

int go[MAXN][26], suf[MAXN], long_suf[MAXN], term[MAXN], timer = 1, comp[MAXN];

void add(int pos, string &s) {
    int id = 0;
    for (auto x : s) {
        assert('a' <= x && x <= 'z');
        if (go[id][x - 'a'] == -1)
            go[id][x - 'a'] = timer++;
        id = go[id][x - 'a'];
    }
    term[id] = pos;
}

void solve() {
    string t;
    cin >> t;
    int n;
    cin >> n;
    vector<string> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        add(i, v[i]);
    }
    queue<int> q;
    suf[0] = 0;
    for (int i = 0; i < 26; ++i)
        if (go[0][i] == -1)
            go[0][i] = 0;
        else {
            suf[go[0][i]] = 0;
            q.push(go[0][i]);
        }
    while (!q.empty()) {
        int v = q.front();
        if (term[suf[v]] == -1)
            long_suf[v] = long_suf[suf[v]];
        else
            long_suf[v] = suf[v];
        q.pop();
        for (int i = 0; i < 26; ++i)
            if (go[v][i] == -1)
                go[v][i] = go[suf[v]][i];
            else {
                suf[go[v][i]] = go[suf[v]][i];
                q.push(go[v][i]);
            }
    }
    vector<int> s(n);
    for (int i = 0; i < n; ++i)
        s[i] = v[i].size();
    sort(s.begin(), s.end());
    s.resize(unique(s.begin(), s.end()) - s.begin());
    timer = 0;
    for (auto x : s)
        comp[x] = timer++;
    vector<int> my_len(s.size());
    for (int i = 0; i < MAXN; ++i)
        if (comp[i] != -1)
            my_len[comp[i]] = i;
    vector<vector<int>> inputs(s.size());
    int id = 0;
    for (int i = 0; i < t.size(); ++i) {
        char x = t[i];
        id = go[id][x - 'a'];
        int tmp = id;
        if (term[tmp] == -1)
            tmp = long_suf[tmp];
        while (tmp != -1) {
            inputs[comp[v[term[tmp]].size()]].push_back(i);
            tmp = long_suf[tmp];
        }
    }
    int Q;
    cin >> Q;
    int ans[Q];
    memset(ans, 0, sizeof(ans));
    vector<pair<int, int>> op(Q);
    vector<pair<int, int>> cl(Q);
    vector<int> lenggg(Q);
    for (int i = 0; i < Q; ++i) {
        int l, r;
        cin >> l >> r;
        op[i] = {l, i};
        cl[i] = {r, i};
        lenggg[i] = r - l + 1;
    }
    sort(op.begin(), op.end());
    sort(cl.begin(), cl.end());
    for (int i = 0; i < inputs.size(); ++i) {
        int mlen = my_len[i];
        int uko = 0, ukl = 0;
        for (int j = 0; j < Q; ++j) {
            while (uko < inputs[i].size() && op[j].first > inputs[i][uko] + 2 - mlen)
                ++uko;
            if (mlen <= lenggg[op[j].second])
                ans[op[j].second] -= uko;
            while (ukl < inputs[i].size() && cl[j].first > inputs[i][ukl])
                ++ukl;
           if (mlen <= lenggg[cl[j].second])
                ans[cl[j].second] += ukl;
        }
    }
    for (int i = 0; i < Q; ++i)
        cout << ans[i]<< ' ';
    cout << '\n';
}

void precalc() {
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < 26; ++j)
            go[i][j] = -1;
        comp[i] = term[i] = suf[i] = long_suf[i] = -1;
    }
}

int main() {
    precalc();
    #ifdef DEBUG
        freopen("t.cpp", "r", stdin);
    #else
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #endif // DEBUG
    solve();
    return 0;
}
