#include <bits/stdc++.h>

using namespace std;

struct i_p{
     long long x, y;
     i_p(){}
     i_p(long long x1, long long y1){
        x = x1;
        y = y1;
     }
};

i_p operator -(i_p a, i_p b){
    return i_p(a.x - b.x, a.y - b.y);
}

long long v_p(i_p a, i_p b){
    return a.x * b.y - a.y * b.x;
}

long long s_p(i_p a, i_p b){
    return a.x * b.x + a.y * b.y;
}

long double sqare_div_2(vector<i_p> & a){
    long long ans = 0;
    for (int i = 1; i < a.size() - 1; ++i){
        ans += v_p(a[i] - a[0], a[i + 1] - a[0]);
    }
    return ans;
}

bool in(vector<i_p> & a, i_p p){
    if (v_p(a[0] - a[a.size() - 1], p - a[a.size() - 1]) < 0)return false;
    if (v_p(a[1] - a[0], p - a[0]) < 0)return false;
    int l = 1, r = a.size() - 1;
    while (l + 1 < r){
        int mid = (l + r) / 2;
        if (v_p(a[mid] - a[0], p - a[0]) >= 0)l = mid;
        else r = mid;
    }
    return(v_p(a[r] - a[l], p - a[l]) >= 0);
}

void make_good(vector<i_p> & v){
    long long min_y = 1e9, min_x = 1e9, ind = 0;
    for (int i = 0; i < v.size(); ++i){
        if (v[i].y < min_y){
            min_y = v[i].y;
            min_x = v[i].x;
            ind = i;
        }
        else if (v[i].y == min_y){
            if (v[i].x < min_x){
                min_x = v[i].x;
                ind = i;
            }
        }
    }
    vector<i_p> local;
    for (int i = ind; i < v.size(); ++i){
        local.push_back(v[i]);
    }
    for (int i = 0; i < ind; ++i){
        local.push_back(v[i]);
    }
    for (int i = 0; i < v.size(); ++i){
        v[i] = local[i];
    }
}

bool cmp(vector<i_p> a, vector<i_p> b){
    return sqare_div_2(a) <  sqare_div_2(b);
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<vector<i_p>> Points(n);
    for (int ch = 0; ch < n; ++ch){
        int k;
        cin >> k;
        Points[ch].resize(k);
        for (int i = 0; i < k; ++i){
            long long x, y;
            cin >> x >> y;
            Points[ch][i] = i_p(x, y);
        }
        make_good(Points[ch]);
    }
    sort(Points.begin(), Points.end(), cmp);
    int m;
    cin >> m;
    vector<bool> used(n, false);
    for (int ch = 0; ch < m; ++ch){
        long long x, y;
        cin >> x >> y;
        i_p p = i_p(x, y);
        int l = -1, r = n;
        while (l + 1 != r){
            int mid = (l + r) / 2;
            if (in(Points[mid], p))r = mid;
            else l = mid;
        }
        if (r != n)used[r] = true;
        /*long long ans = 0;
        for (int i = 0;i < n; ++i){
            if (used[i]){
                ans += sqare_div_2(Points[i]);
                if (i != 0){
                    ans -= sqare_div_2(Points[i - 1]);
                }
            }
        }
        cout.precision(10);
    cout << fixed << (long double)ans / 2.0 << endl;*/
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i){
        if (used[i]){
            ans += sqare_div_2(Points[i]);
            if (i != 0){
                ans -= sqare_div_2(Points[i - 1]);
            }
        }
    }
    cout.precision(10);
    cout << fixed << (long double)ans / 2.0 << endl;
    return 0;
}
