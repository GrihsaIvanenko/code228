#include <bits/stdc++.h>

using namespace std;

struct z {
    vector<int> g;
    int p, s, l, u, k;
    z() {
        g.assign(26, -1);
        p = 0;
        s = -1;
        l = 0;
        u = 0;
        k = 0;
    }
};

vector<z> g;

int a(int A, char t) {
    t -= 'a';
    int B = g.size();
    g.push_back(z());
    g[B].p = A;
    g[B].s = 0;
    g[B].l = g[A].l + 1;
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
        g[D].p = A;
        g[D].s = g[C].s;
        g[D].l = g[A].l + 1;
        g[B].s = D;
        g[C].s = D;
        for (; A != -1 && g[A].g[t] == C; A = g[A].s)
            g[A].g[t] = D;
        break;
    }
    return g[g[B].p].g[t];
}

vector<int> q;

void r(int A, int t) {
    if (A == 0)
        return;
    g[A].u = t;
    ++g[A].k;
    q[g[A].k - 1] = max(q[g[A].k - 1], g[A].l);
    if (g[g[A].p].u < t)
        r(g[A].p, t);
    if (g[g[A].s].u < t)
        r(g[A].s, t);
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int k;
    cin >> k;
    q.resize(k);
    vector<int> t(k);
    g.push_back(z());
    for (int i = 0; i < k; ++i) {
        string s;
        cin >> s;
        int v = 0;
        for (auto x : s)
            v = a(v, x);
        t[i] = v;
    }
    for (int i = 0; i < k; ++i)
        r(t[i], i + 1);
    for (int i = k - 2; i >= 0; --i)
        q[i] = max(q[i], q[i + 1]);
    for (int i = 1; i < k; ++i)
        cout << q[i] << '\n';
    return 0;
}
