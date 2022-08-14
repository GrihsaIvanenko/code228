#include <bits/stdc++.h>

using namespace std;

const long long P1 = 999983, MOD1 = 1000000021;

const int MAXN = 200001;

//int p1[MAXN];

/*const long long P1 = 999983, P2 = 999979, P3 = 999961, MOD1 = 1000000009, MOD2 = 1000000021, MOD3 = 1000000033;

const int MAXP = 200001, MAXN = 100;

long long p1[MAXP], p2[MAXP], p3[MAXP];

long long cnt[MAXN], sup_cnt[MAXP];

int main () {
    p1[0] = p2[0] = p3[0] = 0;
    p1[1] = p2[1] = p3[1] = 1;
    for (int i = 2; i < MAXP; ++i) {
        p1[i] = (p1[i - 1] * P1) % MOD1;
        p2[i] = (p2[i - 1] * P2) % MOD2;
        p3[i] = (p3[i - 1] * P3) % MOD3;
    }
    string st1, st2;
    cin >> st1 >> st2;
    vector<long long> s1(st1.size()), s2(st2.size());
    for(int i = 0; i < st1.size(); ++i)
        s1[i] = (int)st1[i] - 32;
    for (int i = 0; i < st2.size(); ++i)
        s2[i] = (int)st2[i] - 32;
    for (int i = 0; i < MAXN; ++i) {
        cnt[i] = 0;
    }
    for (int i = 0; i < s2.size(); ++i)
        ++cnt[s2[i]];
    for (int i = 0; i < MAXP; ++i)
        sup_cnt[i] = 0;
    for (int i = 0; i < MAXN; ++i) {
        if (cnt[i] !=0)
            ++sup_cnt[cnt[i]];
        cnt[i] = 0;
    }
    long long ideal_hash1 = 0, ideal_hash2 = 0, ideal_hash3 = 0;
    for (int i = 0; i < MAXP; ++i) {
        ideal_hash1 = (ideal_hash1 + p1[i] * sup_cnt[i]) % MOD1;
        ideal_hash2 = (ideal_hash2 + p2[i] * sup_cnt[i]) % MOD2;
        ideal_hash3 = (ideal_hash3 + p3[i] * sup_cnt[i]) % MOD3;
        sup_cnt[i] = 0;
    }
    long long now_hash1 = 0, now_hash2 = 0, now_hash3 = 0;
    for (int i = 0; i < s2.size(); ++i) {
        now_hash1 = (now_hash1 + (MOD1 - sup_cnt[cnt[s1[i]]]) * p1[cnt[s1[i]]]) % MOD1;
        now_hash2 = (now_hash2 + (MOD2 - sup_cnt[cnt[s1[i]]]) * p2[cnt[s1[i]]]) % MOD2;
        now_hash3 = (now_hash3 + (MOD3 - sup_cnt[cnt[s1[i]]]) * p3[cnt[s1[i]]]) % MOD3;
        --sup_cnt[cnt[s1[i]]];
        ++cnt[s1[i]];
        ++sup_cnt[cnt[s1[i]]];
        now_hash1 = (now_hash1 + sup_cnt[cnt[s1[i]]] * p1[cnt[s1[i]]]) % MOD1;
        now_hash2 = (now_hash2 + sup_cnt[cnt[s1[i]]] * p2[cnt[s1[i]]]) % MOD2;
        now_hash3 = (now_hash3 + sup_cnt[cnt[s1[i]]] * p3[cnt[s1[i]]]) % MOD3;
    }
    vector<int> ans;
    if (now_hash1 == ideal_hash1 && now_hash2 == ideal_hash2 && now_hash3 == ideal_hash3)
        ans.push_back(1);
    /*cout << 1 << endl;
    for (int j = 0; j < 10; ++j) {
        cout << j << " " << sup_cnt[j] << endl;
    }
    cout << endl;
    for (int i = s2.size(); i < s1.size(); ++i) {
        now_hash1 = (now_hash1 + (MOD1 - sup_cnt[cnt[s1[i]]]) * p1[cnt[s1[i]]]) % MOD1;
        now_hash2 = (now_hash2 + (MOD2 - sup_cnt[cnt[s1[i]]]) * p2[cnt[s1[i]]]) % MOD2;
        now_hash3 = (now_hash3 + (MOD3 - sup_cnt[cnt[s1[i]]]) * p3[cnt[s1[i]]]) % MOD3;
        --sup_cnt[cnt[s1[i]]];
        ++cnt[s1[i]];
        ++sup_cnt[cnt[s1[i]]];
        now_hash1 = (now_hash1 + sup_cnt[cnt[s1[i]]] * p1[cnt[s1[i]]]) % MOD1;
        now_hash2 = (now_hash2 + sup_cnt[cnt[s1[i]]] * p2[cnt[s1[i]]]) % MOD2;
        now_hash3 = (now_hash3 + sup_cnt[cnt[s1[i]]] * p3[cnt[s1[i]]]) % MOD3;
        now_hash1 = (now_hash1 + (MOD1 - sup_cnt[cnt[s1[i - s2.size()]]]) * p1[cnt[s1[i - s2.size()]]]) % MOD1;
        now_hash2 = (now_hash2 + (MOD2 - sup_cnt[cnt[s1[i - s2.size()]]]) * p2[cnt[s1[i - s2.size()]]]) % MOD2;
        now_hash3 = (now_hash3 + (MOD3 - sup_cnt[cnt[s1[i - s2.size()]]]) * p3[cnt[s1[i - s2.size()]]]) % MOD3;
        --sup_cnt[cnt[s1[i - s2.size()]]];
        --cnt[s1[i - s2.size()]];
        ++sup_cnt[cnt[s1[i - s2.size()]]];
        now_hash1 = (now_hash1 + sup_cnt[cnt[s1[i - s2.size()]]] * p1[cnt[s1[i - s2.size()]]]) % MOD1;
        now_hash2 = (now_hash2 + sup_cnt[cnt[s1[i - s2.size()]]] * p2[cnt[s1[i - s2.size()]]]) % MOD2;
        now_hash3 = (now_hash3 + sup_cnt[cnt[s1[i - s2.size()]]] * p3[cnt[s1[i - s2.size()]]]) % MOD3;
        if (now_hash1 == ideal_hash1 && now_hash2 == ideal_hash2 && now_hash3 == ideal_hash3)
            ans.push_back(i - s2.size() + 2);
        /*cout << i - s2.size() + 2 << endl;
        for (int j = 0; j < 10; ++j) {
            cout << j << " " << sup_cnt[j] << endl;
        }
        cout << endl;
    }
    cout << ans.size() << endl;
    for (auto x : ans)
        cout << x << " ";
    cout << endl;
    return 0;
}
*/

