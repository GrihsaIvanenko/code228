#include <bits/stdc++.h>

using namespace std;

const int al_size = 26, mins = int('a'), mod = 10000;

struct segment {
    vector<int> go;
    bool terminal;
    int suff, col;
    segment() {
        terminal = 0;
        go.assign(al_size, -1);
        col = 0;
    }
};

struct coras {
    vector<segment> trie;

    coras() {
        trie.resize(1);
    }

    void eat(string &s) {
        int id = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (trie[id].go[s[i] - mins] == -1) {
               trie[id].go[s[i] - mins] = trie.size();
               segment t;
               trie.push_back(t);
            }
            id = trie[id].go[s[i] - mins];
        }
        trie[id].terminal |= 1;
    }

    void build() {
        trie[0].suff = 0;
        deque<int> q;
        for (int i = 0; i < al_size; ++i) {
            int to = trie[0].go[i];
            if (to != -1) {
                q.push_back(to);
                trie[to].suff = 0;
            } else {
                trie[0].go[i] = 0;
            }
        }
        while (!q.empty()) {
            int it = q.front();
            q.pop_front();
            for (int i = 0; i < al_size; ++i) {
                int to = trie[it].go[i];
                if (to != -1) {
                    q.push_back(to);
                    trie[to].suff = trie[trie[it].suff].go[i];
                    trie[to].terminal |= trie[trie[to].suff].terminal;
                } else {
                    trie[it].go[i] = trie[trie[it].suff].go[i];
                }
            }
        }
    }
    void fill_in(vector<vector<int>> &go, int id = 0) {
        trie[id].col = 1;
        for (int i = 0; i < al_size; ++i) {
            if (!trie[trie[id].go[i]].terminal) {
                ++go[id][trie[id].go[i]];
                if (trie[trie[id].go[i]].col == 0) {
                    fill_in(go, trie[id].go[i]);
                }
            }
        }
    }
};

vector<vector<int>> pw(vector<vector<int>> &p1, vector<vector<int>> &p2) {
    vector<vector<int>> res(p1.size(), vector<int>(p1.size(), 0));
    for (int i = 0; i < p1.size(); ++i) {
        for(int j = 0; j < p1.size(); ++j) {
            for(int k = 0; k < p1.size(); ++k) {
                res[i][j] += (p1[i][k] * p2[k][j]) % mod;
                res[i][j] %= mod;
            }
        }
    }
    return res;
}

vector<vector<int>> pow_matrix(vector<vector<int>> v, int p) {
    if (p == 1) {
       return v;
    }
    vector<vector<int>> res = pow_matrix(pw(v, v), p / 2);
    if (p % 2) {
       res = pw(res, v);
    }
    return res;
}

int pow_number(int it, int p) {
    if (p == 0) {
       return 1;
    }
    if (p == 1) {
       return it;
    }
    int res = pow_number((it * it) % mod, p / 2);
    if (p % 2) {
       res *= it;
       res %= mod;
    }
    return res;
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, t;
    cin >> n >> t;
    coras corasic;
    for (int i = 0; i < t; ++i) {
        string s;
        cin >> s;
        corasic.eat(s);
    }
    corasic.build();
    vector<vector<int>> go(101, vector<int>(101, 0));
    corasic.fill_in(go);
    vector<vector<int>> res = pow_matrix(go, n);
    int ans = 0;
    for (int i = 0; i < 101; ++i) {
        ans += res[0][i];
        ans %= mod;
    }
    int all = pow_number(al_size, n);
    cout << (all + mod - ans) % mod << '\n';
    return 0;
}

