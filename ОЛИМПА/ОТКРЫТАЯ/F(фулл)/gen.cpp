#include <bits/stdc++.h>

using namespace std;

int main() {
    srand(time(nullptr));
    int n = rand() % 10 + 1;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i)
        v[i] = {rand(), rand()};
    int m = 0;
    vector<pair<pair<int, int>, int>> kek;
    int n1 = n;
    while (n1 > 0) {
        int W = rand() % 5 + 1;
        n1 -= W;
        kek.push_back({{rand(), rand()}, W});
    }
    cout << n << " " << kek.size() << '\n';
    for (auto x : v)
        cout << x.first << " " << x.second << '\n';
    for (auto x : kek)
        cout << x.first.first << " " << x.first.second << " " << x.second << '\n';
    return 0;
}
