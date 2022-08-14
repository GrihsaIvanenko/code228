#include <bits/stdc++.h>

using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int fat_sz = 500;
    int n, m;
    cin >> n >> m;
    vector<int> weight(n), versions(n);
    for (int i = 0; i < n; ++i) {
        cin >> versions[i];
        --versions[i];
    }
    vector<pair<int, int>> rebs(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        ++weight[a];
        ++weight[b];
        rebs[i] = {a, b};
    }
    vector<int> renumber(n);
    for (int i = 0; i < n; ++i)
        renumber[i] = i;
    int timer = 0;
    for (int i = 0; i < n; ++i)
        if (weight[i] >= fat_sz) {
            swap(renumber[i], renumber[timer]);
            swap(versions[renumber[i]], versions[renumber[timer++]]);
        }
    vector<int> fat_g[n], easy_g[n];
    for (auto x : rebs) {
        x.first = renumber[x.first];
        x.second = renumber[x.second];
        if (x.first < timer)
            fat_g[x.second].push_back(x.first);
        else
            easy_g[x.second].push_back(x.first);
        if (x.second < timer)
            fat_g[x.first].push_back(x.second);
        else
            easy_g[x.first].push_back(x.second);
    }
    rebs.clear();
    rebs.shrink_to_fit();
    vector<vector<int>> version(timer, vector<int>(100000));
    int good = 0;
    for (int i = 0; i < timer; ++i) {
        for (int j = 0; j < fat_g[i].size(); ++j)
            ++version[i][versions[fat_g[i][j]]];
        for (int j = 0; j < easy_g[i].size(); ++j)
            ++version[i][versions[easy_g[i][j]]];
        good += version[i][versions[i]];
    }
    for (int i = timer; i < n; ++i) {
        for (int j = 0; j < easy_g[i].size(); ++j) {
            if (versions[i] == versions[easy_g[i][j]])
                ++good;
        }
        for (int j = 0; j < fat_g[i].size(); ++j) {
            if (versions[i] == versions[fat_g[i][j]])
                ++good;
        }
    }
    good /= 2;
    int q;
    cin >> q;
    for (int ch = 0; ch < q; ++ch) {
        int v, ver;
        cin >> v >> ver;
        --v;
        --ver;
        v = renumber[v];
        if (v < timer) {
            good -= version[v][versions[v]];
            good += version[v][ver];
            for (int i = 0; i < fat_g[v].size(); ++i) {
                --version[fat_g[v][i]][versions[v]];
                ++version[fat_g[v][i]][ver];
            }
        } else {
            for (int i = 0; i < fat_g[v].size(); ++i) {
                --version[fat_g[v][i]][versions[v]];
                ++version[fat_g[v][i]][ver];
                if (versions[fat_g[v][i]] == versions[v])
                    --good;
                if (versions[fat_g[v][i]] == ver)
                    ++good;
            }
            for (int i = 0; i < easy_g[v].size(); ++i) {
                if (versions[easy_g[v][i]] == versions[v])
                    --good;
                if (versions[easy_g[v][i]] == ver)
                    ++good;
            }
        }
        versions[v] = ver;
        cout << m - good << '\n';
    }
    return 0;
}
