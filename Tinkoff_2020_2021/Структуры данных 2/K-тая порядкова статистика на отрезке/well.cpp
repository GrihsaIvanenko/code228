#include <bits/stdc++.h>

using namespace std;

const int MAXN = 131072 * 4;

int sum[MAXN * 22], l[MAXN * 22], r[MAXN * 22], roots[MAXN], timer = 2;

int nw() {
    ++timer;
    return timer;
}

void fir_build(int v = 0, int lb = 0, int rb = MAXN) {
    if (lb + 1 == rb)
        return;
    int mid = (lb + rb) >> 1;
    l[v] = nw();
    fir_build(l[v], lb, mid);
    r[v] = nw();
    fir_build(r[v], mid, rb);
}

void add(int pos, int v, int ide, int lb = 0, int rb = MAXN) {
    if (lb + 1 == rb) {
        sum[v] = sum[ide] + 1;
        return;
    }
    int mid = (lb + rb) >> 1;
    if (pos < mid) {
        l[v] = nw();
        r[v] = r[ide];
        add(pos, l[v], l[ide], lb, mid);
    } else {
        l[v] = l[ide];
        r[v] = nw();
        add(pos, r[v], r[ide], mid, rb);
    }
    sum[v] = sum[l[v]] + sum[r[v]];
}

int pos(int k, int vl, int vr, int lb = 0, int rb = MAXN) {
    if (lb + 1 == rb) {
        return lb;
    }
    int mid = (lb + rb) >> 1;
    if (sum[l[vr]] - sum[l[vl]] >= k)
        return pos(k, l[vl], l[vr], lb, mid);
    return pos(k - (sum[l[vr]] - sum[l[vl]]), r[vl], r[vr], mid, rb);
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    roots[0] = nw();
    fir_build(roots[0]);
    vector<int> vals, val_mem;
    vals.reserve(n);
    map<int, int> compress;
    int  a1, l, m, mod = 1e9;
    cin >> a1 >> l >> m;
    vals.push_back(a1);
    val_mem.push_back(vals.back());
    for (int i = 1; i < n; ++i) {
        vals.push_back((long long)(vals.back() * (long long)l + (long long)m) % mod);
        val_mem.push_back(vals.back());
    }
    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());
    for (unsigned i = 0; i < vals.size(); ++i) {
        compress[vals[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
        roots[i + 1] = nw();
        add(compress[val_mem[i]], roots[i + 1], roots[i]);
    }
    int B;
    cin >> B;
    long long ans = 0;
    for (int ch = 0; ch < B; ++ch) {
        long long G, x1, lx, mx, y1, ly, my, k1, lk, mk, xg, yg, ig, jg, kg;
        cin >> G >> x1 >> lx >> mx >> y1 >> ly >> my >> k1 >> lk >> mk;
        xg = x1;
        yg = y1;
        ig = min(x1, y1);
        jg = max(x1, y1);
        kg = k1;
        ans += vals[pos(kg, roots[ig - 1], roots[jg])];
        for (int i = 1; i < G; ++i) {
            xg = ((ig - 1) * lx + mx) % n + 1;
            yg = ((jg - 1) * ly + my) % n + 1;
            ig = min(xg, yg);
            jg = max(xg, yg);
            kg = (((kg - 1) * lk + mk) % (jg - ig + 1)) + 1;
            ans += vals[pos(kg, roots[ig - 1], roots[jg])];
        }
    }
    cout << ans << endl;
    return 0;
}
