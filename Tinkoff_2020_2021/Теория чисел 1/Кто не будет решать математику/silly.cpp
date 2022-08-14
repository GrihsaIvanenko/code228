#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    set<pair<int, string>> ff;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i + j == 0)
                continue;
            bool good = true;
            int ans = 0;
            string qwer;
            for (int k = 0; k < n; ++k) {
                int pnow = k % (i + j);
                if (pnow < i) {
                    if (s[k] == '1')
                        good = false;
                    qwer.push_back('0');
                } else {
                    if (s[k] == '0')
                        good = false;
                    ++ans;
                    qwer.push_back('1');
                }
            }
            if (good)
                ff.insert({ans, qwer});
        }
    }
    if (ff.size())
        cout << (*ff.rbegin()).second;
    else
        cout << "-1";
    return 0;
}
