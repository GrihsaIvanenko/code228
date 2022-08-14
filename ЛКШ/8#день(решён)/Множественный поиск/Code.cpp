#include <bits/stdc++.h>

using namespace std;

struct segment{
    segment() {
        go.assign(26, -1);
    }
    vector<int> go;
    vector<int> terminal;
    int suff = -1, long_suff = -1;
    bool used = false;
};

struct coras{
    vector<segment> trie;
    coras() {
        trie.resize(1);
    }
    void eat(string s, int pos, int id = 0) {
        if (s.size() == 0) {
            trie[id].terminal.push_back(pos);
            return;
        }
        if (trie[id].go[s[0]- 'a'] == -1) {
            segment t;
            trie[id].go[s[0] - 'a'] = trie.size();
            trie.push_back(t);
        }
        eat(s.substr(1), pos, trie[id].go[s[0] - 'a']);
    }
    void build() {
        trie[0].suff = trie[0].long_suff = 0;
        deque<int> q;
        for (int i = 0; i < 26; ++i) {
            if (trie[0].go[i] == -1) {
                trie[0].go[i] = 0;
            }
            else{
                q.push_back(trie[0].go[i]);
                trie[trie[0].go[i]].suff = 0;
                trie[trie[0].go[i]].long_suff = 0;
            }
        }
        while (!q.empty()) {
            int id = q.front();
            q.pop_front();
            for (int i = 0; i < 26; ++i) {
                if (trie[id].go[i] == -1) {
                    trie[id].go[i] = trie[trie[id].suff].go[i];
                } else {
                    q.push_back(trie[id].go[i]);
                    trie[trie[id].go[i]].suff = trie[trie[id].suff].go[i];
                    if (trie[trie[trie[id].go[i]].suff].terminal.size() != 0) {
                        trie[trie[id].go[i]].long_suff = trie[trie[id].go[i]].suff;
                    }
                    else{
                        trie[trie[id].go[i]].long_suff = trie[trie[trie[id].go[i]].suff].long_suff;
                    }
                }
            }
        }
    }
    void debug() {
        int id = 0;
        while (true + true) {
            cout << "id: " << id << endl;
            cout << "print: 0-exit; 1-go(input); 2-go; 3-suff, l_suff, terminal\n";
            int tmp;
            cin >> tmp;
            if (tmp == 0) {
                return;
            } else if (tmp == 1) {
                cin >> id;
            } else if (tmp == 2) {
                for (int i = 0; i < 26; ++i) {
                    cout << char(i + 'a') << trie[id].go[i] << " ";
                }
                cout << endl;
            } else{
                cout << trie[id].suff << "-suff " << trie[id].long_suff << "-long_suff ";
                for (auto x : trie[id].terminal) {
                    cout << x << " ";
                }
                cout << "is terminal\n";
            }
        }
    }
    void work(string &s, vector<vector<int>> &ins) {
        int id = 0;
        for (int i = 0; i < s.size(); ++i) {
            id = trie[id].go[s[i] - 'a'];
            int long_id = id;
            while (long_id != 0 && !trie[long_id].used) {
                trie[long_id].used = 1;
                for (auto x : trie[long_id].terminal) {
                    ins[x].push_back(i);
                }
                long_id = trie[long_id].long_suff;
            }
        }
    }
};

void solve() {
    int n;
    cin >> n;
    coras corasic;
    vector<int> lens(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        lens[i] = s.size();
        corasic.eat(s, i);
    }
    vector<vector<int>> ins(n);
    corasic.build();
    //corasic.debug();
    string text;
    cin >> text;
    corasic.work(text, ins);
    for (int i = 0; i < ins.size(); ++i) {
        for (int j = 0; j < ins[i].size(); ++j) {
            ins[i][j] -= (lens[i] - 1);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (ins[i].size() != 0) {
            cout << "YES\n";
        } else{
            cout << "NO\n";
        }
    }
}

int main() {
    solve();
}
