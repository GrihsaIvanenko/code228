#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> mexs(5001, -1);
    mexs[1] = 0;
    for (int i = 2; i <= 5000; ++i) {
        set<int> s;
        for (int j = 1; j < i; ++j)
            if (j + j >= i) {
                s.insert(mexs[j]);
            }
        int prev = -1;
        for (auto x : s) {
            if (x - prev != 1) {
                mexs[i] = prev + 1;
                break;
            }
            prev = x;
        }
        if (mexs[i] == -1)
            mexs[i] = (*s.rbegin()) + 1;
    }
    int a, b, c;
    cin >> a >> b >> c;
    if (mexs[a] ^ mexs[b] ^ mexs[c]) {
        cout << "YES\n";
        bool finder = 1;
        for (int i = 1; i < a && finder; ++i)
            if (i + i >= a) {
                if ((mexs[i] ^ mexs[b] ^ mexs[c]) == 0) {
                    cout << i << " " << b << " " << c << endl;
                    finder = 0;
                }
            }
        for (int i = 1; i < b && finder; ++i)
            if (i + i >= b) {
                if ((mexs[a] ^ mexs[i] ^ mexs[c]) == 0) {
                    cout << a << " " << i << " " << c << endl;
                    finder = 0;
                }
            }
        for (int i = 1; i < c && finder; ++i)
            if (i + i >= c) {
                if ((mexs[a] ^ mexs[b] ^ mexs[i]) == 0) {
                    cout << a << " " << b << " " << i << endl;
                    finder = 0;
                }
            }
    } else
        cout << "NO\n";
    return 0;
}
