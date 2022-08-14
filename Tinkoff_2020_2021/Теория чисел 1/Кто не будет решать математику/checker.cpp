#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;
    int ans = 0;
    for (auto x : s)
        if (x == '1')
            ++ans;
    cout << ans << '\n';
}
