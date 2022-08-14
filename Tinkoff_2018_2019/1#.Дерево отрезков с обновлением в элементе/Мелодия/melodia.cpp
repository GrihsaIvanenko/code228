#include <bits/stdc++.h>

using namespace std;

int main(){
    multiset<int> s;
    int n, m, l;
    cin >> n >> m >> l;
    for(int i = 0; i < n; ++i){
        int x;
        cin >> x;
        s.insert(-x);
    }
    set<int> is;
    for(int i = 0; i < m; ++i){
        int x;
        cin >> x;
        if(is.find(x) != is.end()){
            continue;
        }
        if(s.lower_bound(-x) == s.end()){
            cout << i << endl;
            return 0;
        }
        if(x - abs(*s.lower_bound(-x)) > l){
            cout << i << endl;
            return 0;
        }
        l -= (x - abs(*s.lower_bound(-x)));
        is.insert(x);
        s.erase(s.find(*s.lower_bound(-x)));
    }
    cout << m << endl;
    return 0;
}
