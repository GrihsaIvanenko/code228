#include <bits/stdc++.h>

using namespace std;

void rip() {
    cout << "Impossible";
    exit(0);
}

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void make_good(pair<long long, long long> &p, long long a, long long b) {
    if (p.first < 0) {
       long long change = (p.first - b + 1) / b;
       p.first -= b * change;
       p.second += a * change;

    } else {
        long long change = p.first / b;
        p.first -= change * b;
        p.second += change * a;
    }
}

pair<long long, long long> solve_ab1(long long a, long long b) {
    if (b == 1) {
        return {0, 1};
    }
    pair<long long, long long> tmp = solve_ab1(b, a % b);
    tmp = {tmp.second, (1ll - tmp.second * a) / b};
    make_good(tmp, a, b);
    return tmp;
}

pair<long long, long long> solve_abc(long long a, long long b, long long c) {
    long long gd = gcd(a, b);
    if (c % gd != 0)
        rip();
    a /= gd;
    b /= gd;
    c /= gd;
    pair<long long, long long> presolution = solve_ab1(a, b);
    presolution.first *= c;
    presolution.second *= c;
    make_good(presolution, a, b);
    return presolution;
}

int main () {
    long long a, b, c;
    cin >> a >> b >> c;
    pair<long long, long long> ans = solve_abc(a, b, c);
    cout << ans.first << ' ' << ans.second;
    return 0;
}

