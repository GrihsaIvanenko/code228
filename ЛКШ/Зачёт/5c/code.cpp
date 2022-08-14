#include <bits/stdc++.h>

using namespace std;

struct segment{
    segment() {
        go.assign(26, -1);
    }
    vector<int> go;
    int terminal = 0;
    int suff = -1, long_suff = -1;
};

struct coras{
    vector<segment> trie;
    coras() {
        trie.resize(1);
    }
    void eat(string &s, int pos = 0, int id = 0) {
        if (pos == s.size()) {
            trie[id].terminal++;
            return;
        }
        if (trie[id].go[s[pos]- 'a'] == -1) {
            segment t;
            trie[id].go[s[pos] - 'a'] = trie.size();
            trie.push_back(t);
        }
        eat(s, pos + 1, trie[id].go[s[pos] - 'a']);
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
                    if (trie[trie[trie[id].go[i]].suff].terminal != 0) {
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
                cout << trie[id].suff << "-suff " << trie[id].long_suff << "-long_suff " << trie[id].terminal << " is terminal\n";
            }
        }
    }
    void work(string &s, int good_pos, long long &ans) {
        int id = 0;
        for (int i = 0; i < s.size(); ++i) {
            id = trie[id].go[s[i] - 'a'];
            int long_id = id;
            while (long_id != 0 && i >= good_pos) {
                ans += (long long)trie[long_id].terminal;
                long_id = trie[long_id].long_suff;
            }
        }
    }
};

const int MAXN = 100000;

vector<pair<int, char>> tr[MAXN];

coras corasic;

long long ans = 0;

string s;

void dfs(int v, int good_pos = 0) {
    if (tr[v].size() == 0) {
        corasic.work(s, good_pos, ans);
    }
    for (int i = 0; i < tr[v].size(); ++i) {
        if(i == 0) {
            s.push_back(tr[v][i].second);
            dfs(tr[v][i].first, good_pos);
            s.pop_back();
        } else {
            int gp = s.size();
            s.push_back(tr[v][i].second);
            dfs(tr[v][i].first, gp);
            s.pop_back();
        }
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> used(n);
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        for (int j = 0; j < t; ++j) {
            int tmp;
            char to;
            cin >> tmp >> to;
            --tmp;
            tr[i].push_back({tmp, to});
        }
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        corasic.eat(s);
    }
    corasic.build();
    dfs(0);
    cout << ans << endl;
    return 0;
}
