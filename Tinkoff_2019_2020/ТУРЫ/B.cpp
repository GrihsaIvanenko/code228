#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define endl '\n'
#define F(); cin.tie(nullptr);cout.tie(nullptr);ios_base::sync_with_stdio(false);

int main () {
    int n, m;
    cin >> n >> m;
    if (n * m > 2) {
        if (min(n, m) == 1 || n * m % 2){
            cout << -1 << endl;
            return 0;
        }
    }
    int sum = 0;
    vector<vector<int>> costs(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> costs[i][j];
            sum += costs[i][j];
        }
    }
    if (sum < 0) {
        cout << -1 << endl;
        return 0;
    }
    if (n * m == 1) {
        cout << "1 1" << endl;
        return 0;
    }
    vector<pair<int, int>> way;
        way.reserve(n * m);
    if (n % 2 == 0) {
        for (int i = 0; i < n; i += 2) {
            for (int j = 1; j < m; ++j)
                way.push_back({i, j});
            for (int j = m - 1; j > 0; --j)
                way.push_back({i + 1, j});
        }
        for (int i = n - 1; i > -1; --i)
            way.push_back({i, 0});
    } else {
        for (int i = 0; i < m; i += 2) {
            for (int j = 1; j < n; ++j)
                way.push_back({j, i});
            for (int j = n - 1; j > 0; --j)
                way.push_back({j, i + 1});
        }
        for (int i = m - 1; i > -1; --i)
            way.push_back({0, i});
    }
    vector<int> pref_sums(n * m);
    pref_sums[0] = costs[way[0].first][way[0].second];
    //cout << 0 << ": " <<  pref_sums[0] << " " << way[0].first << " " << way[0].second << endl;
    for (int i = 1; i < n * m; ++i) {
        pref_sums[i] = pref_sums[i - 1] + costs[way[i].first][way[i].second];
        //cout << i << ": " << pref_sums[i] << " " << way[i].first << " " << way[i].second << endl;
    }
    int id = 0;
    for (int i = 0; i < n * m; ++i) {
        if (pref_sums[i] < pref_sums[id])
            id = i;
    }
    //cout << id << "FFFFF" << endl;
    for (int i = id + 1; i < n * m; ++i)
        cout << way[i].first + 1 << " " << way[i].second + 1 << endl;
    for (int i = 0; i <= id; ++i)
        cout << way[i].first + 1 << " " << way[i].second + 1 << endl;
    return 0;
}
