#include <bits/stdc++.h>

using namespace std;

const int al_size = 26, mins = int('a');

struct segment {
    vector<int> go, terminal;
    int suff, long_suff;
    segment() {
        go.assign(al_size, -1);
    }
};

struct coras {
    vector<segment> trie;

    coras() {
        trie.resize(1);
    }

    void eat(string &s, int number) {
        int id = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (trie[id].go[s[i] - mins] == -1) {
               trie[id].go[s[i] - mins] = trie.size();
               segment t;
               trie.push_back(t);
            }
            id = trie[id].go[s[i] - mins];
        }
        trie[id].terminal.push_back(number);
    }

    void build() {
        trie[0].suff = 0;
        trie[0].long_suff = 0;
        deque<int> q;
        for (int i = 0; i < al_size; ++i) {
            int to = trie[0].go[i];
            if (to != -1) {
                q.push_back(to);
                trie[to].suff = 0;
                trie[to].long_suff = 0;
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
                    if (trie[trie[to].suff].terminal.size() > 0) {
                       trie[to].long_suff = trie[to].suff;
                    } else {
                        trie[to].long_suff = trie[trie[to].suff].long_suff;
                    }
                } else {
                    trie[it].go[i] = trie[trie[it].suff].go[i];
                }
            }
        }
    }

    void work(string &s, vector<vector<int>> &ins) {
        int id = 0;
        for (int i = 0; i < s.size(); ++i) {
            id = trie[id].go[s[i] - mins];
            int cop = id;
            while (cop != 0) {
                for(auto x : trie[cop].terminal) {
                    ins[x].push_back(i);
                }
                cop = trie[cop].long_suff;
            }
        }
    }

    void debug() {
        int id = 0;
        while(true) {
            cout << "PROGRAMM:print 1->go(input); 2->go; 3->terminal; 4->suff, long_suff; 5->stop\n";
            cout << "PROGRAMM: id = " << id << endl << "YOU:";
            int type;
            cin >> type;
            if (type == 1) {
               int to;
               cin >> to;
               id = to;
            } else if (type == 2) {
                cout << "PROGRAMM: go ";
                for (int i = 0; i < al_size; ++i) {
                    cout << trie[id].go[i] << '(' << char('a' + i) << ") ";
                }
                cout << endl;
            } else if (type == 3) {
                cout << "PROGRAMM: terminal ";
                for (auto x : trie[id].terminal) {
                    cout << x << " ";
                }
                cout << endl;
            } else if (type == 4) {
                cout << "PROGRAMM: suff of " << id << " = " << trie[id].suff << ", long suff of " << id << " = " << trie[id].long_suff << endl;
            } else if (type == 5) {
                cout << "PROGRAMM: END OF DEBUG" << endl;
                return;
            }

        }
    }
};

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    string F;
    cin >> F;
    int n;
    cin >> n;
    coras corasic;
    vector<int> sz(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        sz[i] = s.size();
        corasic.eat(s, i);
    }
    corasic.build();
    vector<vector<int>> ins(n);
    corasic.work(F, ins);
    for (int i = 0; i < n; ++i) {
        cout << ins[i].size() << ' ';
        for (auto x : ins[i]) {
            cout << x - sz[i] + 2 << ' ';
        }
        cout << '\n';
    }
    return 0;
}
