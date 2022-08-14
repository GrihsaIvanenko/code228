#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e9 + 100, TWO = 2;

vector<pair<ll, ll>> pr;

void decompose(vector<vector<pair<ll, int>>> &asks, ll k, int id, int le, int re, int v, int lb, int rb) {
    if (le >= rb || re <= lb)
        return;
    if (le <= lb && rb <= re) {
        asks[v].push_back({k, id});
        return;
    }
    int mid = (lb + rb) / 2;
    decompose(asks, k, id, le, re, v + v, lb, mid);
    decompose(asks, k, id, le, re, v + v + 1, mid, rb);
}

ll F(ll k, ll b, ll pos) {
    return k - b + pos * b;
}

ll first_point_when_second_better(pair<ll, ll> l1, pair<ll, ll> l2) {
    if (l1.second == l2.second) {
        if (l1.first < l2.first)
            return INF * INF;
        return -INF * INF;
    }
    ll lb = -INF, rb = INF;
    while (rb - lb > 1) {
        ll mid = (lb + rb) / TWO;
        if (F(l1.first, l1.second, mid) >= F(l2.first, l2.second, mid))
            rb = mid;
        else
            lb = mid;
    }
    return rb;
}

void add_line(vector<pair<ll, pair<ll, ll>>> &kht, pair<ll, ll> &line) {
    while (kht.size() > 0 && first_point_when_second_better(kht.back().second, line) <=  kht.back().first)
        kht.pop_back();
    ll pos_good = 1;
    if (kht.size() != 0)
        pos_good = first_point_when_second_better(kht.back().second, line);
    if (pos_good != INF *INF)
        kht.push_back({pos_good, line});
}

int main() {
    freopen("sample.cpp", "r", stdin);
    for (int i = 0; i < 6; ++i) {
        long double a, b;
        cin >> a;
        b = a * 37.5;
        cout.precision(10);
        cout << fixed << a * sqrt((0.04 / b) * (0.04 / b) + (0.04 / 37.5) * (0.04 / 37.5)) << endl;
    }
    return 0;
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    int sz = 1;
    while (sz < n + n)
        sz += sz;
    pr.resize(sz / 2);
    for (int i = 0; i < n; ++i) {
        cin >> pr[i].first >> pr[i].second;
    }
    for (int i = n; i < sz / 2; ++i)
        pr[i] = {INF, INF};
    int m;
    cin >> m;
    vector<pair<pair<ll, int>, pair<ll, ll>>> asks(m);
    for (int i = 0; i < m; ++i) {
        ll a, b, k;
        cin >> a >> b >> k;
        asks[i] = {{k, i}, {a - 1, b}};
    }
    sort(asks.begin(), asks.end());
    vector<vector<pair<ll, pair<ll, ll>>>> lines(sz);
    for (int i = 0; i < sz / 2; ++i) {
        lines[sz / 2 + i].push_back({1, pr[i]});
    }
    vector<vector<pair<ll, int>>> tasks(sz);
    for (int i = 0; i < m; ++i)
        decompose(tasks, asks[i].first.first, asks[i].first.second, asks[i].second.first, asks[i].second.second, 1, 0, sz / 2);
    vector<ll> answers(m, INF * INF);
    for (int i = sz - 1; i >= sz / 2; --i) {
        for (auto x : tasks[i])
            answers[x.second] = min(F(pr[i - sz / 2].first, pr[i - sz / 2].second, x.first), answers[x.second]);
    }
    for (int i = sz / 2 - 1; i > 0; --i) {
        int uk = 0;
        for (int j = 0; j < lines[i + i].size(); ++j) {
            while (uk < lines[i + i + 1].size() && lines[i + i + 1][uk].second.second > lines[i + i][j].second.second) {
                add_line(lines[i], lines[i + i + 1][uk++].second);
            }
            add_line(lines[i], lines[i + i][j].second);
        }
        while (uk < lines[i + i + 1].size())
            add_line(lines[i], lines[i + i + 1][uk++].second);
        uk = 0;
        for (auto x : tasks[i]) {
            while (uk + 1 < lines[i].size() && lines[i][uk + 1].first <= x.first)
                ++uk;
            answers[x.second] = min(answers[x.second], F(lines[i][uk].second.first, lines[i][uk].second.second, x.first));
        }
   }
    for (auto x : answers)
        cout << x << '\n';
    return 0;
}
