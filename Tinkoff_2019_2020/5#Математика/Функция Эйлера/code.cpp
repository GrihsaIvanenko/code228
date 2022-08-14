#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e8 + 1;

int lm[MAXN], Fi[MAXN];

short k[MAXN];

vector<int> simple;

int pw(int k, int x) {
    if (x == 0)
        return 1;
    if (x % 2)
        return pw(k * k, x / 2) * k;
    return pw(k * k, x / 2);
}

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int p;
    cin >> p;
    Fi[1] = 1;
    for (int i = 0; i < MAXN; ++i)
        lm[i] = -1;
    for (int i = 2; i <= p; ++i) {
        if (lm[i] == -1) {
            lm[i] = i;
            k[i] = 1;
            simple.push_back(i);
            Fi[i] = i - 1;
        }
        for (int j = 0; j < simple.size() && simple[j] <= lm[i] && (long long)simple[j] * (long long)i <= (long long)p; ++j) {
            int id = i * simple[j];
            lm[id] = simple[j];
            if (lm[id] == lm[i])
                k[id] = k[i] + 1;
            else
                k[id] = 1;
            int tmp = pw(lm[id], k[id] - 1);
            //cout << id << ": " << k[id] << " " << (lm[id] - 1) << " " << tmp << " " << i << ' ' << Fi[i / tmp] << "res " << (lm[id] - 1) * tmp * Fi[i / tmp] << endl;
            Fi[id] = (lm[id] - 1) * tmp * Fi[i / tmp];
        }
    }
    long long ans = 0;
    for (int i = 1; i <= p; ++i) {
        ans += (long long)Fi[i];
        if (i % 100 == 0) {
            cout << ans << " ";
            ans = 0;
        }
    }
    if (p % 100 != 0)
        cout << ans;
    cout << '\n';
    return 0;
}
