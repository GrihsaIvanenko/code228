#include <bits/stdc++.h>

using namespace std;

const long long NONE = 9e18;

const long long MAXN = 1048566;

long long solve(pair<long long, long long> l1, pair<long long, long long> l2) {
    return (l2.second - l1.second) / (l1.first - l2.first);
}

long long f(long long x, long long k, long long b) {
    return k * x + b;
}

struct segtree {
    long long k, b;
    segtree *l = nullptr, *r = nullptr;
    segtree(long long lb, long long rb) {
        k = NONE;
        b = NONE;
        if (lb + 1 != rb) {
            long long mid = (lb + rb) >> 1;
            l = new segtree(lb, mid);
            r = new segtree(mid, rb);
        }
    }
    void add(long long k1, long long b1, long long lb, long long rb) {
        if (k == NONE) {
            k = k1;
            b = b1;
            return;
        }
        if (k == k1) {
            b = max(b, b1);
            return;
        }
        long long mid = (lb + rb) >> 1;
        if (f(mid, k, b) < f(mid, k1, b1)) {
            swap(k, k1);
            swap(b, b1);
        }
        if (solve({k, b}, {k1, b1}) < mid) {
            if (l != nullptr) {
                l->add(k1, b1, lb, mid);
            }
        } else if (solve({k, b}, {k1, b1}) > mid){
            if (r != nullptr) {
                r->add(k1, b1, mid, rb);
            }
        } else {
            if (f(mid - 1, k, b) < f(mid - 1, k1, b1)) {
                if (l != nullptr) {
                    l->add(k1, b1, lb, mid);
                }
            } else {
                if (r != nullptr) {
                    r->add(k1, b1, mid, rb);
                }
            }
        }
    }
    long long max_val(long long pos, long long lb, long long rb) {
        long long cur = 0;
        if (k == NONE) {
            return 0ll;
        }
        cur = max(cur, f(pos, k, b));
        long long mid = (lb + rb) >> 1;
        if (pos < mid) {
            if (l != nullptr){
                return max(l->max_val(pos, lb, mid), cur);
            } else {
                return cur;
            }
        } else {
            if (r != nullptr) {
                return max(r->max_val(pos, mid, rb), cur);
            } else {
                return cur;
            }
        }
    }
    void pr(long long lb, long long rb) {
        long long mid = (lb + rb) >> 1;
        cout << lb << " " << rb << ": (" << mid << ") ";
        if (k == NONE) {
            cout << "NULL NULL\n";
        } else {
            cout << k << " " << b << '\n';
        }
        if (l != nullptr) {
            l->pr(lb, mid);
        }
        if (r != nullptr) {
            r->pr(mid, rb);
        }
    }
};

int main(){
    segtree *li_chao = new segtree(-MAXN, MAXN);
    long long n;
    cin >> n;
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        long long x, c, t;
        cin >> x >> c >> t;
        long long cur = li_chao->max_val(x, -MAXN, MAXN);
        //cout << cur << endl;
        if (i != 0) {
            cur += (long long)t;
        }
        if (i == n - 1)ans = max(cur, ans);
        long long c1 = c;
        c1 *= (long long)x;
        //cout << c << " up " << -c1 + cur << endl;
        //cout << -c << " down " << c1 + cur << endl;
        li_chao->add(c, -c1 + cur, -MAXN, MAXN);
        li_chao->add(-c, c1 + cur, -MAXN, MAXN);
    }
    cout << ans << endl;
    return 0;
}
