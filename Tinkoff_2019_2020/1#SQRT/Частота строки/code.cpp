#include <bits/stdc++.h>

using namespace std;

#define DEBUGs

const int SZ = 10;

const int MAXN = 2e6;

int timer = 1;

int go[26][MAXN];

vector<int> term[MAXN];

int main() {
    for (int i = 0; i < 26; ++i)
        memset(go[i], 0, sizeof(go[i]));
    #ifdef DEBUG
        freopen("t.cpp", "r", stdin);
    #else
        cin.tie(0);
        cout.tie(0);
        ios_base::sync_with_stdio(0);
    #endif
    string s;
    cin >> s;
    for (int st = 0; st < (int)s.size(); ++st) {
        int id = 0;
        for (int len = 1; len <= SZ && (st + len <= (int)s.size()); ++len) {
            if (!go[s[st + len - 1] - 'a'][id]) {
                go[s[st + len - 1] - 'a'][id] = timer++;
                if (timer >= MAXN)
                    assert(false);
            }
            id = go[s[st + len - 1] - 'a'][id];
            term[id].push_back(st);
        }
    }
    int n;
    cin >> n;
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        int k;
        string t;
        cin >> k >> t;
        int Tlen = t.size();
        if (t.size() > SZ) {
            t += "#" + s;
            vector<int> inp;
            vector<int> pf(t.size());
            for (int i = 1; i < (int)t.size(); ++i) {
                int cur = pf[i - 1];
                while (cur != -1 && t[cur] != t[i]) {
                    if (cur == 0)
                        cur = -1;
                    else
                        cur = pf[cur - 1];
                }
                pf[i] = cur + 1;
                if (pf[i] == (int)t.size() - (int)s.size() - 1)
                    inp.push_back(i + Tlen);
            }
            if (k > (int)inp.size()) {
                ans[i] = -1;
                continue;
            }
            int answer = s.size();
            for (int j = k - 1; j < (int)inp.size(); ++j)
                answer = min(answer, inp[j] - inp[j - k + 1]);
            ans[i] = answer + Tlen;
        } else {
            int id = 0;
            bool fail = false;
            for (auto x : t) {
                if (!go[x - 'a'][id])
                    fail = true;
                id = go[x - 'a'][id];
            }
            if (fail) {
                ans[i] = -1;
            } else if ((int)term[id].size() < k) {
                ans[i] = -1;
            } else {
                int answer = s.size();
                for (int j = k - 1; j < (int)term[id].size(); ++j)
                    answer = min(answer, term[id][j] - term[id][j - k + 1]);
                ans[i] = answer + Tlen;
            }
        }
    }
    for (auto x : ans)
        cout << x << '\n';
    return 0;
}
