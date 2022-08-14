#include <bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
    Point() {}
    Point(long long a, long long b) {
        x = a;
        y = b;
    }
};

Point operator -(Point A, Point B) {
        return Point(A.x - B.x, A.y - B.y);
}

long long cross(Point A, Point B) {
    return A.x * B.y - A.y * B.x;
}

long long dust(Point A) {
    return A.x * A.x + A.y * A.y;
}

int find_left_down(vector<Point> &v) {
    int ans = 0;
    for (int i = 1; i < v.size(); ++i)
        if (v[i].y < v[ans].y || (v[i].y == v[ans].y && v[i].x < v[ans].x))
            ans = i;
    return ans;
}

int find_(bool left, int beg, vector<Point>&v, vector<int> &used) {
    int cur = -1;
    for (int i = 0; i < used.size(); ++i) {
        if (!used[i])
            cur = i;
    }
    if (cur == -1)
        return cur;
    for (int i = 0; i < used.size(); ++i) {
        if (used[i])
            continue;
        if (left) {
            if (cross (v[cur] - v[beg], v[i] - v[beg]) < 0 ||
            (cross (v[cur] - v[beg], v[i] - v[beg]) == 0) && dust(v[cur] - v[beg]) < dust(v[i] - v[beg]))
                cur = i;
        } else {
            if (cross (v[cur] - v[beg], v[i] - v[beg]) > 0 ||
            (cross (v[cur] - v[beg], v[i] - v[beg]) == 0) && dust(v[cur] - v[beg]) < dust(v[i] - v[beg]))
                cur = i;
        }
    }
    return cur;
}

int main() {
    //cin.tie(0);
    //cout.tie(0);
    //ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<Point> v(n);
    for (int i = 0; i < n; ++i) {
        long long a, b;
        cin >> a >> b;
        v[i] = Point(a, b);
    }
    int beg = find_left_down(v);
    vector<int> used(n, 0), ans = {beg};
    used[beg] = 1;
    string autoroot;
    cin >> autoroot;
    for (int i = 0; i < autoroot.size(); ++i) {
        int to;
        if (autoroot[i] == 'L') {
            to = find_(1, beg, v, used);
        } else {
            to = find_(0, beg, v, used);
        }
        if (to == -1) {
            cout << "-1\n";
            return 0;
        }
        used[to] = 1;
        ans.push_back(to);
        beg = to;
    }
    int to = find_(0, beg, v, used);
    if (to == -1) {
        cout << -1 << '\n';
        return 0;
    }
    ans.push_back(to);
    for (auto x : ans)
        cout << x + 1 << " ";
    cout << '\n';
    return 0;
}
