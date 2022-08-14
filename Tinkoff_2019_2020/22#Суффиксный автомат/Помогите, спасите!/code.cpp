#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct z {
    vector<int> g;
    int p, s, l;
    z() {
        g.assign(26, -1);
        p = 0;
        s = -1;
        l = 0;
    }
};

vector<z> g;

int l = 0;

ll r = 0;

int a(int A, char t) {
    t -= 'a';
    int B = g.size();
    g.push_back(z());
    g[B].l = g[A].l + 1;
    g[B].s = 0;
    g[B].p = A;
    for (; A != -1; A = g[A].s) {
        if (g[A].g[t] == -1) {
            g[A].g[t] = B;
            continue;
        }
        int C = g[A].g[t];
        if (g[C].p == A) {
            g[B].s = C;
            break;
        }
        int D = g.size();
        g.push_back(z());
        g[D].g = g[C].g;
        g[D].s = g[C].s;
        g[D].p = A;
        g[D].l = g[A].l + 1;
        g[C].s = D;
        g[B].s = D;
        for (; A != -1 && g[A].g[t] == C; A = g[A].s)
            g[A].g[t] = D;
        break;
    }
    r += (long long)(g[B].l - g[g[B].s].l);
    return g[g[B].p].g[t];
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    g.push_back(z());
    string s;
    cin >> s;
    for (auto x : s) {
        l = a(l, x);
        cout << r << '\n';
    }
    return 0;
}
