#include <bits/stdc++.h>

using namespace std;

const int MAXN = 15000001;

int lp[MAXN];

vector<int> simple;
vector<int> counter(MAXN);
map<int, vector<int>> cash;

void gen(int numb, int was, int id, vector<pair<int, int>>&del, vector<int>&counter){
    if (id == del.size()) {
        ++counter[was];
        cash[numb].push_back(was);
        return;
    }
    int tmp = 1;
    for (int i = 0; i <= del[id].first; ++i) {
        gen(numb, was * tmp, id + 1, del, counter);
        tmp *= del[id].second;
    }
}

void write_dels(int numb, vector<int> &dels, vector<int>&counter) {
    vector<pair<int, int>> imba;
    for (int i = 0; i < dels.size(); ++i)
        if (imba.size() != 0 && imba.back().second == dels[i])
            ++imba.back().first;
        else
            imba.push_back({1, dels[i]});
    gen(numb, 1, 0, imba, counter);
}

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < MAXN; ++i)
        lp[i] = 0;
    for (int i = 2; i < MAXN; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            simple.push_back(i);
        }
        for (int j = 0; j < simple.size() && simple[j] <= lp[i] && simple[j] * i < MAXN; ++j)
            lp[simple[j] * i] = simple[j];
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        if (cash.find(t) != cash.end()) {
            for (auto x : cash[t]) {
                ++counter[x];
            }
            continue;
        }
        int tt = t;
        vector<int> dels;
        while (t > 1) {
            dels.push_back(lp[t]);
            t /= lp[t];
        }
        write_dels(tt, dels, counter);
    }
    int ans = -1;
    for (int i = 0; i < MAXN; ++i) {
        if (counter[i] != 0 && counter[i] != n)
            ans = max(ans, counter[i]);
    }
    if (ans == -1)
        cout << -1 << endl;
    else
        cout << n - ans << endl;
    return 0;
}
