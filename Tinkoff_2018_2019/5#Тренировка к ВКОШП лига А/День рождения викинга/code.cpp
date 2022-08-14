#include <bits/stdc++.h>

using namespace std;

int main() {
    long double R, L;
    cin >> R >> L;
    long long l, r;
    l = L * 1000.0, r = R * 1000.0;
    cout.precision(50);
    cout << fixed << -R << " " << 0.0 << endl;
    if (L >= R * 2.0) {
       cout << R << " " << 0.0 << endl;
       return 0;
    }
    long double t = l * l - r * r - r * r;
    t /= R;
    t /= 2000000.0;
    cout << fixed << t << " " << sqrt(R * R - t * t)<< endl;
    return 0;
}
