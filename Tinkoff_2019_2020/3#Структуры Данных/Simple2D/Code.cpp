#include <bits/stdc++.h>

using namespace std;

#define F(); cin.tie(nullptr);cout.tie(nullptr);ios_base::sync_with_stdio(false);
#define endl '\n'
#define pb push_back
#define x first
#define y second

vector<int> fenv;

void add(int pos) {
    for (; pos < fenv.size(); pos += (pos & -pos))
        ++fenv[pos];
}

int gt(int pos) {
    int ans = 0;
    for (; pos > 0; pos -= (pos & -pos))
        ans += fenv[pos];
    return ans;
}

int sm(int l, int r) {
    return gt(r) - gt(l - 1);
}

int main () {
    //F();
    int n;
    cin >> n;
    vector<pair<int, int>> points(n);
    vector<int> coordinats;
    coordinats.reserve(n + n + n + n + n + n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        points[i] = {a, b};
        coordinats.pb(a);
        coordinats.pb(b);
    }
    int q;
    cin >> q;
    vector<pair<pair<int, int>, pair<int, int>>> asks(q);
    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (a > c)
            swap(a, c);
        if (b > d)
            swap(b, d);
        coordinats.pb(a);
        coordinats.pb(b);
        coordinats.pb(c);
        coordinats.pb(d);
        asks[i] = {{a, b}, {c, d}};
    }
    sort(coordinats.begin(), coordinats.end());
    coordinats.resize(unique(coordinats.begin(), coordinats.end()) - coordinats.begin());
    int timer = 1;
    map<int, int> compress;
    for (auto x : coordinats)
        compress[x] = timer++;
    coordinats.clear();
    coordinats.shrink_to_fit();
    for (int i = 0; i < n; ++i) {
        points[i] = {compress[points[i].first], compress[points[i].second]};
    }
    sort(points.begin(), points.end());
    for (int i = 0; i < q; ++i) {
        asks[i] = {{compress[asks[i].x.x], compress[asks[i].x.y]}, {compress[asks[i].y.x], compress[asks[i].y.y]}};
    }
    compress.clear();
    vector<pair<pair<int, int>, pair<int, int>>> tasks(q + q);
    for (int i = 0; i < q; ++i) {
        tasks[i + i] = {{asks[i].x.x - 1, i}, {asks[i].x.y, asks[i].y.y}};
        tasks[i + i + 1] = {{asks[i].y.x, i}, {asks[i].x.y, asks[i].y.y}};
    }
    asks.clear();
    asks.shrink_to_fit();
    vector<vector<int>> ans(q);
    sort(tasks.begin(), tasks.end());
    int id = 0;
    fenv.resize(timer);
    for (int i = 0; i < q + q; ++i) {
        while(id < n && points[id].x <= tasks[i].x.x) {
            add(points[id++].y);
        }
        ans[tasks[i].x.y].pb(sm(tasks[i].y.x, tasks[i].y.y));
    }
    for (int i = 0; i < q; ++i)
        cout << ans[i][1] - ans[i][0] << endl;
    return 0;
}
