#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define F(); cin.tie(nullptr);cout.tie(nullptr);ios_base::sync_with_stdio(false);

void easy(int n, int imba) {
    cout << imba << " " << n / 2 << endl;
    for (int i = 0; i < imba; ++i) {
        cout << n / 2 << ' ';
        for (int j = 0; j < n; ++j)
            if ((1 << i) & j)
                cout << j << ' ';
        cout << endl;
    }
    exit(0);
}
int main () {
    F();
    int n;
    cin >> n;
    int imba = 0;
    while ((1 << imba) < n)
        ++imba;
    if (n == (1 << imba))
        easy(n, imba);
    vector<pair<int, int>> good((1 << imba));
    for (int i = 0; i < (1 << imba); ++i) {
        int k = i, tmp = 0;
        while (k > 0) {
            tmp += k % 2;
            k /= 2;
        }
        good[i] = {tmp, i};
    }
    sort(good.begin(), good.end());
    vector<vector<int>> cl(imba);
    for (int i = 0; i < imba; ++i)
        cl[i].reserve(n);
    int term = 0;
    for (int i = 0; i < n; ++i) {
        int it = good[i].second;
        int k = good[i].first;
        for (int j = 0; j < 31; ++j)
            if ((1 << j) & it)
                cl[j].push_back(i);
    }
    int mx = 0;
    for (auto x : cl)
        mx = max(mx, (int)x.size());
    cout << imba << " " << mx << endl;
    for (auto x : cl) {
        cout << x.size() << " ";
        for (auto y : x)
            cout << y << " ";
        cout << endl;
    }
    return 0;
}
