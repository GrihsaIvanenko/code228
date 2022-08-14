#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    set<pair<int, int>>s;
    set<int> can;
    s.insert({-(n<<1), k});
    while (!s.empty()) {
        pair<int, int> p = *s.begin();
        s.erase(s.begin());
        if (p.second == 0 || p.first == 0) {
           can.insert(-p.first);
           continue;
        }
        if ((-p.first) % 2 == 0)s.insert({p.first / 2, p.second - 1});
        s.insert({p.first + 1, p.second - 1});
    }
    cout << can.size() << '\n';
    cout.precision(1);
    for (auto x : can) {
        cout << fixed << (long double)x / 2.0 << ' ';
    }
    cout << '\n';
    return 0;
}
