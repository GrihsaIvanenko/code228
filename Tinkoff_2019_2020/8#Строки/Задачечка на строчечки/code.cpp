#include <bits/stdc++.h>

using namespace std;

const int AL = 26;

struct part {
    vector<int> go;
    vector<int> term;
    int suf, long_suf;
    part() {
        go.assign(26, -1);
        suf = -1;
        long_suf = -1;
    }
};

struct coras {
    vector<part> c;
    coras() {
        c.resize(1);
    }
    void eat(string &s, int pos) {
        int id = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            int to = s[i] - 'a';
            if (c[id].go[to] == -1) {
                c[id].go[to] = c.size();
                part p;
                c.push_back(p);
            }
            id = c[id].go[to];
        }
        c[id].term.push_back(pos);
    }
    void build() {
        c[0].suf = 0;
        c[0].long_suf = 0;
        deque<int> q;
        for (int i = 0; i < AL; ++i) {
            int to = c[0].go[i];
            if (to != -1) {
                q.push_back(to);
                c[to].suf = 0;
                c[to].long_suf = 0;
            } else {
                c[0].go[i] = 0;
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            for (int i = 0; i < AL; ++i) {
                int to = c[v].go[i];
                if (to == -1) {
                    c[v].go[i] = c[c[v].suf].go[i];
                } else {
                    c[to].suf = c[c[v].suf].go[i];
                    q.push_back(to);
                    if ((int)c[c[to].suf].term.size() > 0)
                        c[to].long_suf = c[to].suf;
                    else
                        c[to].long_suf = c[c[to].suf].long_suf;
                }
            }
        }
    }
    void print_() {
        int id = 0;
        while (true) {
            cout << id << ": " << c[id].suf << " " << c[id].long_suf << endl;
            for (int i = 0; i < AL; ++i) {
                if (c[id].go[i] != -1)
                    cout << char((int)('a') + i) << ' ' << c[id].go[i] << ";";
            }
            cout << endl;
            cin >> id;
            if (id == -1)
                return;
        }
    }
    void work(string &s, vector<pair<int, vector<int>>> &ins) {
        int id = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            id = c[id].go[s[i] - 'a'];
            int tmp = id;
            while (tmp != 0) {
                for (auto x : c[tmp].term) {
                   ins[x].second.push_back(i);
                }
                tmp = c[tmp].long_suf;
            }
        }
    }
};

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    string text;
    cin >> text;
    int n;
    cin >> n;
    coras corasic;
    vector<pair<int, vector<int>>> ans(n);
    for (int i = 0; i < n; ++i) {
        string t;
        cin >> t;
        corasic.eat(t, i);
        ans[i].first = t.size();
    }
    corasic.build();
    //corasic.print_();
    corasic.work(text, ans);
    for (auto x : ans) {
        cout << x.second.size() << ' ';
        for (auto y : x.second) {
            cout << y + 2 - x.first << ' ';
        }
        cout << '\n';
    }
    return 0;
}
