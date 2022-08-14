#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6;

long long pw[MAXN], p = 53, mod = 1e9 + 7;

vector<long long> ahash, bhash;

long long get_pos(char t) {
    if (t >= 'A' && t <= 'Z') {
        return t - 'A' + 27;
    }
    return t - 'a' + 1;
}

long long get_hash(int l, int r, vector<long long> &hhash){
    if (l > r){
        return mod;
    }
    return (hhash[r] - hhash[l] * pw[r - l] + mod * pw[r - l]) % mod;
}


bool good(int pos, string &a){
    if (get_hash(pos, pos + a.size(), bhash) == get_hash(0, a.size(), ahash)){
        return true;
    }
    int l = 0, r = a.size();
    while (r - l > 1){
        int mid = (l + r) >> 1;
        if (get_hash(pos, pos + mid, bhash) == get_hash(0, mid, ahash)){
            l = mid;
        }
        else{
            r = mid;
        }
    }
    return get_hash(pos + l + 1, a.size() + pos, bhash) == get_hash(l + 1, a.size(), ahash);
}

void solve() {
    string a, b;
    cin >> a >> b;
    if (a.size() > b.size()){
        cout << "0\n";
        return;
    }
    ahash.resize(MAXN + 1);
    bhash.resize(MAXN + 1);
    pw[0] = 1;
    for (int i = 1; i < MAXN; ++i){
        pw[i] = (pw[i - 1] * p) % mod;
    }
    for (int i = 0; i < b.size(); ++i){
        if (i < a.size()) {
            ahash[i + 1] = (ahash[i] * p + get_pos(a[i])) % mod;
        }
        bhash[i + 1] = (bhash[i] * p + get_pos(b[i])) % mod;
    }
    vector<int> ans;
    for (int i = 0; i < b.size() - a.size() + 1; ++i){
        if (good(i, a)){
            ans.push_back(i + 1);
        }
    }
    cout << ans.size() << '\n';
    for (auto x : ans){
        cout << x << " ";
    }
    return;
}

int main() {
    solve();
    return 0;
}
