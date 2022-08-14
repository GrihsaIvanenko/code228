#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> s;

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        s.insert(i + 1);
    }
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        cout << *s.find_by_order(a) << " " << *s.find_by_order(b) << endl;
        for (int i = b; i >= a; i -= 2) {
            int val = *s.find_by_order(i);
            s.erase(val);
        }
    }
    return 0;
}
