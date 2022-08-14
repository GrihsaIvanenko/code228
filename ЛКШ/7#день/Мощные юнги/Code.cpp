#include <bits/stdc++.h>

using namespace std;

const int MAXH = 1000001, MAXN = 200000, szb = 500;

long long H[MAXH], un[MAXN];

long long ans = 0;

void add(long long pos, long long inc) {
    ans -= (H[pos] * H[pos] * pos);
    H[pos] += inc;
    ans += (H[pos] * H[pos] * pos);
}

long long move_(int &pos, int fin, bool r) {
    if (r) {
        if (pos < fin){
            for (; pos < fin; ++pos) {
                add(un[pos], 1);
            }
        } else{
            for (; pos > fin; --pos) {
                add(un[pos - 1], -1);
            }
        }
    } else {
        if (pos < fin) {
            for (; pos < fin; ++pos) {
                add(un[pos], -1);
           }
        } else {
            for (; pos > fin; --pos) {
                add(un[pos - 1], 1);
            }
        }
    }
    pos = fin;
    return ans;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> un[i];
    }
    vector<pair<pair<int, int>, pair<int, int>>> tasks(m);
    vector<pair<int, long long>> ans(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        tasks[i] = {{a / szb, b}, {a, i}};
    }
    sort(tasks.begin(), tasks.end());
    int nl = 0, nr = 0;
    for (int i = 0; i < m; ++i) {
        move_(nl, tasks[i].second.first, 0);
        ans[i] = {tasks[i].second.second, move_(nr, tasks[i].first.second, 1)};
    }
    sort(ans.begin(), ans.end());
    for (auto x : ans) {
        cout << x.second << '\n';
    }
    return 0;
}
