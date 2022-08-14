#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

const int MAXN = 131072;

tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> t[MAXN + MAXN];

void add(int pos, pair<int, int> val) {
    pos += MAXN;
    while (pos) {
        t[pos].insert(val);
        pos >>= 1;
    }
}

void del(int pos, pair<int, int> val) {
    pos += MAXN;
    while (pos)  {
        t[pos].erase(val);
        pos >>= 1;
    }
}

int ask(int l, int r, int x) {
    l += MAXN;
    r += MAXN;
    int ans = 0;
    while (l < r) {
        if (l & 1) {
            ans += t[l].size() - t[l].order_of_key({x, -1});
            ++l;
        }
        if (r & 1) {
            --r;
            ans += t[l].size() - t[r].order_of_key({x, -1});
        }
        l >>= 1;
        r >>= 1;
    }
    return ans;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        add(i, {v[i], i});
    }
    cin >> n;
    for (int i = 0; i < n; ++i) {
        char t;
        cin >> t;
        if (t == 'C') {
            int x, z;
            cin >> x >> z;
            --x;
            del(x, {v[x], x});
            v[x] = z;
            add(x, {v[x], x});
        } else {
            int x1, y1, x2, y2, A, B;
            cin >> x1 >> y1 >> x2 >> y2;
            --x1;
            A = ask(x1, x2, (y1 + y2 + 2)>>1);
            B = x2 - x1 - ask(x1, x2, (y1 + y2) >> 1);
            if (A == B)
                cout << "0\n";
            else if (A < B)
                cout << "1\n";
            else
                cout << "2\n";
        }
    }
    return 0;
}
