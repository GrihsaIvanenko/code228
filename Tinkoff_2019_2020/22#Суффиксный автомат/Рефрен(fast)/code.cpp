#include <bits/stdc++.h>

using namespace std;

struct z {
    int suf, l, p;
    bool used;
    long long dp, cur;
    vector<int> go;
    z() {
        go.assign(10, 0);
        suf = 0;
        l = 0;
        dp = 0;
        cur = 0;
        p = 0;
        used = false;
    }
};

vector<z> a;

int add(int A, int x) {
    int B = a.size();
    a.push_back(z());
    a[B].suf = 1;
    a[B].l = a[A].l + 1;
    a[B].p = A;
    for (; A; A = a[A].suf) {
        if (!a[A].go[x]) {
            a[A].go[x] = B;
            continue;
        }
        int C = a[A].go[x];
        if (a[C].l == a[A].l + 1) {
            a[B].suf = C;
            break;
        }
        int D = a.size();
        a.push_back(z());
        a[D].go = a[C].go;
        a[D].suf = a[C].suf;
        a[C].suf = a[B].suf = D;
        a[D].p = A;
        a[D].l = a[A].l + 1;
        for (; A && a[A].go[x] == C; A = a[A].suf)
            a[A].go[x] = D;
        break;
    }
    return B;
}

int last = 1;

void vosst(int v) {
    if (v == 1)
        return;
    vosst(a[v].p);
    for (int i = 0; i < 10; ++i)
        if (a[a[v].p].go[i] == v)
            cout << i + 1 << ' ';
}

void dfs(int v) {
    a[v].used = 1;
    for (auto x : a[v].go) {
        if (x == 0)
            continue;
        if (!a[x].used)
            dfs(x);
        a[v].dp += a[x].dp;
    }
    a[v].cur = a[v].dp * (long long)a[v].l;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    a.push_back(z());
    a.push_back(z());
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        --x;
        last = add(last, x);
    }
    while (last != 1) {
        ++a[last].dp;
        last = a[last].suf;
    }
    dfs(last);
    int cur = 1;
    for (int i = 2; i < (int)a.size(); ++i)
        if (a[cur].cur < a[i].cur)
            cur = i;
    cout << a[cur].cur << '\n' << a[cur].l << '\n';
    vosst(cur);
    cout << '\n';
    return 0;
}
