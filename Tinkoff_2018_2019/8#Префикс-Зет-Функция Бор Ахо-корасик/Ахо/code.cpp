#include <bits/stdc++.h>

using namespace std;

bool FFF = 1;

int n, m, timer = 0, id = 0;

vector<int> ans;

pair<int, int> f(int a) {
    if (a < n) {
       return {0, a};
    }
    return {1, a - n - 1};
}

void print(pair<int, int> p) {
    if (p.first) {
       cout << 't';
    } else {
        cout << 's';
    }
    cout << ' ' << p.second + 1 << ' ';
}


bool comp(int a, int b) {
    int AA = a, BB = b;
    if (a == n || b == n) {
        return false;
    }
    if (timer == 5) {
       timer = 0;
       cout << "$ " << ans[id++] << endl;
       ans[id] = max(ans[id], ans[id - 1]);
    }
    ++timer;
    if (a > b) {
        swap(a, b);
    }
    pair<int, int> p1 = f(a), p2 = f(b);
    while (p2.first && p2.second > id) {
        cout << "$ " << ans[id++] << endl;
        ans[id] = max(ans[id - 1], ans[id]);
        timer = 1;
    }
    if  (id == m) {
        FFF = 0;
        return false;
    }
    print(p1);
    print(p2);
    cout << endl;
    string feedback;
    cin >> feedback;
    return feedback == "Yes";
}

int main() {
    cin >> n >> m;
    if (n > m)  {
        for (int i = 0; i < m; ++i) {
            cout << "$ 0" << endl;
        }
        return 0;
    }
    ans.resize(m);
    vector<int> p(n + m + 1);
    for (int i = 1; i < n + m + 1; ++i) {
        int cur = p[i - 1];
        while (!comp(cur, i) && cur > 0 && FFF) {
            cur = p[cur - 1];
        }
        if (!FFF) {
            return 0;
        }
        if (comp(i, cur) && FFF) {
           p[i] = cur + 1;
        }
        if (!FFF) {
            return 0;
        }
        if (i > n + 1) {
            if (p[i] == n) {
                ans[i - n - 1] = ans[i - n - 2] + 1;
            } else {
                ans[i - n - 1] = ans[i - n - 2];
            }
        } else if (i == n + 1 && p[i] == n) {
            ans[i - n - 1] = 1;
        }
    }
    return 0;
}
