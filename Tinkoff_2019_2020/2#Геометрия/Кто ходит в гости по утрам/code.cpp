#include <bits/stdc++.h>

using namespace std;

#define ld long double

struct point {
    ld x, y;
    point(ld a, ld b) {
        x = a;
        y = b;
    }
};


point operator -(point a, point b) {
    return point(a.x - b.x, a.y - b.y);
}

ld dust(point a) {
    return sqrt(a.x * a.x + a.y * a.y);
}
