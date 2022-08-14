#include <bits/stdc++.h>

using namespace std;

bool sim(int v) {
    for (int i = 2; i * i <= v; ++i)
        if (v % i == 0)
            return false;
    return true;
}

vector<int> simple;

set<int> s, s1;

void gen(int x, int k, int kolvo = 0) {
    if (s.find(x) == s.end()) {
        if (x % 6 == 0)
            s1.insert(x);
    }
    s.insert(x);
    if (kolvo == k)
        return;
    for (auto y : simple)
        gen(x * y, k, kolvo + 1);
    for (auto y : simple)
        if (x % y == 0)
            gen(x / y, k, kolvo + 1);
}

int f(int x, int k) {
    s.clear();
    gen(x, k);
    return s.size();
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, k;
    //cin >> n >> k;
    n = 17, k = 4;
    for (int i = 2; i <= n; ++i)
        if (sim(i))
            simple.push_back(i);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int kolvo = f(i, k);
        ans += i * kolvo;
    }
    cout << ans << '\n';
    return 0;
}
