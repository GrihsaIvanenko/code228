#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100100, AL = 26;

vector<pair<int, char>> g[MAXN];

struct Part {
    vector<int> to;
    int sf, term;
    Part() {
        to.assign(AL, -1);
        sf = -1;
        term = 0;
    }
};

struct corasic {
    vector<Part> c;
    corasic() {
        c.reserve(MAXN);
        c.resize(1);
    }
    void eat(string &s) {
        int id = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (c[id].to[s[i] - 'a'] == -1) {
                c[id].to[s[i] - 'a'] = c.size();
                Part p;
                c.push_back(p);
            }
            id = c[id].to[s[i] - 'a'];
        }
        ++c[id].term;
    }
    void build() {
        c[0].sf = 0;
        deque<int> q;
        for (int i = 0; i < AL; ++i) {
            int to = c[0].to[i];
            if (to != -1) {
                c[to].sf = 0;
                q.push_back(to);
            } else {
                c[0].to[i] = 0;
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            for (int i = 0; i < AL; ++i) {
                int u = c[v].to[i];
                if (u != -1) {
                    q.push_back(u);
                    c[u].sf = c[c[v].sf].to[i];
                    c[u].term += c[c[u].sf].term;
                } else {
                    c[v].to[i] = c[c[v].sf].to[i];
                }
            }
        }
    }
    void dance(long long &ans, int v = 0, int id = 0) {
        ans += (long long)c[id].term;
        for (auto x : g[v])
            dance(ans, x.first, c[id].to[x.second - 'a']);
    }
};

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int v;
            char t;
            cin >> v >> t;
            --v;
            g[i].push_back({v, t});
        }
    }
    int m;
    cin >> m;
    corasic coras;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        coras.eat(s);
    }
    coras.build();
    long long ans = 0;
    coras.dance(ans);
    cout << ans << '\n';
    return 0;
}
