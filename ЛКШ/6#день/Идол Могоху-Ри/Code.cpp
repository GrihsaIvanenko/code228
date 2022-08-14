#include <bits/stdc++.h>

using namespace std;

struct point {
    long long x, y;
    point() {}
    point(long long xx, long long yy) {
        x = xx;
        y = yy;
    }
};

point operator -(point a, point b) {
    return point(a.x - b.x, a.y - b.y);
}

point operator +(point a, point b) {
    return point(a.x + b.x, a.y + b.y);
}

long long cros(point a, point b) {
    return a.x * b.y - b.x * a.y;
}

long long superlen(point a) {
    return a.x * a.x + a.y * a.y;
}

bool cmp(point a, point b) {
    return cros(a, b) > 0;
}

bool in(point t, vector<point> &v) {
    if (cros(v[0], t) >= 0 && cros(t, v.back()) >= 0) {
        auto pose = upper_bound(v.begin(), v.end(), t, cmp);
        int pos = pose - v.begin();
        if (pos == v.size()) {
            return superlen(v[pos - 1]) >= superlen(t);
        }
        return (cros(v[pos] - v[pos - 1], t - v[pos - 1]) >= 0);
    }
    return false;
}

void read(vector<point> &v) {
    int n;
    cin >> n;
    vector<point> t;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        t.push_back(point(a, b));
    }
    int it = 0;
    for (int i = 0; i < n; ++i) {
        if (t[it].y > t[i].y || (t[it].y == t[i].y && t[it].x > t[i].x)) {
            it = i;
        }
    }
    point base = t[it];
    for (int i = it; i < n - 1; ++i) {
        v.push_back(t[i + 1] - t[i]);
    }
    v.push_back(t[0] - t.back());
    for (int i = 0; i < it; ++i) {
        v.push_back(t[i + 1] - t[i]);
    }
    v.push_back(base);
}

void menclovs_sum(vector<point> &res, vector<point> &A, vector<point> &B) {
    int Ait = 0, Bit = 0;
    for (int i = 0; i < A.size() + B.size(); ++i) {
        point push;
        if (Ait == A.size()) {
            push = B[Bit++];
        } else if (Bit == B.size()) {
            push = A[Ait++];
        } else{
            if (cros(A[Ait], B[Bit]) > 0) {
                push = A[Ait++];
            } else{
                push = B[Bit++];
            }
        }
        if (res.size() > 0 && cros(push, res.back()) == 0){
            push = push + res.back();
            res.pop_back();
        }
        res.push_back(push);
    }
}

void solve() {
    vector<point> A, B, C;
    read(A); read(B); read(C);
    point tmp = A.back() + B.back() + C.back();
    A.pop_back();
    B.pop_back();
    C.pop_back();
    vector<point> res, preres;
    menclovs_sum(preres, A, B);
    A.clear();
    B.clear();
    menclovs_sum(res, preres, C);
    C.clear();
    preres.clear();
    vector<point> polygon;
    point sum = point(0, 0);
    for (int i = 0; i < res.size() - 1; ++i) {
        sum = sum + res[i];
        polygon.push_back(sum);
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a *= 3;
        b *= 3;
        point t = point(a, b);
        t = t - tmp;
        if (in(t, polygon)) {
            cout << "YES\n";
        } else{
            cout << "NO\n";
        }
    }
}

int main() {
    solve();
    return 0;
}
