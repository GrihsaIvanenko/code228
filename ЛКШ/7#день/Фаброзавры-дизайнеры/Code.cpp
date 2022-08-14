#include <bits/stdc++.h>

using namespace std;

int size_of_block = 100;

void solve() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> v(n), sorted(n), push((n + size_of_block - 1) / size_of_block);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        sorted[i] = v[i];
    }
    for (int i = 0; i < n; i += size_of_block) {
        sort(sorted.begin() + i, sorted.begin() + min(n, i + size_of_block));
    }
    for (int i = 0; i < q; ++i) {
        char type;
        int l, r, t;
        cin >> type >> l >> r >> t;
        --l;
        if (type == '+') {
            if (l / size_of_block == r / size_of_block) {
                for (int i = l; i < r; ++i) {
                    v[i] += t;
                }
                for (int i = l - l % size_of_block; i < min(l + size_of_block - l % size_of_block, n); ++i) {
                    sorted[i] = v[i];
                }
                sort(sorted.begin() + l - l % size_of_block, sorted.begin() + min(l + size_of_block - l % size_of_block, n));
            } else{
                int finish = l - l % size_of_block + size_of_block;
                for (int i = l; i < finish; ++i) {
                    v[i] += t;
                }
                for (int i = finish - size_of_block; i < finish; ++i) {
                    sorted[i] = v[i];
                }
                sort(sorted.begin() + finish - size_of_block, sorted.begin() + finish);
                int start = r - r % size_of_block;
                for (int i = start; i < r; ++i) {
                    v[i] += t;
                }
                for (int i = start; i < min(n, start + size_of_block); ++i) {
                    sorted[i] = v[i];
                }
                sort(sorted.begin() + start, sorted.begin() + min(n, start + size_of_block));
                start /= size_of_block;
                finish /= size_of_block;
                swap(start, finish);
                for (int i = start; i < finish; ++i) {
                    push[i] += t;
                }
            }
        } else {
            bool found = false;
            if (l / size_of_block == r / size_of_block) {
                for (int i = l; i < r; ++i) {
                    if (v[i] + push[i / size_of_block] == t) {
                        found = true;
                    }
                }
            } else {
                int finish = l + size_of_block - l % size_of_block;
                for (int i = l; i < finish; ++i) {
                    if (v[i] + push[i / size_of_block] == t) {
                        found = true;
                    }
                }
                int start = r - r % size_of_block;
                for (int i = start; i < r; ++i) {
                    if (v[i] + push[i / size_of_block] == t){
                        found = true;
                    }
                }
                start /= size_of_block;
                finish /= size_of_block;
                swap(start, finish);
                for (int i = start; i < finish; ++i) {
                    auto st_it = sorted.begin() + size_of_block * i;
                    auto fin_it = sorted.begin() + min(size_of_block * i + size_of_block, n);
                    auto res = lower_bound(st_it, fin_it, t - push[i]);
                    int pos = res - sorted.begin();
                    if (sorted[pos] + push[i] == t) {
                        found = true;
                    }
                }
            }
            if (found){
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
        /*for(auto x : sorted){
                    cout << x << " ";
                }
                cout << "sorted\n";
                for(auto x : v){
                    cout << x << " ";
                }
                cout << "v\n";
                for(auto x : push){
                    cout << x << " ";
                }
                cout << "push\n\n";*/
    }
}

int main() {
    solve();
    return 0;
}
