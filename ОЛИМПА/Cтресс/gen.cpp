#include <bits/stdc++.h>

using namespace std;

int main() {
    srand(time(nullptr));
    int n  = 100;
    vector<int> ans;
    cout << n << "\n";
    for (int i = 0; i < n; ++i)
        ans.push_back(rand() + 1);
    for (auto x : ans)
        cout << x << " ";
    cout << '\n';
    return 0;
}
