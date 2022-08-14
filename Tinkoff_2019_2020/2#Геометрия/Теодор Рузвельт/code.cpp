#include <bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
    Point () {}
    Point (long long a, long long b) {
        x = a;
        y = b;
    }
};

Point operator -(Point A, Point B) {
    return Point(A.x - B.x, A.y - B.y);
}

long long suplen(Point A) {
    return A.x * A.x + A.y * A.y;
}

long long cross (Point A, Point B) {
    return A.x * B.y - A.y * B.x;
}

bool cmp (Point A, Point B) {
    return cross(A, B) > 0;
}

struct Polygon {
    vector<Point> v;
    Point base;
    Polygon () {}
    Polygon (vector<Point> &pp) {
        int id = 0;
        for (int i = 1; i < pp.size(); ++i) {
            if (pp[id].y > pp[i].y || (pp[id].y == pp[i].y && pp[id].x > pp[i].x)) {
                id = i;
            }
        }
        base = pp[id];
        for (int i = id + 1; i < pp.size(); ++i) {
            v.push_back(pp[i] - base);
        }
        for (int i = 0; i < id; ++i) {
            v.push_back(pp[i] - base);
        }
    }
    bool in(Point A) {
        A = A - base;
        if (cross(v[0], A) >= 0 && cross(A, v.back()) >= 0) {
            int it = upper_bound(v.begin(), v.end(), A, cmp) - v.begin();
            if (it == v.size()) {
                return suplen(v.back()) >= suplen(A);
            }
            return (cross(v[it] - v[it - 1], A - v[it - 1]) >= 0);
        }
        return false;
    }
};

int main () {
    int n, m, k;
    cin >> n >> m >> k;
    vector<Point> v(n);
    for (int i = 0; i < n; ++i) {
        long long a, b;
        cin >> a >> b;
        v[i] = Point(a, b);
    }
    Polygon P = Polygon(v);
    for (int i = 0; i < m; ++i) {
        Point x;
        cin >> x.x >> x.y;
        if (P.in(x))
            --k;
    }
    if (k <= 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
