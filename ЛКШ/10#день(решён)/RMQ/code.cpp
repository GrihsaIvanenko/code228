#include <bits/stdc++.h>

using namespace std;

const int MAXN = 25000;

vector<unsigned int> asks[MAXN];

unsigned int it[MAXN], p[MAXN];//, R[MAXN];

unsigned int get(unsigned int x) {
    if (x == p[x])
        return x;
    unsigned int tmp = get(p[x]);
    it[tmp] = min(it[tmp], it[x]);
    return p[x] = tmp;
}

void unite(unsigned int a, unsigned int b) {
    a = get(a);
    b = get(b);
    if (a == b)
        return;
    //if (R[a] > R[b])
      //  swap(a, b);
    p[a] = b;
    //R[b] = max(R[b], R[a] + 1);
    it[b] = min(it[a], it[b]);
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    unsigned int a, b, n, m;
    bool first = 1;
    while (true) {
        cin >> n >> m >> a >> b;
        if (n != 0 || m != 0 || a != 0 || b != 0) {
            for (unsigned int i = 1; i <= n; ++i) {
                it[i - 1] = a * i + b;
                p[i - 1] = i - 1;
                //R[i - 1] = 0;
                if (!first)asks[i - 1].clear();
            }
            unsigned int F = m + m + n;
            for (unsigned int i = n + 1; i <= F; ++(++i)) {
                unsigned int l = (a * i + b) % n, r = (a * i + a + b) % n;
                asks[max(l, r)].push_back(min(l, r));
            }
            vector<unsigned int> maxx;
            maxx.reserve(MAXN);
            long long ans = 0;
            for (unsigned int rr = 0; rr < n; ++rr) {
                while (!maxx.empty() && it[maxx.back()] >= it[rr]) {
                    unite(maxx.back(), rr);
                    maxx.pop_back();
                }
                maxx.push_back(rr);
                for (auto x : asks[rr]) {
                    ans += (long long)it[get(x)];
                }
            }
            cout << ans << '\n';
            first = false;
        }
        else
           return 0;
    }
    return 0;
}
