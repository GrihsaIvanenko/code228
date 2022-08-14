#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1001 * 4096;

int to[MAXN], used[MAXN];

vector<pair<string, pair<int, int>>> inp;

#define imp inp

int gt(int l, int m) {
    return (l << 12) + m;
}

void dfs(int res) {
    used[res] = 1;
    if (inp[res >> 12].first == "end") {
        used[res] = 2;
        return;
    }
    int new_id = -1;
    if (inp[res >> 12].first == "begin")
        new_id = res + (1 << 12);
    else if (inp[res >> 12].first == "and") {
        int A = (res >> imp[res >> 12].second.first) & 1;
        int B = (res >> imp[res >> 12].second.second) & 1;
        new_id = res - (res & (A << (imp[res >> 12].second.first))) + ((A & B) << (imp[res >> 12].second.first)) + (1 << 12);
    } else if (inp[res >> 12].first == "or") {
        int A = (res >> imp[res >> 12].second.first) & 1;
        int B = (res >> imp[res >> 12].second.second) & 1;
        new_id = res - (res & (A << (imp[res >> 12].second.first))) + ((A | B) << (imp[res >> 12].second.first)) + (1 << 12);
    } else if (inp[res >> 12].first == "xor") {
        int A = (res >> imp[res >> 12].second.first) & 1;
        int B = (res >> imp[res >> 12].second.second) & 1;
        new_id = res - (res & (A << (imp[res >> 12].second.first))) + ((A ^ B) << (imp[res >> 12].second.first)) + (1 << 12);
    } else if (inp[res >> 12].first == "move") {
        int A = (res >> imp[res >> 12].second.first) & 1;
        int B = (res >> imp[res >> 12].second.second) & 1;
        new_id = res - (res & (A << (imp[res >> 12].second.first))) + (B << (imp[res >> 12].second.first)) + (1 << 12);
    } else if (inp[res >> 12].first == "set") {
        int B = (res >> imp[res >> 12].second.first) & 1;
        int A = imp[res >> 12].second.second;
        new_id = res - (res & (B << (imp[res >> 12].second.first))) + (A << (imp[res >> 12].second.first)) + (1 << 12);
    } else if (inp[res >> 12].first == "not") {
       new_id = (res ^ (1 << (inp[res >> 12].second.first))) + (1 << 12);
    } else if (inp[res >> 12].first == "jump") {
        if (res & (1 << inp[res >> 12].second.first)) {
            new_id = (inp[res >> 12].second.second << 12) + (res & ((1 << 12) - 1));
        } else {
            new_id = res + (1 << 12);
        }
    } else {
        assert(false);
    }
    if (used[new_id] == 0) {
        dfs(new_id);
        used[res] = used[new_id];
    } else {
        used[res] = 2 + (used[new_id] & 1);
    }
}

void solve() {
    int n, k;
    cin >> n >> k;
    inp.reserve(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        if (s == "begin" || s == "end")
            inp.push_back({s, {-1, -1}});
        else if (s == "not") {
            int x;
            cin >> x;
            inp.push_back({s, {x, -1}});
        } else {
            int x, y;
            cin >> x >> y;
            inp.push_back({s, {x, y}});
        }
    }
    for (int i = 0; i < (1 << k); ++i) {
        dfs(i);
        if (used[i] == 3) {
            cout << "No\n";
            for (int j = 0; j < k; ++j)
                cout << ((i >> j) & 1);
            cout << '\n';
            return;
        }
    }
    cout << "Yes\n";
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
