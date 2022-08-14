#include <bits/stdc++.h>

using namespace std;

int main () {
    string s;
    cin >> s;
    vector<char> s1;
    s1.reserve(s.size() * 4);
    for (int i = 0; i < s.size(); ++i) {
        s1.push_back('*');
        s1.push_back(s[i]);
    }
    for (int i = 0; i < s.size() - 1; ++i) {
        s1.push_back('*');
        s1.push_back(s[i]);
    }
    s1.push_back('*');
    int ans = 1;
    vector<int> pol(s1.size());
    int l = -1, r = -1;
    for (int i = 0; i < s1.size(); ++i) {
        if (i <= r) {
            pol[i] = min(pol[l + r - i], r - i);
        }
        while (pol[i] + i + 1 < s1.size() && i - pol[i] - 1 >= 0 && s1[i - pol[i] - 1] == s1[i + pol[i] + 1])
            ++pol[i];
        if (i + pol[i] > r) {
            r = i + pol[i];
            l = i - pol[i];
        }
        int cur = min(pol[i] - pol[i] % 2, (int)(s.size() - s.size() % 2));
        cur += i % 2;
        if (cur > s.size())
            cur -= 2;
        if (ans < cur && cur <= s.size()) {
            ans = cur;
        }
    }
    cout << ans << endl;
    return 0;
}
