#include <bits/stdc++.h>

using namespace std;

vector<int> p(string &s) {
    vector<int> z(s.size());
    int l = 0, r = 0;
    for (int i = 1; i < s.size(); ++i) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i);
        }
        while (i + z[i] < s.size() && s[i + z[i]] == s[z[i]])
            ++z[i];
        if (i + z[i] > r) {
            r = i + z[i];
            l = i;
        }
    }
    return z;
}

int main () {
    string a, b;
    cin >> a >> b;
    string c = a + '#' + b;
    vector<int> p1 = p(c);
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    c = a + '#' + b;
    vector<int> p2 = p(c);
    reverse(p1.begin(), p1.end());
    reverse(p2.begin(), p2.end());
    for (int i = 0; i <= a.size(); ++i) {
        p1.pop_back();
        p2.pop_back();
    }
    reverse(p1.begin(), p1.end());
    vector<int> ans;
    for (int i = 0; i <= (int)(b.size() - a.size()); ++i) {
        if (p1[i] + p2[i + a.size() - 1] >= a.size() - 1)
            ans.push_back(i + 1);
    }
    cout << ans.size() << endl;
    for (auto x : ans)
        cout << x << " ";
    cout << endl;
    return 0;
}
