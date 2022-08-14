#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e7 + 1e6;

int lp[MAXN];

vector<int> simple;

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    long long n;
    cin >> n;
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    for (int i = 0; i < MAXN; ++i)
        lp[i] = 0;
    for (int i = 2; i < MAXN; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            simple.push_back(i);
        }
        for (int j = 0; j < simple.size() && simple[j] <= lp[i] && simple[j] * i < MAXN; ++j)
            lp[simple[j] * i] = simple[j];
    }
    for i in range(2, MAXN):
        if lp[i] == 0:
            lp[i] = i
            simple.append(i)
         j = 0
         while j < len(simple) and simple[j] <= lp[i] and simple[j] * i < MAXN:
                lp[simple[j] * i] = simple[j]
                j = j + 1

    long long to = n * n + n;
    int ans = 0;
    for (long long i = n * n + (1 - n % 2); i <=to; ++(++i)) {
        for (auto x : simple) {
            if (i % x == 0)
                break;
            if (x * x > i) {
                ++ans;
                break;
            }
        }
    }
    cout << ans;
    return 0;
}
