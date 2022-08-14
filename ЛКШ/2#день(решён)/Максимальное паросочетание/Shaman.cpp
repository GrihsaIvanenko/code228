#include <bits/stdc++.h>

using namespace std;


const int MAXN = 5000;

vector<pair<int, int>> leftg[MAXN], rightg[MAXN], ansg[MAXN];

int used[MAXN], mt_left[MAXN], mt_right[MAXN], mt_ans[MAXN], num_ans[MAXN], left_good[MAXN], right_good[MAXN];

bool kun(int v, char type) {
    if (used[v] == 1) {
        return false;
    }
    used[v] = 1;
    if (type == 0) {
        for (auto x : leftg[v]) {
            if (mt_left[x.first] == -1) {
                mt_left[x.first] = v;
                return true;
            } else if (kun(mt_left[x.first], 0)) {
                mt_left[x.first] = v;
                return true;
            }
        }
    } else if (type == 1) {
         for (auto x : rightg[v]) {
            if (mt_right[x.first] == -1) {
                mt_right[x.first] = v;
                return true;
            } else if (kun(mt_right[x.first], 1)) {
                mt_right[x.first] = v;
                return true;
            }
        }
    } else {
        for (auto x : ansg[v]) {
            if (mt_ans[x.first] == -1) {
                mt_ans[x.first] = v;
                num_ans[x.first] = x.second;
                return true;
            } else if (kun(mt_ans[x.first], 2)) {
                mt_ans[x.first] = v;
                num_ans[x.first] = x.second;
                return true;
            }
        }
    }
    return false;
}

int main() {
    int n, m, e;
    cin >> n >> m >> e;
    int wl[n], wr[m];
    pair<int, int> wll[n], wrr[m];
    for (int i = 0; i < n; ++i){
        cin >> wl[i];
        wll[i].first = -wl[i];
        wll[i].second = i;
    }
    sort(wll, wll + n);
    for (int i = 0; i < m; ++i){
        cin >> wr[i];
        wrr[i].first = -wr[i];
        wrr[i].second = i;
    }
    sort(wrr, wrr + m);
    for (int i = 0; i < e; ++i){
        int from, to;
        cin >> from >> to;
        --from;
        --to;
        leftg[from].push_back({to, i + 1});
        rightg[to].push_back({from, i + 1});
    }
    for (int i = 0; i < MAXN; ++i){
        mt_ans[i] = num_ans[i] = mt_left[i] = mt_right[i] = -1;
        right_good[i] = left_good[i] = 0;
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < MAXN; ++j){
            used[j] = 0;
        }
        kun(wll[i].second, 0);
    }
    int w_ans = 0;
    for (int i = 0; i < m; ++i){
        if (mt_left[i] != -1){
            left_good[mt_left[i]] = 1;
            w_ans += wl[mt_left[i]];
        }
    }
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < MAXN; ++j){
            used[j] = 0;
        }
       kun(wrr[i].second, 1);
    }
    for (int i = 0; i < n; ++i){
        if (mt_right[i] != -1){
            right_good[mt_right[i]] = 1;
            w_ans += wr[mt_right[i]];
        }
    }
    cout << w_ans << endl;
    for (int i = 0; i < n; ++i){
        if (left_good[i]){
            for (auto x : leftg[i]){
                if (right_good[x.first]){
                    ansg[i].push_back(x);
                }
            }
        }
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < MAXN; ++j){
            used[j] = 0;
        }
        if (left_good[i]){
            kun(i, 2);
        }
    }
    vector<int> ans_reb;
    for (int i = 0; i < m; ++i){
        if (mt_ans[i] != -1){
            ans_reb.push_back(num_ans[i]);
            w_ans -= wr[i];
            w_ans -= wl[mt_ans[i]];
        }
    }
    if (w_ans != 0){
        while (true){
            w_ans++;
        }
    }
    sort(ans_reb.begin(), ans_reb.end());
    cout << ans_reb.size() << endl;
    for (auto x : ans_reb){
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
