#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500000, SZ = 1000, SZ1 = 5000;

pair<int, int> val[MAXN], sorted[MAXN], cash1[SZ], cash2[SZ];

struct block {
    int l, r, push, rev, srt;
    block(int x) {
        l = r = x;
        push = -1;
        rev = 0;
        srt = 0;
    }
    int sz() {
        return r - l;
    }
    void add_back(int x) {
        sorted[r] = val[r] = {x, r};
        ++r;
    }
    int get(int x) {
        if (push != -1) {
            if (push >= x)
                return r - l;
            return 0;
        }
        int ans = 0;
        if (!srt) {
            for (int i = l; i < r; ++i)
                sorted[i] = val[i];
            sort(sorted + l, sorted + r);
            srt = 1;
        }
        return r - (lower_bound(sorted + l, sorted + r, make_pair(x, -1)) - sorted);
    }
    void print() {
        cout << "l: " << l << " ;r " << r << " ;push " << push << " ; rev " << rev << " ;str " << srt << endl;
        for (int i = l; i < r; ++i)
            cout << val[i].first << " " << val[i].second << " val; ";
        cout << endl;
        for (int i = l; i < r; ++i)
            cout << sorted[i].first << " " << sorted[i].second << " sor; ";
        cout << endl;
    }
};

vector<block> parts;

block split(block &t, int vale) {
    int L1 = t.l;
    int R1 = t.l + vale;
    int L2 = t.l + vale;
    int R2 = t.r;
    block res = block(L2);
    res.r = R2;
    t.l = L1;
    t.r = R1;
    if (t.push != -1) {
        res.push = t.push;
        return res;
    }
    if (t.srt == 0) {
        if (t.rev) {
           res.rev = 1;
           res.l = L1;
           res.r = R2 - vale;
           t.l = R2 - vale;
           t.r = R2;
        }
        return res;
    }
    if (t.rev) {
        res.srt = 0;
        t.srt = 0;
        res.rev = 1;
        res.l = L1;
        res.r = R2 - vale;
        t.l = R2 - vale;
        t.r = R2;
    } else {
        t.srt = 0;
        for (int i = L1 + 1; i < R2; ++i)
            assert(sorted[i] >= sorted[i - 1]);
    }
    return res;
}

int main() {
    // freopen("t.cpp", "r", stdin);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    int timer = 0;
    parts.push_back(block(0));
    for (int i = 0; i < n; ++i) {
        if (timer == SZ) {
            parts.push_back(block(i));
            timer = 0;
        }
        int x;
        cin >> x;
        parts.back().add_back(x);
        ++timer;
    }
    int n1 = n;
    swap(n1, n);
    int q;
    cin >> q;
    for (int Q = 0; Q < q; ++Q) {
        int L, R;
        string s;
        cin >> s >> L >> R;
        --L;
        R -= L;
        int id = 0;
        for (; L;) {
            if (parts[id].sz() <= L) {
                L -= parts[id].sz();
                ++id;
            } else {
                parts.insert(parts.begin() + id + 1, split(parts[id], L));
                ++id;
                L = 0;
            }
        }
        int LL = id;
        for (; R; ) {
            if (parts[id].sz() <= R) {
                R -=  parts[id].sz();
                ++id;
            } else {
                parts.insert(parts.begin() + id + 1, split(parts[id], R));
                ++id;
                R = 0;
            }
        }
        int RR = id;
        if (s[0] == 'g') {
            int x, ans = 0;
            cin >> x;
            for (; LL < RR; ++LL)
                ans += parts[LL].get(x);
            cout << ans << '\n';
        } else if (s[0] == 's') {
            int x;
            cin >> x;
            for (; LL < RR; ++LL)
                parts[LL].push = x;
        } else {
            reverse(parts.begin() + LL, parts.begin() + RR);
            for (; LL < RR; ++LL)
                parts[LL].rev ^= 1;
        }
        if (Q % SZ1 == SZ1 - 1) {
            timer = 0;
            for (auto x : parts) {
                if (x.push != -1) {
                    int kolvo = x.sz(), toto = x.push;
                    for (int i = 0; i < kolvo; ++i) {
                        sorted[timer] =  {toto, timer};
                        ++timer;
                    }
                } else if (x.rev) {
                    for (int i = x.r - 1; i >= x.l; --i)
                        sorted[timer++] = val[i];
                } else {
                    for (int i = x.l; i < x.r; ++i)
                        sorted[timer++] = val[i];
                }
            }
            swap(sorted, val);
            vector<block> new_parts;
            for (int i = 0; i < n; i += SZ) {
                new_parts.push_back(block(i));
                new_parts.back().r = min(i + SZ, n);
            }
            swap(new_parts, parts);
        }
     }
    return 0;
}
