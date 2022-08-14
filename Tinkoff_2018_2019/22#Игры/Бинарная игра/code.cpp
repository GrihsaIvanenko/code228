#include <bits/stdc++.h>

using namespace std;

const int al_size = 2, mins = int('0');

vector<vector<int>> bak;

vector<int> c, ban;

queue<int> losers;

struct segment {
    vector<int> go;
    bool terminal;
    int suff, col, dp;
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
                bak[to].push_back(0);
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
                    bak[to].push_back(it);
                    trie[to].suff = trie[trie[it].suff].go[i];
                    trie[to].terminal |= trie[trie[to].suff].terminal;
                    trie[to].terminal |= trie[it].terminal;
                } else {
                    if (trie[trie[it].suff].go[i] != it) {
                        bak[trie[trie[it].suff].go[i]].push_back(it);
                    }
                    trie[it].go[i] = trie[trie[it].suff].go[i];
                }
            }
        }
    }

    int down(string &s) {
        int id = 0;
        for (int i = 0; i < s.size(); ++i) {
            id = trie[id].go[s[i] - mins];
        }
        return id;
    }

    void build_accepted() {
        for (int i = 0; i < trie.size(); ++i) {
            if (trie[i].terminal) {
                ban[i] = 1;
                for (auto x : bak[i]) {
                    c[x]--;
                }
            }
        }
        for (int i = 0; i < trie.size(); ++i) {
            if  (c[i] == 0 && !ban[i]) {
                ban[i] = 2;
                losers.push(i);
            }
        }
        while (!losers.empty()) {
            int lox = losers.front();
            losers.pop();
            for (auto x : bak[lox]) {
                if (ban[x]) {
                    continue;
                }
                ban[x] = 1;
                for (auto y : bak[x]) {
                    if (ban[y]) {
                       continue;
                    }
                    c[y]--;
                    if (c[y] == 0) {
                        ban[y] = 2;
                        losers.push(y);
                    }
                }
            }
        }
    }
};

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, l;
    cin >> n >> l;
    coras corasic;
    vector<int> sz(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        sz[i] = s.size();
        corasic.eat(s);
    }
    bak.resize(corasic.trie.size());
    c.assign(bak.size(), 2);
    ban.resize(bak.size());
    corasic.build();
    corasic.build_accepted();
    int pos = 0;
    if (l != 0) {
       string it;
       cin >> it;
       pos = corasic.down(it);
    }
    if (!ban[pos]) cout << "Friendship";
    else if (ban[pos] == 1) cout << "Olya";
    else cout << "Iskander";
    cout << endl;
    return 0;
}

