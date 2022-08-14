#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> L(n), R(n), v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    vector<pair<int, int>> st;
    st.push_back({-1, -1});
    for (int i = 0; i < n; ++i) {
        while (st.back().first >= v[i])
            st.pop_back();
        L[i] = st.back().second;
        st.push_back({v[i], i});
    }
    st.clear();
    st.push_back({-1, n});
    for (int i = n - 1; i >= 0; --i) {
        while (st.back().first >= v[i])
            st.pop_back();
        R[i] = st.back().second;
        st.push_back({v[i], i});
    }
    int ANSL = 1e9 + 7, ANSR = 1e9 + 7;
    for (int i = 0; i < n; ++i) {
        if (v[i] == 0)
            continue;
        int x = v[i];
        int y = R[i] - L[i] - 1;
        if (x > y)
            swap(x, y);
        ANSL = min(ANSL, x);
        ANSR = min(ANSR, y);
    }
    cout << (long long)ANSL * ANSR << '\n';
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
