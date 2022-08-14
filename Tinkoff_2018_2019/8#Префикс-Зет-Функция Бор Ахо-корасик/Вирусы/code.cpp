#include <bits/stdc++.h>

using namespace std;

const int al_size = 2, mins = int('0');

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

    bool cycle(int id = 0) {
        if (trie[id].terminal) {
           return false;
        }
        if (trie[id].col == 1) {
           return true;
        }
        trie[id].col = 1;
        bool res = 0;
        for (int i = 0; i < al_size; ++i) {
            if  (trie[trie[id].go[i]].col == 2 || trie[trie[id].go[i]].terminal) {
                continue;
            } else {
                res |= cycle(trie[id].go[i]);
            }
        }
        trie[id].col = 2;
        return res;
    }
};

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    coras corasic;
    vector<int> sz(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        sz[i] = s.size();
        corasic.eat(s);
    }
    corasic.build();
    if (corasic.cycle()) {
        cout << "TAK\n";
    } else {
        cout << "NIE\n";
    }
    return 0;
}

