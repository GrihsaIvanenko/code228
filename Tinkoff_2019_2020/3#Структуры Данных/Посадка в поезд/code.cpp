#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

int n;

int maine () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    vector<tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>> doshka(n + 1);
    for (int i = 0; i < n; ++i) {
        int w, pos;
        cin >> pos >> w;
        int poss = pos, ans = 0;
        for (; poss > 0; poss -= (poss & -poss))
            ans += (int)doshka[poss].size() - doshka[poss].order_of_key(w);
        cout << ans << ' ';
        for (; pos <= n; pos += (pos & -pos))
            doshka[pos].insert(w);
    }
    cout << endl;
    return 0;
}

int main() {
    while(cin >> n) {
        maine();
    }
    return 0;
}
