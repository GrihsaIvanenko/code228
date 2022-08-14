#include <bits/stdc++.h>

using namespace std;

#define DEBUGs

using ld = double;
using ll = int;

const ld eps = 1e-6;

#ifdef DEBUGddfsfsdfsd
    const int MAXN = 8;
#else
    const int MAXN = 2048 * 16;
#endif // DEBUG

struct Point {
    ll x, y;
    Point() {}
    Point(ll xx, ll yy) {
        x = xx;
        y = yy;
    }
    void rot() {
        swap(x, y);
        x = -x;
    }
    void read() {
        cin >> x >> y;
    }
    pair<ld, ld> mid() {
        return {x / 2.0, y / 2.0};
    }
    void print() {
        cout << "(" << x << " " << y << ")";
    }
    void println() {
        print();
        cout << '\n';
    }
};

Point operator - (Point a, Point b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator + (Point a, Point b) {
    return Point(a.x + b.x, a.y + b.y);
}

struct Gpoint {
    ld x, y;
    Gpoint() {}
    Gpoint(ld xx, ld yy) {
        x = xx;
        y = yy;
    }
    Gpoint(Point a) {
        x = a.x;
        y = a.y;
    }
    Gpoint(pair<ld, ld> p) {
        x = p.first;
        y = p.second;
    }
    void rot() {
        swap(x, y);
        x = -x;
    }
    void read() {
        cin >> x >> y;
    }
    void print() {
        cout << "(" << x << " " << y << ")";
    }
    void println() {
        print();
        cout << '\n';
    }
};

bool eq(ld a, ld b) {
    return fabs(a - b) < eps;
}

ld gcross(Gpoint a, Gpoint b) {
    return a.x * b.y - a.y * b.x;
}

ll cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

ld gscal (Gpoint a, Gpoint b) {
    return a.x * b.x + a.y * b.y;
}

ll scal (Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

bool gcoline(Gpoint a, Gpoint b) {
    return eq(gcross(a, b), 0.0);
}

bool coline(Point a, Point b) {
    return cross(a, b) == 0;
}

Gpoint operator -(Gpoint a, Gpoint b) {
    return Gpoint(a.x - b.x, a.y - b.y);
}

Gpoint operator +(Gpoint a, Gpoint b) {
    return Gpoint(a.x + b.x, a.y + b.y);
}

struct Line {
    ld a, b, c;
    Line() {}
    Line(ld aa, ld bb, ld cc) {
        a = aa;
        b = bb;
        c = cc;
    }
    Line(Gpoint A, Gpoint B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
    void print() {
        cout << "(a " << a << "; b " << b << "; c " << c << ")";
    }
    void println() {
        print();
        cout << '\n';
    }
};

bool collinear(Line a, Line b) {
    Gpoint A = Gpoint(a.a, a.b);
    Gpoint B = Gpoint(b.a, b.b);
    return gcoline(A, B);
}

Gpoint intersect(Line a, Line b) {
   if (collinear(a, b)) {
        while (true) {
            cout << "TRATATA! TRATATA! MI VEZEM KOTA!!!\n";
        }
   }
   return Gpoint((b.c * a.b - a.c * b.b) / (b.b * a.a - a.b * b.a), (a.c * b.a - b.c * a.a) / (b.b * a.a - a.b * b.a));
}

ll duster(Point A, Point B) {
    Point C = B - A;
    return C.x * C.x + C.y * C.y;
}

ld dust(Point A, Point B) {
    return sqrt(duster(A, B));
}

ld gdust(Gpoint A, Gpoint B) {
    Gpoint C = B - A;
    return sqrt(C.x * C.x + C.y * C.y);
}

struct circle {
    Gpoint C;
    ld R;
    circle () {}
    circle (Gpoint Cen, ld Rad) {
        C = Cen;
        R = Rad;
    }
    void print() {
        cout << "Centre: ";
        C.print();
        cout << "; R: " << R << ";";
    }
    void println() {
        print();
        cout << '\n';
    }
    bool inside(Gpoint O) {
        return gdust(C, O) + eps < R;
    }
    bool outside(Gpoint O) {
        return gdust(C, O) - eps > R;
    }
    bool onsize(Gpoint O) {
        return fabs(gdust(C, O) - R) < eps;
    }
};

struct Triangle {
    Point A, B, C;
    Triangle() {}
    Triangle (Point &x, Point &y, Point &z) {
        A = x;
        B = y;
        C = z;
    }
    void read() {
        A.read();
        B.read();
        C.read();
    }
    void print() {
        cout << "A: ";
        A.print();
        cout << "; B";
        B.print();
        cout << "; C";
        C.print();
        cout << '\n';
    }
    circle Opis_okruznost() {
        Point v1 = C - A, v2 = B - A;
        Gpoint AA = Gpoint(A);
        Gpoint P1 = AA + v1.mid(), P2 = AA + v2.mid();
        v1.rot();
        v2.rot();
        Gpoint P3 = P1 + v1, P4 = P2 + v2;
        Line per1 = Line(P1, P3), per2 = Line(P2, P4);
        circle res;
        res.C = intersect(per1, per2);
        res.R = gdust(res.C, Gpoint(A));
        return res;
    }
};

struct Ksegtree {
    Ksegtree *ld, *lu, *rd, *ru;
    Gpoint HAHA_GRISHA;
    int sum;
    Ksegtree () {
        ld = nullptr;
        lu = nullptr;
        rd = nullptr;
        ru = nullptr;
        sum = 0;
    }
    void add(Point A, int dx = 0, int dy = 0, int ux = MAXN, int uy = MAXN) {
        HAHA_GRISHA = Gpoint(A);
        ++sum;
        if (dx + 1 == ux) {
            return;
        }
        int midx = (dx + ux) / 2, midy = (dy + uy) / 2;
        if (A.x >= midx) {
            if (A.y >= midy) {
                if (ru == nullptr)
                    ru = new Ksegtree();
                ru->add(A, midx, midy, ux, uy);
            } else {
                if (rd == nullptr)
                    rd = new Ksegtree();
                rd->add(A, midx, dy, ux, midy);
            }
        } else {
            if (A.y >= midy) {
                if (lu == nullptr)
                    lu = new Ksegtree();
                lu->add(A, dx, midy, midx, uy);
            } else {
                if (ld == nullptr)
                    ld = new Ksegtree();
                ld->add(A, dx, dy, midx, midy);
            }
        }
    }
    int ask_in_krug(circle MCK, int dx = 0, int dy = 0, int ux = MAXN, int uy = MAXN) {
        if (dx + 1 == ux) {
            if (MCK.inside(HAHA_GRISHA))
                return 1;
            return 0;
        }
        Gpoint LD = Gpoint(dx, dy), LU = Gpoint(dx, uy), RD = Gpoint(ux, dy), RU = Gpoint(ux, uy);
        if (MCK.inside(LD) && MCK.inside(LU) && MCK.inside(RD) && MCK.inside(RU)) {
            return sum;
        }
        long double dxx = dx;
        long double uxx = ux;
        long double dyy = dy;
        long double uyy = uy;
        /*if ((MCK.C.x + MCK.R + eps) < dxx || (MCK.C.x - MCK.R - eps) > uxx ||
            (MCK.C.y + MCK.R + eps) < dyy || (MCK.C.y - MCK.R - eps) > uyy)
            return 0;*/
        if (MCK.outside(LD) && MCK.outside(LU) && MCK.outside(RD) && MCK.outside(RU) &&
             (!(dxx - eps < MCK.C.x && MCK.C.x < uxx + eps)) &&
             (!(dyy - eps < MCK.C.y && MCK.C.y < uyy + eps))) {
            return 0;
        }
        int midx = (dx + ux) / 2, midy = (dy + uy) / 2;
        int res = 0;
        if (ld != nullptr)
            res += ld->ask_in_krug(MCK, dx, dy, midx, midy);
        if (rd != nullptr)
            res += rd->ask_in_krug(MCK, midx, dy, ux, midy);
        if (lu != nullptr)
            res += lu->ask_in_krug(MCK, dx, midy, midx, uy);
        if (ru != nullptr)
            res += ru->ask_in_krug(MCK, midx, midy, ux, uy);
        return res;
    }
    void print(int dx = 0, int dy = 0, int ux = MAXN, int uy = MAXN) {
        cout << dx << " " << dy << " " << ux << " " << uy << ": sum ";
        cout << sum << "; ";
        if (dx + 1 == ux) {
            cout << endl;
            return;
        }
        if (ld != nullptr)
            cout << "YES ";
        else
            cout << "NO ";
        if (rd != nullptr)
            cout << "YES ";
        else
            cout << "NO ";
        if (lu != nullptr)
            cout << "YES ";
        else
            cout << "NO ";
        int midx = (dx + ux) / 2, midy = (dy + uy) / 2;
        if (ru != nullptr)
            cout << "YES ";
        else
            cout << "NO ";
        cout << endl;
        if (ld != nullptr)
            ld->print(dx, dy, midx, midy);
        if (rd != nullptr)
            rd->print(midx, dy, ux, midy);
        if (lu != nullptr)
            lu->print(dx, midy, midx, uy);
        if (ru != nullptr)
            ru->print(midx, midy, ux, uy);
    }
};

void solve () {
    int n, m;
    cin >> n >> m;
    vector<Point> Ps(n);
    Ksegtree *root = new Ksegtree();
    for (int i = 0; i < n; ++i) {
        Ps[i].read();
        Ps[i].x += MAXN / 2;
        Ps[i].y += MAXN / 2;
        root->add(Ps[i]);
    }
    vector<Triangle> lovushki(m);
    bool good = true;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a;
        --b;
        --c;
        lovushki[i] = Triangle(Ps[a], Ps[b], Ps[c]);
        circle D = lovushki[i].Opis_okruznost();
        int res = root->ask_in_krug(D);
        if (res > 0)
            good = 0;
    }
    if (good)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
    #ifdef DEBUG
        freopen("sample.cpp", "r", stdin);
    #else
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #endif
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
