#include <bits/stdc++.h>

using namespace std;

bool comp(string &s1, string &s2, int l1, int r1, int l2, int r2) {
    vector<int> v1(26), v2(26);
    for (int i = l1; i < r1; ++i) {
        ++v1[s1[i] - 'a'];
    }
    for (int i = l2; i < r2; ++i) {
        ++v2[s2[i] - 'a'];
    }
    for (int i = 0; i < 26; ++i) {
        if (v1[i] != v2[i]) {
           return 0;
        }
    }
    return 1;
}

vector<int> work(string &s1, string &s2, int l1, int r1, int l2, int r2) {
    if (l1 + 1 == r1) {
       if (s1[l1] != s2[l2]) {
           return {-1};
        } else {
            return {100};
        }
    }
    vector<int> v1 = work(s1, s2, l1, (l1 + r1) >> 1, l2, (l2 + r2) >> 1), v2;
    if (v1.back() == -1) {
        v1 = work(s1, s2, l1, (l1 + r1) >> 1, (l2 + r2) >> 1, r2);
        if (v1.back() == -1) {
            return {-1};
        } else {
            v2 = work(s1, s2, (l1 + r1) >> 1, r1, l2, (l2 + r2) >> 1);
            if (v2.back() == -1) {
                return {-1};
            } else {
                for (auto x : v2) {
                    v1.push_back(x);
                }
                v1.push_back(1);
                return v1;
            }
        }
    } else {
        v2 = work(s1, s2, (l1 + r1) >> 1, r1, (l2 + r2) >> 1, r2);
        if (v2.back() == -1) {
            v1 = work(s1, s2, l1, (l1 + r1) >> 1, (l2 + r2) >> 1, r2);
            if (v1.back() == -1) {
                return {-1};
            } else {
                v2 = work(s1, s2, (l1 + r1) >> 1, r1, l2, (l2 + r2) >> 1);
                if (v2.back() == -1) {
                    return {-1};
                } else {
                    for (auto x : v2) {
                        v1.push_back(x);
                    }
                    v1.push_back(1);
                    return v1;
                }
            }
        } else {
            for (auto x : v2) {
                v1.push_back(x);
            }
            v1.push_back(0);
            return v1;
        }
    }
}

void solve(string &s1, string &s2) {
    vector<int> v = work(s1, s2, 0, s1.size(), 0, s2.size());
    if (v.back() == -1) {
       cout << "No\n";
    } else {
        cout << "Yes\n";
        for (auto x : v) {
            if (x != 100)cout << x << " ";
        }
        cout << '\n';
    }
}

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string a, b;
        cin >> a >> b;
        solve(a, b);
    }
    return 0;
}

