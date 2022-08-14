#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

const int MAXN = 1000;

vector<int> g[MAXN];

int mt[MAXN], pr[MAXN], ran[MAXN];

char used[MAXN];

struct task{
    int time, ax, bx, ay, by;
    task(){}
    task(int time_, int ax_, int ay_, int bx_, int by_){
        time = time_;
        ax = ax_;
        bx = bx_;
        ay = ay_;
        by = by_;
    }
};

vector<task> tasks;

int get(int x) {
    if (pr[x] == x) {
        return x;
    }
    return pr[x] = get(pr[x]);
}

void unite(int x, int y) {
    x = get(x);
    y = get(y);
    pr[y] = x;
    return;
    if (ran[x] < ran[y]) {
        swap(x, y);
    }
    ran[x] = max(ran[x], ran[y] + 1);
}

bool dfs(int v) {
    if (used[v] == 1) {
        return 0;
    }
    used[v] = 1;
    for (auto x : g[v]) {
        if (mt[x] == -1) {
            mt[x] = v;
            return true;
        }
    }
    for (auto x : g[v]) {
         if (dfs(mt[x])) {
            mt[x] = v;
            return true;
        }
    }
    return false;
}

bool good(int a, int b) {
    return tasks[b].time - tasks[a].time - abs(tasks[a].bx - tasks[a].ax) - abs(tasks[a].by - tasks[a].ay) -  abs(tasks[b].ax - tasks[a].bx) - abs(tasks[b].ay - tasks[a].by)> 0;
}

void solve() {
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        string s;
        int a, b, c, d;
        cin >> s >> a >> b >> c >> d;
        tasks.push_back(task((s[0] - '0') * 600 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + (s[4] - '0'), a, b, c, d));
    }
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                if (good(i, j)) {
                    g[i].push_back(j);
                }
            }
        }
    }
    for (int i = 0; i < MAXN; ++i) {
        pr[i] = i;
        ran[i] = used[i] = 0;
        mt[i] = -1;
    }
    for (int i = 0; i < MAXN; ++i) {
        dfs(i);
        for (int j = 0; j < MAXN; ++j) {
            used[j] = 0;
        }
    }
    for (int i = 0; i < k; ++i) {
        if (mt[i] != -1) {
            unite(i, mt[i]);
        }
    }
    set<int> ans;
    for (int i = 0; i < k; ++i) {
        ans.insert(get(i));
    }
    cout << ans.size() << '\n';
}

int main() {
    solve();
    return 0;
}
