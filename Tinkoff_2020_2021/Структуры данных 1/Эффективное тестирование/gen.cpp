#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> s;

int main() {
    srand(time(nullptr));
    int n, m;
    n = rand();
    m = rand();
    vector<pair<int, int>> outp = {make_pair(n, m)};
    for (int i = 0; i < m; ++i) {
        s.insert(i + 1);
    }
    for (int i = 0; i < n; ++i) {
        if (s.size() == 0) {
            outp[0].first = i - 1;
            break;
        }
        int a = rand() % s.size();
        int b = rand() % (s.size() - a) + a;
        if ((b - a) & 1)
            --b;
        outp.push_back({a + 1, b + 1});
        for (int i = b; i >= a; i -= 2) {
            int val = *s.find_by_order(i);
            s.erase(val);
        }
    }
    for (auto x : outp)
        cout << x.first << " " << x.second << '\n';
    return 0;
}
