#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200000, SZ = 2154;

int val[MAXN], a[MAXN], b[MAXN], tim[MAXN], ans[MAXN], bef_val[MAXN];
int ch_val[MAXN], ch_pos[MAXN], timer = 0, cnt[MAXN << 1], cntcnt[MAXN << 1];

bool cmp(int A, int B) {
    int P1 = tim[A] / SZ, P2 = tim[B] / SZ;
    if (P1 != P2)
        return P1 < P2;
    P1 = a[A] / SZ, P2 = a[B] / SZ;
    if (P1 != P2)
        return P1 < P2;
    return b[A] < b[B];
}

void gg(bool tl = true) {
    if (tl)
        while (true)
            tl = !tl;
    assert(false);
}

void add(int val) {
    if (val < 0 || cnt[val] < 0 || cnt[val] + 1 >= MAXN)
        gg();
    if (cnt[val]) {
        --cntcnt[cnt[val]];
    }
    ++cnt[val];
    ++cntcnt[cnt[val]];
}

void del(int val) {
    if (val < 0 || cnt[val] < 1 || cnt[val] + 1 >= MAXN)
        gg();
    --cntcnt[cnt[val]];
    --cnt[val];
    if (cnt[val]) {
        ++cntcnt[cnt[val]];
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> values;
    values.reserve(n + m);
    for (int i = 0; i < n; ++i) {
        cin >> val[i];
        values.push_back(val[i]);
    }
    vector<int> tasks;
    tasks.reserve(m);
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t & 1) {
            cin >> a[i] >> b[i];
            --a[i];
            tim[i] = timer;
            tasks.push_back(i);
        } else {
            cin >> ch_pos[timer] >> ch_val[timer];
            --ch_pos[timer];
            bef_val[timer] = val[ch_pos[timer]];
            val[ch_pos[timer]] = ch_val[timer];
            values.push_back(ch_val[timer]);
            ++timer;
        }
    }
    sort(values.begin(), values.end());
    values.resize(unique(values.begin(), values.end()) - values.begin());
    map<int, int> mm;
    for (unsigned i = 0; i < values.size(); ++i)
        mm[values[i]] = i;
    for (int i = 0; i < n; ++i)
        val[i] = mm[val[i]];
    for (int i = 0; i < timer; ++i) {
        bef_val[i] = mm[bef_val[i]];
        ch_val[i] = mm[ch_val[i]];
    }
    sort(tasks.begin(), tasks.end(), cmp);
    int L = 0, R = 0, T = timer;
    for (auto id : tasks) {
        int l = a[id], r = b[id], t = tim[id];
        while (T > t) {
            --T;
            if (L <= ch_pos[T] && ch_pos[T] < R) {
                del(ch_val[T]);
                add(bef_val[T]);
            }
            val[ch_pos[T]] = bef_val[T];
        }
        while (T < t) {
            if (L <= ch_pos[T] && ch_pos[T] < R) {
                del(bef_val[T]);
                add(ch_val[T]);
            }
            val[ch_pos[T]] = ch_val[T];
            ++T;
        }
        while (L > l)
            add(val[--L]);
        while (R < r)
            add(val[R++]);
        while (L < l)
            del(val[L++]);
        while (R > r)
            del(val[--R]);
        for (int i = 1; i < MAXN; ++i)
            if (!cntcnt[i]) {
                ans[id] = i;
                break;
            }
    }
    for (int i = 0; i < MAXN; ++i)
        if (ans[i])
            cout << ans[i] << '\n';
    return 0;
}
