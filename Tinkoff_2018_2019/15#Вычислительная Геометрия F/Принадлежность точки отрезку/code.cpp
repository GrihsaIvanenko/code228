#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    Point() {}
    Point(ll xx, ll yy) {
        x = xx;
        y = yy;
    }
    void read() {
        cin >> x >> y;
    }
};

Point operator + (Point A, Point B) {
    return Point(A.x + B.x, A.y + B.y);
}

Point operator - (Point A, Point B) {
    return Point(A.x - B.x, A.y - B.y);
}

ll cross(Point A, Point B) {
    return A.x * B.y - A.y * B.x;
}

ll scal(Point A, Point B) {
    return A.x * B.x + A.y * B.y;
}

int main() {
    freopen("point3.in", "r", stdin);
    freopen("point3.out", "w", stdout);
    Point A, B, C;
    A.read();
    B.read();
    C.read();
    if (cross(B - A, C - A)) {
        cout << "NO\n";
        return 0;
    }
    if (scal(B - A, C - A) <= 0) {
        cout << "YES\n";
    } else
        cout << "NO\n";
    return 0;
}
