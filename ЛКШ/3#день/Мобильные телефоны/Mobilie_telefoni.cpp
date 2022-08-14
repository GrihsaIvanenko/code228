#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> fen;

int sz;

void add(int x, int y, int k) {
    for (; x < sz; x = x | (x + 1))
        for (int j = y; j < sz; j = j | (j + 1))
            fen[x][j] += k;
}

int sum(int x, int y) {
    int ans = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            ans += fen[x][j];
    return ans;
}

void solve() {
    int t;
    cin >>  t;
    while (t != 3) {
        if (t == 0) {
            cin >> sz;
            fen.assign(sz, vector<int>(sz));
        }
        else if (t == 1) {
            int a, b, k;
            cin >> a >> b >> k;
            add(a, b, k);
        }
        else if (t == 2) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            --a;
            --b;
            cout << sum(c, d) + sum(a, b) - sum(c, b) - sum(a, d) << '\n';
        }
        cin >> t;
    }
}

int main() {
    solve();
    return 0;
}
