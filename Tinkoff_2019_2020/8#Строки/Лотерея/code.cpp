#include <bits/stdc++.h>

using namespace std;

vector<int> ifwin;

int k;

struct part {
    vector<int> go;
    int term, from;
    long long dp = 0;
    bool ban;
    part () {
        ban = false;
        term = 0;
        dp = 0;
        from = -1;
        go.resize(k, -1);
    }
};

struct trie {
    vector<part> b;
    trie () {
        b.resize(1);
    }
    void eat(string & s) {
        int id = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (b[id].go[s[i] - '0'] == -1) {
                part tmp;
                b[id].go[s[i] - '0'] = b.size();
                b.push_back(tmp);
            }
            id = b[id].go[s[i] - '0'];
            ++b[id].term;
        }
        b[id].ban |= true;
    }
    void dpp () {
        for (int i = 0; i < k; ++i)
            if (b[0].go[i] != -1)
                dfs(b[0].go[i]);
        if (b[0].go[0] != -1)
            b[0].dp = b[b[0].go[0]].dp;
        else
            b[0].dp = 0;
        b[0].from = 0;
        for (int i = k - 1; i > 0; --i)
            if (b[0].go[i] != -1) {
                if (b[b[0].go[i]].dp < b[0].dp) {
                    b[0].dp = b[b[0].go[i]].dp;
                    b[0].from = i;
                }
            } else {
                b[0].dp = 0;
                b[0].from = i;
            }
    }
    void dfs (int v, int deep = 0) {
        if (b[v].ban) {
            b[v].dp = (long long)ifwin[deep] * (long long)b[v].term;
            return;
        }
        for (int i = 0; i < k; ++i)
            if (b[v].go[i] != -1)
                dfs(b[v].go[i], deep + 1);
        b[v].from = 0;
        for (int i = 1; i < k; ++i)
            if (get_dp(v, i, deep) < get_dp(v, b[v].from, deep))
                b[v].from = i;
        b[v].dp = get_dp(v, b[v].from, deep);
    }
    long long get_dp(int v, int i, long long deep) {
        if (b[v].go[i] == -1)
            return (long long)b[v].term * (long long)ifwin[deep];
        return (long long)(b[v].term - b[b[v].go[i]].term) * (long long)ifwin[deep] + (long long)b[b[v].go[i]].dp;
    }
    void print (int v = 0) {
        cout << v << " " << b[v].dp << " " << b[v].from << " " << b[v].term << endl;
        for (auto x : b[v].go)
            if (x != -1)
                print(x);
    }
    void print_ans(int k) {
        int v = 0;
        while (v != -1 && b[v].from != -1) {
            cout << char('0' + b[v].from);
            v = b[v].go[b[v].from];
            --k;
        }
        while (v == -1 && k > 0) {
            cout << 0;
            --k;
        }
    }
};

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m >> k;
    ifwin.resize(m);
    for (int i = 0; i < m; ++i)
        cin >> ifwin[i];
    trie bor;
    for (int i = 0; i < n; ++i) {
        string t;
        cin >> t;
        bor.eat(t);
    }
    bor.dpp();
    bor.print_ans(m);
    cout << '\n' << bor.b[0].dp << '\n';
    return 0;
}
