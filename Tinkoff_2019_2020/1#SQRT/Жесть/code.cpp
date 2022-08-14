#include <bits/stdc++.h>

using namespace std;

#define DEBUGs

const int C = 8000, NORMA = 1000;

struct Node {
    bool rev, push;
    int to;
    vector<int> in_me, sorted;
    Node() {
        rev = push = false;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> norm((NORMA + n - 1) / NORMA);
    int N = n;
    for (int i = 0; i < norm.size(); ++i) {
        norm[i] = min(N, NORMA);
        N -= norm[i];
    }
    vector<int> parts_order;
    vector<Node> d;
    int CNTCNT = 0, POSPOS = 0;
    for (int i = 0; i < n; ++i) {
        if (CNTCNT == 0) {
            parts_order.push_back(d.size());
            d.push_back(Node());
            d.back().in_me.reserve(norm[POSPOS]);
        }
        int x;
        cin >> x;
        d.back().in_me.push_back(x);
        ++CNTCNT;
        if (CNTCNT == norm[POSPOS]) {
            CNTCNT = 0;
            ++POSPOS;
        }
    }
    for (int i = 0; i < d.size(); ++i) {
        d[i].sorted = d[i].in_me;
        sort(d[i].sorted.begin(), d[i].sorted.end());
    }
    int q;
    cin >> q;
    for (int ICQ = 0; ICQ < q; ++ICQ) {
        string s;
        cin >> s;
        int l, r;
        cin >> l >> r;
        --l;
        int has_before_L = 0;
        int id_first_more_L = -1;
        for (int I = 0; I < parts_order.size(); ++I) {
            int i = parts_order[I];
            if (has_before_L + d[i].in_me.size() > l) {
                id_first_more_L = I;
                break;
            }
            has_before_L += d[i].in_me.size();
        }
        if (has_before_L != l) {
            int new_plohish = d.size();
            d.push_back(Node());
            bool nada = d[parts_order[id_first_more_L]].push;
            if (nada) {
                for (int i = 0; i < d[parts_order[id_first_more_L]].in_me.size(); ++i)
                    d[parts_order[id_first_more_L]].in_me[i] = d[parts_order[id_first_more_L]].to;
                d[parts_order[id_first_more_L]].push = 0;
                d[parts_order[id_first_more_L]].rev = 0;
            }
            int kolvo_to_split = l - has_before_L;
            d[new_plohish].in_me.reserve(kolvo_to_split);
            if (d[parts_order[id_first_more_L]].rev) {
                reverse(d[parts_order[id_first_more_L]].in_me.begin(), d[parts_order[id_first_more_L]].in_me.end());
                d[parts_order[id_first_more_L]].rev = 0;
            }
            for (int i = 0; i < d[parts_order[id_first_more_L]].in_me.size(); ++i)
                if (i < kolvo_to_split)
                    d[new_plohish].in_me.push_back(d[parts_order[id_first_more_L]].in_me[i]);
                else
                    d[parts_order[id_first_more_L]].in_me[i - kolvo_to_split] = d[parts_order[id_first_more_L]].in_me[i];
            for (int i = 0; i < kolvo_to_split; ++i)
                d[parts_order[id_first_more_L]].in_me.pop_back();
            d[new_plohish].sorted = d[new_plohish].in_me;
            if (!nada)
                sort(d[new_plohish].sorted.begin(), d[new_plohish].sorted.end());
            d[parts_order[id_first_more_L]].sorted = d[parts_order[id_first_more_L]].in_me;
            if (!nada)
                sort(d[parts_order[id_first_more_L]].sorted.begin(), d[parts_order[id_first_more_L]].sorted.end());
            parts_order.push_back(0);
            for (int i = parts_order.size() - 1; i > id_first_more_L; --i)
                parts_order[i] = parts_order[i - 1];
            parts_order[id_first_more_L] = new_plohish;
            ++id_first_more_L;
        }
        int has_before_R = 0;
        int id_first_more_R = parts_order.size();
        for (int I = 0; I < parts_order.size(); ++I) {
            int i = parts_order[I];
            if (has_before_R + d[i].in_me.size() > r) {
                id_first_more_R = I;
                break;
            }
            has_before_R += d[i].in_me.size();
        }
        if (has_before_R != r) {
            int new_plohish = d.size();
            d.push_back(Node());
            bool nada = d[parts_order[id_first_more_R]].push;
            if (nada) {
                for (int i = 0; i < d[parts_order[id_first_more_R]].in_me.size(); ++i)
                    d[parts_order[id_first_more_R]].in_me[i] = d[parts_order[id_first_more_R]].to;
                d[parts_order[id_first_more_R]].push = 0;
                d[parts_order[id_first_more_R]].rev = 0;
            }
            int kolvo_to_split = r - has_before_R;
            d[new_plohish].in_me.reserve(kolvo_to_split);
            if (d[parts_order[id_first_more_R]].rev) {
                reverse(d[parts_order[id_first_more_R]].in_me.begin(), d[parts_order[id_first_more_R]].in_me.end());
                d[parts_order[id_first_more_R]].rev = 0;
            }
            for (int i = 0; i < d[parts_order[id_first_more_R]].in_me.size(); ++i)
                if (i < kolvo_to_split)
                    d[new_plohish].in_me.push_back(d[parts_order[id_first_more_R]].in_me[i]);
                else
                    d[parts_order[id_first_more_R]].in_me[i - kolvo_to_split] = d[parts_order[id_first_more_R]].in_me[i];
            for (int i = 0; i < kolvo_to_split; ++i)
                d[parts_order[id_first_more_R]].in_me.pop_back();
            d[new_plohish].sorted = d[new_plohish].in_me;
            if (!nada)
                sort(d[new_plohish].sorted.begin(), d[new_plohish].sorted.end());
            d[parts_order[id_first_more_R]].sorted = d[parts_order[id_first_more_R]].in_me;
            if (!nada)
                sort(d[parts_order[id_first_more_R]].sorted.begin(), d[parts_order[id_first_more_R]].sorted.end());
            parts_order.push_back(0);
            for (int i = parts_order.size() - 1; i > id_first_more_R; --i) {
                parts_order[i] = parts_order[i - 1];
            }
            parts_order[id_first_more_R] = new_plohish;
            ++id_first_more_R;
        }
        if (s[0] == 'r') {
            for (int i = id_first_more_L; i < id_first_more_R; ++i)
                d[parts_order[i]].rev = !d[parts_order[i]].rev;
            reverse(parts_order.begin() + id_first_more_L, parts_order.begin() + id_first_more_R);
        } else if (s[0] == 's') {
            int x;
            cin >> x;
            for (int i = id_first_more_L; i < id_first_more_R; ++i) {
                d[parts_order[i]].push = true;
                d[parts_order[i]].to = x;
            }
        } else {
            int x;
            cin >> x;
            int ans = 0;
            for (int I = id_first_more_L; I < id_first_more_R; ++I) {
                int i = parts_order[I];
                if (d[i].push) {
                    if (d[i].to >= x)
                        ans += d[i].in_me.size();
                } else {
                    ans += (d[i].sorted.end() - lower_bound(d[i].sorted.begin(), d[i].sorted.end(), x));
                }
            }
            cout << ans << '\n';
        }
        if (ICQ % C == C - 1) {
            CNTCNT = POSPOS = 0;
            vector<int> new_parts_order;
            vector<Node> new_d;
            for (int I = 0; I < parts_order.size(); ++I) {
                int i = parts_order[I];
                if (d[i].push) {
                    for (int j = 0; j < d[i].in_me.size(); ++j)
                        d[i].in_me[j] = d[i].to;
                    d[i].push = d[i].rev = false;
                }
                if (d[i].rev)
                    reverse(d[i].in_me.begin(), d[i].in_me.end());
                for (int j = 0; j < d[i].in_me.size(); ++j) {
                    if (CNTCNT == 0) {
                        new_parts_order.push_back(new_d.size());
                        new_d.push_back(Node());
                        new_d[POSPOS].in_me.reserve(norm[POSPOS]);
                    }
                    new_d[POSPOS].in_me.push_back(d[i].in_me[j]);
                    ++CNTCNT;
                    if (CNTCNT == norm[POSPOS]) {
                        CNTCNT = 0;
                        ++POSPOS;
                    }
                }
            }
            for (int i = 0; i < new_d.size(); ++i) {
                new_d[i].sorted = new_d[i].in_me;
                sort(new_d[i].sorted.begin(), new_d[i].sorted.end());
            }
            swap(new_parts_order, parts_order);
            swap(d, new_d);
        }
    }
}

int main() {
    #ifdef DEBUG
        freopen("t.cpp", "r", stdin);
    #else
        cin.tie(nullptr);
        cout.tie(nullptr);
        ios_base::sync_with_stdio(false);
    #endif // DEBUG
    solve();
    return 0;
}
