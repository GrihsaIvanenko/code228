#include <bits/stdc++.h>

using namespace std;

int main () {
    int n;
    cin >> n;
    vector<long long> was(n), become(n);
    for (int i = 0; i < n; ++i)
        cin >> was[i];
    for (int i = 0; i < n; ++i)
        cin >> become[i];
    vector<long long> d1(n + 1), dh(n + 1);
    int q, size_of_block = 400;
    cin >> q;
    vector<pair<pair<int, int>, pair<long long, long long>>> asks(q);
    vector<int> ans(n, -1);
    for (int i = 0; i < n; ++i)
        if (become[i] <= was[i])
            ans[i] = 0;
    for (int i = 0; i < q; ++i) {
        cin >> asks[i].first.first >> asks[i].first.second >> asks[i].second.first >> asks[i].second.second;
        --asks[i].first.first;
    }
    for (int iter = 0; iter < (q + size_of_block - 1) / size_of_block; ++iter) {
        int start = iter * size_of_block, finish = min(start + size_of_block, q);
        for (int i = start; i < finish; ++i) {
            int l = asks[i].first.first, r = asks[i].first.second;
            long long x = asks[i].second.first, y = asks[i].second.second;
            d1[l] += x;
            d1[r] -= x + (r - l - 1) * y;
            dh[l + 1] += y;
            dh[r] -= y;
        }
        long long change = 0, step = 0, sum = 0;
        for (int i = 0; i < n; ++i) {
            change += dh[i];
            step += d1[i] + change;
            sum = step;
            //cout << iter << ' ' << i << " " << change << " " << step << " " << sum << endl;
            if (ans[i] == -1 && was[i] + sum >= become[i]) {
                for (int j = start; j < finish; ++j) {
                    if (ans[i] == -1 && asks[j].first.first <= i && i < asks[j].first.second) {
                        was[i] += asks[j].second.first + (long long)(i - asks[j].first.first) * asks[j].second.second;
                        if (ans[i] == -1 && was[i] >= become[i])
                            ans[i] = j + 1;
                    }
                }
            } else if (ans[i] == -1)
                was[i] += sum;
        }
        /*for (auto x : was)
            cout << x << "F ";
        cout << endl;*/
        for (int i = 0; i < n; ++i) {
            d1[i] = 0;
            dh[i] = 0;
        }
    }
    for (auto x : ans)
        cout << x << " ";
    return 0;
}
