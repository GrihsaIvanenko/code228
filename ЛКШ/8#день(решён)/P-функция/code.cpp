#include <bits/stdc++.h>

using namespace std;

vector<int> prefix_function(string &s) {
    int n = s.size();
    vector<int> ans(n);
    for (int i = 1; i < n; ++i) {
        int cur = ans[i - 1];
        while (cur != -1 && s[cur] != s[i]) {
            if (cur == 0) {
                cur = -1;
            }
            else{
                cur = ans[cur - 1];
            }
        }
        ans[i] = cur + 1;
    }
    return ans;
}

int main() {
    string s;
    cin >> s;
    vector<int> ans = prefix_function(s);
    for (auto x : ans) {
        cout << x << " ";
    }
    cout << endl;
}
