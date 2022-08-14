#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    getline(cin, s);
    string ans = "";
    int id = 0;
    bool bakk = 0;
    for (auto x : s) {
        if ('a' <= x && x <= 'z') {
            bakk = 1;
            if (id == 0) {
               ans.push_back(x);
            }
            id = max(id - 1, 0);
        } else if (x == ' ') {
            bakk = 0;
        } else {
            if (bakk) {
               ans.pop_back();
            } else {
                ++id;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
