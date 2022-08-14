#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main () {
    int n;
    cin >> n;
    map<pair<int, int>, long long> q_of_lines;
    map<pair<pair<int, int>, int>, long long> Flines;
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b, c, q;
            cin >> a >> b >> c >> q;
            if (a < 0) {
                a = -a;
                b = -b;
                c = -c;
            } else if (a == 0 && b < 0) {
                a = -a;
                b = -b;
                c = -c;
            }
            int tmp = gcd(abs(a), gcd(abs(b), abs(c)));
            a /= tmp;
            b /= tmp;
            c /= tmp;
            sum += q;
            Flines[{{a, b}, c}] += q;
            q_of_lines[{a / gcd(abs(a), abs(b)), b / gcd(abs(a), abs(b))}] += q;
        } else {
            int a, b, c;
            cin >> a >> b >> c;
            if (a < 0) {
                a = -a;
                b = -b;
                c = -c;
            } else if (a == 0 && b < 0) {
                a = -a;
                b = -b;
                c = -c;
            }
            int tmp = gcd(abs(a), gcd(abs(b), abs(c)));
            a /= tmp;
            b /= tmp;
            c /= tmp;
            if (Flines[{{a, b}, c}] != 0) {
                cout << "inf";
            } else {
                cout << sum - q_of_lines[{a  / gcd(abs(a), abs(b)), b / gcd(abs(a), abs(b))}];
            }
            cout << '\n';
        }
    }
    return 0;
}
