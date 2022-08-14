#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200001;

int fenv[MAXN];

void add(int a, int b) {
    for (; a < MAXN; a += (a & -a))
        fenv[a] += b;
}

int has(int pos) {
    int ans = 0;
    for (; pos > 0; pos -= (pos & -pos))
        ans += fenv[pos];
    return ans;
}

int get_pos(int val) {
    int ans = 0;
    for (int i = 17; i >= 0; --i)
        if (ans + (1 << i) < MAXN && fenv[ans + (1 << i)] < val) {
            val -= fenv[ans + (1 << i)];
            ans += (1 << i);
        }
    return ans + 1;
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
        v[i] = !v[i];
        if (v[i])
            add(i + 1, 1);
    }
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; ++q) {
        char t;
        cin >> t;
        if (t == 'u') {
            int pos, val;
            cin >> pos >> val;
            val = !val;
            if (v[pos - 1] != val)
                add(pos, val - v[pos - 1]);
            v[pos - 1] = val;
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            --l;
            int R = has(r), L = has(l);
            if (R < L + k) {
                cout << "-1 ";
            } else {
                cout << get_pos(L + k) << ' ';
            }
        }
    }
    cout << '\n';
    return 0;
}
