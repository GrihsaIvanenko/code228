#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 200001, size_of_block = 400;

long long fenv[MAXN];

long long p[MAXN];

void add(long long pos, long long inc) {
    for (; pos < MAXN; pos = pos | (pos + 1)) {
        fenv[pos] += inc;
    }
}

long long sum(long long r) {
    long long ans = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) {
        ans += fenv[r];
    }
    return ans;
}

long long answer = 0;

long long move_(long long &from, long long to, bool r) {
    if (r) {
        if (from < to) {
            for (; from < to; ++from) {
                answer += sum(MAXN - 1);
                answer -= sum(p[from]);
                add(p[from], 1);
            }
        } else {
            for (; from > to; --from) {
                answer += sum(p[from - 1]);
                answer -= sum(MAXN - 1);
                add(p[from - 1], -1);
            }
        }
    } else {
        if (from < to) {
            for (; from < to; ++from) {
                answer -= sum(p[from] - 1);
                add(p[from], -1);
            }
        } else {
            for (; from > to; --from) {
                answer += sum(p[from - 1] - 1);
                add(p[from - 1], 1);
            }
        }
    }
    return answer;
}

void solve() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    for (long long i = 0; i < MAXN; ++i) {
        fenv[i] = 0;
    }
    long long n, m;
    cin >> n;
    for (long long i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i];
    }
    cin >> m;
    vector<pair<pair<long long, long long>, pair<long long, long long>>> tasks(m);
    vector<long long> ans(m);
    for (long long i = 0; i < m; ++i) {
        long long a, b;
        cin >> a >> b;
        --a;
        tasks[i] = {{a / size_of_block, b}, {a, i}};
    }
    sort(tasks.begin(), tasks.end());
    long long lb = 0, rb = 0;
    for (long long i = 0; i < m; ++i) {
        if (lb > tasks[i].second.first) {
            move_(lb, tasks[i].second.first, 0);
            //cout << " " << lb << " A" << endl;
        }
        if (rb < tasks[i].first.second) {
            move_(rb, tasks[i].first.second, 1);
            //cout << " " << rb << " B" << endl;
        }
        if (lb < tasks[i].second.first) {
            move_(lb, tasks[i].second.first, 0);
            //cout << " " << lb << " C" << endl;
        }
        if (rb > tasks[i].first.second) {
            move_(rb, tasks[i].first.second, 1);
            //cout << " " << rb << " D" << endl;
        }
        ans[tasks[i].second.second] = answer;
    }
    for (long long i = 0; i < m; ++i) {
        cout << ans[i] << '\n';
    }
}

int main() {
    solve();
    return 0;
}
