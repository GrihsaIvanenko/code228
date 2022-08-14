#include <bits/stdc++.h>

using namespace std;

int gogo(vector<vector<int>> &pole, int nx, int ny, int dx, int dy) {
    if (nx >= (int)pole.size()) {
        return 1;
    }
    if (nx < 0)
        return 0;
    if (ny < 0)
        return 0;
    if (ny >= pole[0].size())
        return 0;
    if (pole[nx][ny]) {
        if (dx == 1 && dy == 0) {
            if (pole[nx][ny] == 1) {
                dx = 0;
                dy = 1;
            } else {
                dx = 0;
                dy = -1;
            }
        } else if (dx == -1 && dy == 0) {
            if (pole[nx][ny] == 1) {
                dx = 0;
                dy = -1;
            } else {
                dx = 0;
                dy = 1;
            }
        } else if (dx == 0 && dy == 1) {
            if (pole[nx][ny] == 1) {
                dx = 1;
                dy = 0;
            } else {
                dx = -1;
                dy = 0;
            }
        } else if (dx == 0 && dy == -1) {
            if (pole[nx][ny] == 1) {
                dx = -1;
                dy = 0;
            } else {
                dx = 1;
                dy = 0;
            }
        } else {
            assert(false);
        }
    }
    return gogo(pole, nx + dx, ny + dy, dx, dy);
}

void cnt(vector<vector<int>> &pole) {
    int m = pole[0].size();
    int ans = 0;
    for (int i = 0; i < m; ++i)
        ans += gogo(pole, 0, i, 1, 0);
    cout << ans << '\n';
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> pole(n, vector<int>(m));
    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        pole[x - 1][y - 1] = t;
        cnt(pole);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (pole[i][j] == 0)
                    cout << '.';
                else if (pole[i][j] == 1)
                    cout << '\\';
                else
                    cout << '/';
            }
            cout << endl;
        }
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
