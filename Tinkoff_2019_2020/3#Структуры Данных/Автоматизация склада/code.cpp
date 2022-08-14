#include <bits/stdc++.h>

using namespace std;

const int size_of_block = 3000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> cards(n);
    int v[m];
    for (int i = 0; i < m; ++i) {
        cin >> v[i];
        --v[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> cards[n - i - 1];
        --cards[n - i - 1];
    }
    vector<int> used(n), inp;
    inp.reserve(m + n);
    for (int i = 0; i < m; ++i) {
        if (!used[v[i]]) {
            while(cards.size() > 0 && cards.back() != v[i]) {
                if (!used[cards.back()]) {
                    inp.push_back(cards.back());
                    used[cards.back()] = 1;
                }
                cards.pop_back();
            }
        }
        inp.push_back(v[i]);
        used[v[i]] = 1;
    }
    /*used.clear();
    used.shrink_to_fit();
    cards.shrink_to_fit();
    v.clear();
    v.shrink_to_fit();*/
    vector<vector<int>> inputs(n);
    for (int i = 0;i < inp.size(); ++i) {
        inputs[inp[i]].push_back(i);
    }
    vector<int> ans(inp.size());
    vector<pair<int, pair<int, int>>> tasks;
    tasks.reserve(inp.size());
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < inputs[i].size(); ++j) {
            tasks.push_back({inputs[i][j - 1] / size_of_block, {inputs[i][j], inputs[i][j - 1]}});
        }
        if (inputs[i].size() > 0)
            ans[inputs[i].back()] = n;
    }
    int numbs[n];
    for (int i = 0; i < n; ++i)
        numbs[i] = 0;
    int cur_ans = 0, now_l = 0, now_r = 0;
    sort(tasks.begin(), tasks.end());
    /*for (auto x : inp)
        cout << x << " ";
    cout << endl;*/
    for (int i = 0; i < tasks.size(); ++i) {
        int l = tasks[i].second.second, r = tasks[i].second.first;
        //cout << l << " " << r << endl;
        /*cout << now_l << " " << now_r << ": ";
        for (auto x : numbs) {
            cout << x << " ";
        }cout << endl;*/
        while (now_r < r) {
            ++numbs[inp[now_r]];
            if (numbs[inp[now_r]] == 1)
                ++cur_ans;
            ++now_r;
        }
        /*cout << now_l << " " << now_r << ": ";
        for (auto x : numbs) {
            cout << x << " ";
        }cout << endl;*/
        while (now_l > l) {
            ++numbs[inp[now_l - 1]];
            if (numbs[inp[now_l - 1]] == 1)
                ++cur_ans;
            --now_l;
        }
        /*cout << now_l << " " << now_r << ": ";
        for (auto x : numbs) {
            cout << x << " ";
        }cout << endl;*/
        while (now_r > r) {
            --numbs[inp[now_r - 1]];
            if (numbs[inp[now_r - 1]] == 0)
                --cur_ans;
            --now_r;
        }
        /*cout << now_l << " " << now_r << ": ";
        for (auto x : numbs) {
            cout << x << " ";
        }cout << endl;*/
        while (now_l < l) {
            --numbs[inp[now_l]];
            if (numbs[inp[now_l]] == 0)
                --cur_ans;
            ++now_l;
        }
        /*cout << now_l << " " << now_r << ": ";
        for (auto x : numbs) {
            cout << x << " ";
        }cout << endl << endl;*/
        ans[tasks[i].second.second] = cur_ans;
    }
    cout << ans.size() << '\n';
    for (auto x : ans)
        cout << x << ' ';
    cout << '\n';
}

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(0);
    solve();
    return 0;
}
