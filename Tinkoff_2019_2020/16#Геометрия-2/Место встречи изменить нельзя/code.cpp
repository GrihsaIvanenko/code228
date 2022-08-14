#include <bits/stdc++.h>

using namespace std;

long long ansx1 = 0, ansy1 = 0, ansx2 = 0, ansy2 = 0;

long long dir(long long a, long long b, long long c, long long d) {
    return (a - c) * (a - c) + (d - b) * (d - b);
}

vector<pair<long long, long long>> solve(vector<pair<long long, long long>> v) {
    if (v.size() == 1)
        return v;
    int posb = v.size() / 2;
    vector<pair<long long, long long>> v1, v2;
    v1.reserve(posb);
    v2.reserve(v.size() - posb);
    for (int i = 0; i < v.size(); ++i) {
        if (i < posb)
            v1.push_back(v[i]);
        else
            v2.push_back(v[i]);
    }
    v1 = solve(v1);
    v2 = solve(v2);
    int pos1 = 0;
    for (int i = 0; i < v1.size(); ++i) {
        int fin = min((int)v2.size(), pos1 + 100);
        int st = max(0, pos1 - 100);
        for (int j = st; j < fin; ++j)
            if (dir(v1[i].first, v1[i].second, v2[j].first, v2[j].second) < dir(ansx1, ansy1, ansx2, ansy2)) {
                ansx1 = v1[i].first;
                ansx2 = v2[j].first;
                ansy1 = v1[i].second;
                ansy2 = v2[j].second;
            }
    }
    int pos = 0, uk = 0;
    for (int i = 0; i < v1.size(); ++i) {
        while (uk != v2.size() && v2[uk].second < v1[i].second)
            v[pos++] = v2[uk++];
        v[pos++] = v1[i];
    }
    while (uk != v2.size())
        v[pos++] = v2[uk++];
    return v;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<long long, long long>> d(n);
    for (int i = 0; i < n; ++i)
        cin >> d[i].first >> d[i].second;
    sort(d.begin(), d.end());
    ansx1 = d[0].first, ansy1 = d[0].second, ansx2 = d[1].first, ansy2 = d[1].second;
    solve(d);
    cout << ansx1 << ' ' << ansy1 << '\n' << ansx2 << ' ' << ansy2 << '\n';
    return 0;
}
