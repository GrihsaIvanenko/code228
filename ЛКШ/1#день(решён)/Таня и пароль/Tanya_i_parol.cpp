#include <bits/stdc++.h>

using namespace std;

const int MAXN = 62 * 62;

#define x first
#define y second

multiset<int> g[MAXN];

int in[MAXN];

vector<pair<int, int>> ans;

char get_ch(int t) {
    if (t < 26) {
        return char('A' + t);
    }
    if (t < 52) {
        return char('a' + t - 26);
    }
    return char('0' + t - 52);
}

void dfs(int v) {
    while (!g[v].empty()) {
        int to = *g[v].begin();
        g[v].erase(g[v].find(to));
        dfs(to);
        ans.push_back({v, to});
    }
}

void solve(){
    for (int i = 0; i < MAXN; ++i) {
        in[i] = 0;
    }
    int n, start;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string t;
        cin >> t;
        int tmp[3];
        for (int j = 0; j < 3; ++j) {
            if (t[j] >= 'a' && t[j] <= 'z') {
                tmp[j] = t[j] - 'a' + 26;
            } else if (t[j] >= '0' && t[j] <= '9') {
                tmp[j] = t[j] - '0' + 52;
            } else {
                tmp[j] = t[j] - 'A';
            }
        }
        int v1 = tmp[0] * 62 + tmp[1];
        int v2 = tmp[1] * 62 + tmp[2];
        start = v1;
        g[v1].insert(v2);
        in[v2]++;
    }
    for (int i = 0; i < MAXN; ++i) {
        if (g[i].size() - in[i] == 1) {
            start = i;
        }
    }
    dfs(start);
    reverse(ans.begin(), ans.end());
    /*for(int i = 0; i < ans.size(); ++i){
        cout << get_ch(ans[i].x / 62) << get_ch(ans[i].x % 62) << " " << get_ch(ans[i].y / 62) << get_ch(ans[i].y % 62) << endl;
    }*/
    string answer;
    answer.push_back(get_ch(ans[0].x / 62));
    answer.push_back(get_ch(ans[0].x % 62));
    for (int i = 0; i < ans.size(); ++i) {
        answer.push_back(get_ch(ans[i].y % 62));
        if (i != 0) {
            if (ans[i - 1].y != ans[i].x) {
                cout << "NO\n";
                return;
            }
        }
    }
    if (answer.size() != n + 2) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n" << answer << endl;
}

int main() {
    freopen("password.in", "r", stdin);
    freopen("password.out", "w", stdout);
    solve();
    return 0;
}
