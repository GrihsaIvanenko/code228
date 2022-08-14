#include <bits/stdc++.h>

using namespace std;

long long solve(pair<long long, long long> a, pair<long long, long long> b){
    return (b.second - a.second + a.first - b.first - 1) / (a.first - b.first);
}

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<pair<long long, long long>> trees(n);
    for (int i = 0; i < n; ++i){
        cin >> trees[i].first;
    }
    for (int i = 0; i < n; ++i){
        cin >> trees[i].second;
    }
    vector<pair<long long, pair<long long, long long>>> hull;
    hull.push_back({0, {trees[0].second, 0}});
    for (int i = 1; i < n; ++i){
        int l = 0, r = hull.size();
        while (r - l > 1){
            int mid = (l + r) >> 1;
            if (trees[i].first >= hull[mid].first){
                l = mid;
            }
            else{
                r = mid;
            }
        }
        long long dp = trees[i].first * hull[l].second.first + hull[l].second.second;
        while (hull.size() > 1 && solve({trees[i].second, dp}, hull.back().second) <= hull.back().first){
            hull.pop_back();
        }
        hull.push_back({solve({trees[i].second, dp}, hull.back().second), {trees[i].second, dp}});
    }
    cout << hull.back().second.second << '\n';
    return 0;
}
