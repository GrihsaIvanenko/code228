#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101;

vector<int> suf_arr(vector<int> &s) {
    vector<int> tmp[MAXN], sor, cls(s.size());
    for (int i = 0; i < s.size(); ++i) {
        tmp[s[i]].push_back(i);
    }
    int cls_now = 0;
    for (int i = 0; i < MAXN; ++i) {
        if (tmp[i].size() != 0) {
            for (auto x : tmp[i]) {
                sor.push_back(x);
                cls[x] = cls_now;
            }
            tmp[i].clear();
            ++cls_now;
        }
    }
    int len = 0;
    while ((1 << len) < s.size()) {
        vector<int> cls_pos(cls_now), new_pos(s.size()), new_cls(s.size());
        for (int i = 1; i < s.size(); ++i) {
            if (cls[sor[i]] != cls[sor[i - 1]]) {
                cls_pos[cls[sor[i]]] = i;
            }
        }
        for (int i = 0; i < s.size(); ++i) {
            int mate = ((sor[i] - (1 << len) + s.size() + s.size()) % s.size());
            new_pos[mate] = cls_pos[cls[mate]]++;
        }
        for (int i = 0; i < s.size(); ++i) {
            sor[new_pos[i]] = i;
        }
        for (int i = 1; i < s.size(); ++i) {
            int matei = (sor[i] + (1 << len)) % s.size();
            int matei1 = (sor[i - 1] + (1 << len)) % s.size();
            if (cls[sor[i]] != cls[sor[i - 1]] || cls[matei] != cls[matei1]) {
                new_cls[sor[i]] = new_cls[sor[i - 1]] + 1;
                cls_now = new_cls[sor[i]] + 1;
            } else{
                new_cls[sor[i]] = new_cls[sor[i - 1]];
            }
        }
        cls = new_cls;
        ++len;
    }
    return sor;
}

long long solve(vector<int> v) {
    int n = v.size();
    /*vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }*/
    /*if (cyclic){
        long long ans = v.size();

    }*/
    vector<int> res = suf_arr(v);
    /*for (int i = 0; i < n; ++i) {
        cout << res[i] << ": ";
        for (int j = res[i]; j < res[i] + n; ++j) {
            cout << v[j % n] << " ";
        }
        cout << endl;
    }*/
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        pos[res[i]] = i;
    }
    vector<int> lcp(n - 1);
    int k = 0;
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        if (pos[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = res[pos[i] + 1];
        if (j < i){
            //was = true;
            k = 0;
        }
        while (v[(j + k) % n] == v[(i + k) % n] && k < n){
            ++k;
        }
        lcp[pos[i]] = k;
        ans += (long long)k;
        k = max(k - 1, 0);
    }
    for (int i = 0; i < n - 1; ++i) {
        //ans += (long long)lcp[i];
    }
    return ans;
}

bool cmp(vector<int> &a, vector<int> &b){
    int k = 0, n = a.size();
    while(k < n && a[k] == b[k]){
        ++k;
    }
    if(k == n){
        --k;
    }
    return a[k] < b[k];
}

long long silly(vector<int> v){
    int n = v.size();
    vector<vector<int>> sdvigs(n, vector<int>(n));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            sdvigs[i][j] = v[(i + j) % n];
        }
    }
    sort(sdvigs.begin(), sdvigs.end(), cmp);
    long long ans = 0;
    for(int i = 0; i < n - 1; ++i){
        int k = 0;
        while(sdvigs[i][k] == sdvigs[i + 1][k] && k < n){
            ++k;
            ++ans;
        }
    }
    return ans;
}

int main() {
    /*while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }
        cout << solve() << endl;
    }*/
    int n = 11;
    vector<int> v = {12, 8, 18, 18, 8, 18, 18, 8, 15, 15, 8};
    srand(1511);
    int tmp = 0;
    while(true + true){
        n = rand() % 12 + 1;
        v.resize(n);
        for(int i = 0; i < n; ++i){
            v[i] = rand() % 3;
        }
        if(solve(v) != silly(v)){
            cout << tmp << " : " << n << endl;
            for(auto x : v){
                cout << x << " ";
            }
            cout << endl << "MY: " << solve(v) << " " << "GOOD: " << silly(v) << endl;
            return 0;
        }
        ++tmp;
        if(tmp % 100000 == 0){
            cout << tmp << ": " << n << endl;
            for(auto x : v){
                cout << x << " ";
            }
            cout << endl << endl;
        }
    }
    return 0;
}

