#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

long long cross(pair<long long, long long> A, pair<long long, long long> B) {
    return A.x * B.y - A.y * B.x;
}

long long gcd(long long a, long long b) {
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

pair<long long, long long> operator -(pair<long long, long long> A, pair<long long, long long> B) {
    return {A.x - B.x, A.y - B.y};
}

int main () {
    int n;
    cin >> n;
    vector<pair<long long, long long>> polygon(n);
    for (int i = 0; i < n; ++i)
        cin >> polygon[i].x >> polygon[i].y;
    long long ans_s = cross(polygon[0], polygon.back());
    long long tmp = gcd(abs((polygon.back() - polygon[0]).x), abs((polygon.back() - polygon[0]).y));
    for (int i = 0; i < n - 1; ++i) {
        ans_s += cross(polygon[i + 1], polygon[i]);
        tmp += gcd(abs((polygon[i + 1] - polygon[i]).x), abs((polygon[i + 1] - polygon[i]).y));
    }
    if (ans_s < 0)
        ans_s = -ans_s;
    ans_s += 2;
    cout << (ans_s - tmp) / 2 << endl;
    return 0;
}
