#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bool go = true;
    while (go) {
        vector<long long> numbs(n);
        bool good = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < numbers[i].size(); ++j) {
                numbs[i] *= 10ll;
                if (j == 1 && numbs[i] == 0) {
                    good = 0;
                }
                numbs[i] += v[numbers[i][j] - 'a'] - 1;
            }
            if (i != 0 && numbs[i] <= numbs[i - 1]) {
               good = 0;
            }
        }
        if (good) {
            cout << "Yes\n";
            for (auto x : v) {
                cout << x - 1 << " ";
            }
            cout << '\n';
            return 0;
        }
        go = next_permutation(v.begin(), v.end());
    }
    cout << "No\n";
    return 0;
}
