#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5800080;

vector<int> ld(MAXN);

vector<int> simple;

char cool[7 * MAXN];

int main () {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    for (int i = 2; i < MAXN; ++i) {
        if (ld[i] == 0) {
            simple.push_back(i);
            ld[i] = i;
        }
        for (int j = 0; j < simple.size() && simple[j] <= ld[i] && (long long)simple[j] * (long long)i < (long long)MAXN; ++j) {
            ld[simple[j] * i] = simple[j];
        }
    }
    ld.clear();
    ld.shrink_to_fit();
    int id = 0;
    vector<int> ban(simple.size());
    int tttt = 0;
    for (auto x : simple) {
        string s = to_string(x);
        for (auto y : s)
            cool[id++] = y;
        ban[tttt++] = id;
    }
    vector<int> poss[10];
    for (int i = 0; i < id; ++i) {
        poss[cool[i] - '0'].push_back(i);
    }
    for (int i = 0; i < 10; ++i)
        poss[i].push_back(id);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b, bb;
        cin >> a >> b;
        bb = b;
        int pos = -1, max_pos = ban[a - 1];
        vector<char> ans(max_pos);
        int did = 0;
        while (pos < max_pos) {
            int cur;
            for (int i = 9; i > -1; --i) {
                if (poss[i][upper_bound(poss[i].begin(), poss[i].end(), pos) - poss[i].begin()] - pos - 1 <= b) {
                    cur = upper_bound(poss[i].begin(), poss[i].end(), pos) - poss[i].begin();
                    ans[did++] = (i + '0');
                    b -= poss[i][cur] - pos - 1;
                    pos = poss[i][cur];
                    break;
                }
            }
        }
        for (int i = 0; i < max_pos - bb; ++i)
            cout << ans[i];
        cout << endl;
    }
    return 0;
}
