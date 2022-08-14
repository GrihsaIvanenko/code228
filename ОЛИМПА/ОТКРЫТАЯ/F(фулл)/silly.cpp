#include <bits/stdc++.h>

using namespace std;

bool good(int x) {
    int A = 0;
    if (x % 11 == 0)
        ++A;
    if (x % 13 == 0)
        ++A;
    if (x % 17 == 0)
        ++A;
    if (x % 19 == 0)
        ++A;
    return A == 2;
}

void solve() {
    int ANS = 33001, cnt = 0;
    for (int i = 22000; i <= 33000; ++i) {
        if (good(i)) {
            ANS = min(ANS, i);
            ++cnt;
        }
    }
    assert(ANS != 33001);
    cout << cnt << ' ' << ANS << '\n';
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
