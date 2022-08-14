#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    int q;
    cin >> q;
    for (int AA = 0; AA < q; ++AA){
        int t;
        cin >> t;
        if (t) {
            int l, r, k;
            cin >> l >> r >> k;
            --l;
            --r;
            bool good = true;
            for (int i = 0; i < k && good; ++i)
                if (v[i + l] != v[i + r])
                    good = false;
            if (good)
                cout << "+";
            else
                cout << "-";
        } else {
            int l, r, c;
            cin >> l >> r >> c;
            --l;
            for (; l < r; ++l)
                v[l] = c;
        }
    }
    return 0;
}
