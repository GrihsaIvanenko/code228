#include <bits/stdc++.h>

using namespace std;

vector<long long> y;

struct segtree{
    int lb, rb, mid, push;
    long long val = 0;
    segtree *l = nullptr, *r = nullptr;
    segtree(int lb_, int rb_) {
        lb = lb_;
        rb = rb_;
        mid = (lb + rb) >> 1;
        val = y[rb] - y[lb];
        push = 0;
    }
    void upd() {
        if (push != 0) {
           val = 0;
        } else {
            if (lb + 1 == rb) {
                val = y[rb] - y[lb];
            } else {
                val = 0;
                if (l) {
                    val += l->val;
                } else {
                    val += y[mid] - y[lb];
                }
                if (r) {
                    val += r->val;
                } else {
                    val += y[rb] - y[mid];
                }
            }
        }
    }
    void change(int le, int re, int inc) {
         if (le >= rb || re <= lb) {
           return;
        }
        if (le <= lb && rb <= re) {
           push += inc;
           upd();
           return;
        }
        if (le < mid) {
            if (!l) {
               l = new segtree(lb, mid);
            }
            l->change(le, re, inc);
        }
        if (re > mid) {
            if (!r) {
                r = new segtree(mid, rb);
            }
            r->change(le, re, inc);
        }
        upd();
    }
};

int main() {
    int n;
    cin >> n;
    map<int, int> compress;
    y.push_back(-1000000007);
    vector<pair<pair<int, int>, pair<int, int>>> input;
    for(int i = 0; i < n; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if(a > c) {
            swap(a, c);
        }
        if(b > d) {
            swap(b, d);
        }
        ++c;
        ++d;
        input.push_back({{a, c}, {b, d}});
        y.push_back(b);
        y.push_back(d);
    }
    y.resize(unique(y.begin(), y.end()) - y.begin());
    y.push_back(1000000007);
    sort(y.begin(), y.end());
    for (int i = 0; i < y.size(); ++i) {
        compress[y[i]] = i;
    }
    vector<pair<pair<int, int>, pair<int, int>>> events;
    for(int i = 0; i < input.size(); ++i) {
        events.push_back({{input[i].first.first, 1}, {compress[input[i].second.first], compress[input[i].second.second]}});
        events.push_back({{input[i].first.second, -1}, {compress[input[i].second.first], compress[input[i].second.second]}});
    }
    sort(events.begin(), events.end());
    long long ans = 0;
    segtree *root = new segtree(0, y.size() - 1);
    for(int i = 0; i < events.size(); ++i) {
        if(i != 0) {
            ans += (long long)(2000000014ll - root->val) * (long long)(events[i].first.first - events[i - 1].first.first);
        }
        root->change(events[i].second.first, events[i].second.second, events[i].first.second);
        //cout<< events[i].first.first << " " << events[i].first.second << " " << events[i].second.first << " " << events[i].second.second << endl;
    }
    cout << ans << endl;
    return 0;
}
