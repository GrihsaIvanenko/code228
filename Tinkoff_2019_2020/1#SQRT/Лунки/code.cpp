#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, q, size_of_block = 320;
    cin >> n >> q;
    vector<int> power(n), to(n), jumps(n), rip(n);
    for (int i = 0; i < n; ++i)
        cin >> power[i];
    for (int i = n - 1; i >= 0; --i)
        if (i + power[i] >= n) {
            to[i] = n + 1;
            jumps[i] = 1;
            rip[i] = i + 1;
        }
        else if(i / size_of_block != (i + power[i]) / size_of_block) {
            to[i] = i + power[i];
            jumps[i] = 1;
            rip[i] = 0;
        }
        else {
            to[i] = to[i + power[i]];
            jumps[i] = 1 + jumps[i + power[i]];
            if (to[i] == n + 1)
                rip[i] = rip[i + power[i]];
            else
                rip[i] = 0;
        }
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (!t) {
            int a, b;
            cin >> a >> b;
            --a;
            power[a] = b;
            for (int j = min(a - a % size_of_block + size_of_block - 1, n - 1); j >= a - a % size_of_block; --j)
                if (j + power[j] >= n) {
                    to[j] = n + 1;
                    jumps[j] = 1;
                    rip[j] = j + 1;
                }
                else if(j / size_of_block != (j + power[j]) / size_of_block) {
                    to[j] = j + power[j];
                    jumps[j] = 1;
                    rip[j] = 0;
                }
                else {
                    to[j] = to[j + power[j]];
                    jumps[j] = 1 + jumps[j + power[j]];
                    if (to[j] == n + 1)
                        rip[j] = rip[j + power[j]];
                    else
                        rip[j] = 0;
                }
        } else {
            int b;
            cin >> b;
            --b;
            int ans_jumps = 0;
            while (b != n + 1) {
                ans_jumps += jumps[b];
                if (rip[b])
                    cout << rip[b] << ' ' << ans_jumps << '\n';
                b = to[b];
            }
        }
    }
    return 0;
}
