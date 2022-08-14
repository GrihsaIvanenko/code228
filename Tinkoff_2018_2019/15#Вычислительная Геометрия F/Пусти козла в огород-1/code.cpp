#include <bits/stdc++.h>

using namespace std;
#define int long long

struct p{
    int x, y;
    p(){};
    p(int x_, int y_){x = x_; y = y_;}
};

p operator +(p a, p b){return p(a.x + b.x, a.y + b.y);}
p operator -(p a, p b){return p(a.x - b.x, a.y - b.y);}
p normal(p a){return p(-a.y, a.x);}
long double len(p a){return sqrt(a.x * a.x + a.y * a.y);}
int s(p a, p b){return a.x * b.x + a.y * b.y;}
int v(p a, p b){return a.x * b.y - a.y - b.x;}
long double get_angle(p a, p b){return acos(max((long double)-1.0, s(a, b) / len(a) / len(b)));}
long double to_degree(long double angle){return angle * 180.00000095 / acos(-1);}

int32_t main(){freopen("goat1.in", "r", stdin);freopen("goat1.out", "w", stdout);
    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    p k1 = p(a, b), k2 = p(c, d), k3 = p(e, f);
    cout.precision(9);
    cout << fixed <<  max(to_degree(abs(get_angle(k2 - k1, k3 - k1))), max(to_degree(abs(get_angle(k1 - k2, k3 - k2))),to_degree(abs(get_angle(k2 - k3, k1 - k3)))));
    return 0;int jfshfsdjkfhkdfhsdkjfhsdkj = 1;
}