long long pw(long long it, int k) {
    if (k == 0)
        return 1;
    if (k % 2)
        return (pw(it, k - 1) * it) % MOD1;
    return pw((it * it) % MOD1, k / 2);
}

int main () {
    vector<vector<int>> possa(200);
    string a, b;
    cin >> a >> b;
    for (int i = 0; i < b.size(); ++i) {
        possa[(int)b[i] - 33].push_back(i);
    }
    vector<int> search_for(b.size());
    b.clear();
    b.shrink_to_fit();
    for (int i = 0; i < 200; ++i) {
        if (possa[i].size() == 0)
            continue;
        search_for[possa[i][0]] = 1;
        for (int j = 1; j < possa[i].size(); ++j) {
            search_for[possa[i][j]] = possa[i][j] - possa[i][j - 1] + 1;
        }
        possa[i].clear();
        possa[i].shrink_to_fit();
    }
    for (int i = 0; i < a.size(); ++i) {
        possa[(int)a[i] - 33].push_back(i);
    }
    vector<int> text(a.size() + 1);
    text.back() = 1;
    for (int i = 0; i < 200; ++i) {
        if (possa[i].size() == 0)
            continue;
        text[possa[i][0]] = 1;
        for (int j = 1; j < possa[i].size(); ++j) {
            text[possa[i][j]] = possa[i][j] - possa[i][j - 1] + 1;
        }
    }
    for (int i = 0; i < 200; ++i)
        possa[i].push_back(text.size() - 1);
    /*p1[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        p1[i] = ((long long)p1[i - 1] * P1) % MOD1;
    }*/
    long long id_hash = 0;
    for (int i = 0; i < search_for.size(); ++i) {
        id_hash = (id_hash * P1 + search_for[i]) % MOD1;
    }
    long long now_hash = 0;
    for (int i = 0; i < search_for.size(); ++i) {
        now_hash = (now_hash * P1 + text[i]) % MOD1;
    }
    vector<bool> ans(a.size());
    vector<int> ids(200);
    if (now_hash == id_hash)
        ans[0] = 1;
    for (int i = search_for.size(); i < text.size() - 1; ++i) {
        int t = (int)a[i - search_for.size()] - 33;
        now_hash = (now_hash + (MOD1 - (long long)text[i - search_for.size()]) * pw(P1, search_for.size() - 1)) % MOD1;
        now_hash = (now_hash * P1 + text[i]) % MOD1;
        long long last_val = text[possa[t][++ids[t]]];
        text[possa[t][ids[t]]] = 1;
        if (possa[t][ids[t]] <= i) {
            now_hash = (now_hash + (MOD1 - last_val + 1ll) * (long long)pw(P1, i - possa[t][ids[t]])) % MOD1;
        }
        //cout << now_hash << " " << id_hash << endl;
        if (now_hash == id_hash)
            ans[i - search_for.size() + 1] = 1;
    }
    int kolvo = 0;
    for (auto x : ans)
        if (x)
            ++kolvo;
    cout << kolvo << endl;
    for (int i = 0; i < a.size(); ++i)
        if (ans[i])
            cout << i + 1 << " ";
    cout << endl;
    return 0;
}
