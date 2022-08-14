#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 200001;

struct Node {
    int l, r, y;
    ll siz, F, L, S;
    Node(ll FF, ll LL, ll SS) {
        l = r = -1;
        F = FF;
        L = LL;
        S = SS;
        siz = (LL - FF) / SS + 1;
        y = (rand() << 15) + rand();
    }
    Node() {}
    ll kolvo_in() {
        return (L - F) / S + 1;
    }
};

Node d[MAXN];

int timer = 0, root = -1;

int new_v(ll L, ll R, ll S) {
    d[timer] = Node(L, R, S);
    return timer++;
}

ll sz(int A) {
    if (A == -1)
        return 0;
    return d[A].siz;
}

void update(int v) {
    d[v].siz = sz(d[v].l) + d[v].kolvo_in() + sz(d[v].r);
}

pair<int, int> left_split(int A, ll kolvo) {
    if (A == -1) {
        return {-1, -1};
    }
    if (sz(d[A].l) > kolvo) {
        pair<int, int> p = left_split(d[A].l, kolvo);
        d[A].l = p.second;
        update(A);
        return {p.first, A};
    }
    if (sz(d[A].l) + d[A].kolvo_in() > kolvo) {
        int B = d[A].l;
        d[A].l = -1;
        update(A);
        return {B, A};
    }
    kolvo -= (sz(d[A].l) + d[A].kolvo_in());
    pair<int, int> p = left_split(d[A].r, kolvo);
    d[A].r = p.first;
    update(A);
    return {A, p.second};
}

pair<int, int> right_split(int A, ll kolvo) {
    if (A == -1) {
        return {-1, -1};
    }
    if (sz(d[A].l) >= kolvo) {
        pair<int, int> p = right_split(d[A].l, kolvo);
        d[A].l = p.second;
        update(A);
        return {p.first, A};
    }
    if (sz(d[A].l) + d[A].kolvo_in() >= kolvo) {
        int B = d[A].r;
        d[A].r = -1;
        update(A);
        return {A, B};
    }
    kolvo -= (sz(d[A].l) + d[A].kolvo_in());
    pair<int, int> p = right_split(d[A].r, kolvo);
    d[A].r = p.first;
    update(A);
    return {A, p.second};
}

int merge(int A, int B) {
    if (A == -1)
        return B;
    if (B == -1)
        return A;
    if (d[A].y > d[B].y) {
        d[A].r = merge(d[A].r, B);
        update(A);
        return A;
    }
    d[B].l = merge(A, d[B].l);
    update(B);
    return B;
}

void total_split(int A, vector<int> &res) {
    if (A == -1) {
        return;
    }
    total_split(d[A].l, res);
    res.push_back(A);
    total_split(d[A].r, res);
    d[A].l = -1;
    d[A].r = -1;
    update(A);
}

void print(int v) {
    if (v == -1) {
        return;
    }
    print(d[v].l);
    cout << d[v].F << " lol " << d[v].L << " lol " << d[v].S << endl;
    print(d[v].r);
}

int main() {
    //  freopen("t.txt", "r", stdin);
    srand(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    ll m;
    cin >> n >> m;
    root = new_v(1, m, 1);
    for (int bebe = 0; bebe < n; ++bebe) {
        ll l, r;
        cin >> l >> r;
        --l;
        pair<int, int> p = left_split(root, l);
        l -= sz(p.first);
        r -= sz(p.first);
        root = p.first;
        pair<int, int> p1 = right_split(p.second, r);
        if (l > 0) {
            pair<int, int> p2 = right_split(p1.first, l);
            int F = new_v(d[p2.first].F, d[p2.first].F + (l - 1) * d[p2.first].S, d[p2.first].S);
            root = merge(root, F);
            d[p2.first].F += l * (d[p2.first].S);
            update(p2.first);
            p1.first = merge(p2.first, p2.second);
            r -= l;
        }
        pair<int, int> p2 = right_split(p1.first, 1);
        cout << d[p2.first].F << ' ';
        p1.first = merge(p2.first, p2.second);
        p2 = left_split(p1.first, r);
        r -= sz(p2.first);
        int head_fuck = -1;
        if (r > 0) {
            if (d[p2.second].F + r * d[p2.second].S <= d[p2.second].L)
                head_fuck = new_v(d[p2.second].F + r * d[p2.second].S, d[p2.second].L, d[p2.second].S);
            d[p2.second].L = d[p2.second].F + (r - 1) * d[p2.second].S;
            update(p2.second);
        }
        p1.first = merge(p2.first, p2.second);
        p2 = left_split(p1.first, sz(p1.first) - 1);
        cout << d[p2.second].L << '\n';
        p1.first = merge(p2.first, p2.second);
        vector<int> ver;
        total_split(p1.first, ver);
        ll tmp = 0;
        for (unsigned i = 0; i < ver.size(); ++i) {
            ll add = d[ver[i]].kolvo_in();
            if (tmp % 2 == 0) {
                d[ver[i]].F += d[ver[i]].S;
            }
            tmp += add;
            if (d[ver[i]].F <= d[ver[i]].L) {
                if (d[ver[i]].kolvo_in() % 2 == 0) {
                    d[ver[i]].L -= d[ver[i]].S;
                }
                if (d[ver[i]].S < m)
                    d[ver[i]].S += d[ver[i]].S;
                update(ver[i]);
                root = merge(root, ver[i]);
            }
        }
        root = merge(root, head_fuck);
        root = merge(root, p1.second);
    }
    return 0;
}
