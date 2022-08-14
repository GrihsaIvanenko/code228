#include <bits/stdc++.h>

using namespace std;

void solve(){
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    if (n * m != (a + b) * 3){
        cout << "NO\n";
        return;
    }
    if (a % 2){
        cout << "NO\n";
        return;
    }
    if (n > m)
        swap(n, m);
    if (n == 1 && b > 0){
        cout << "NO\n";
        return;
    }

}

int main() {
    int cnt = 0;
    for (int i = 1; i <=  100; ++i)
        for (int j = i; j <= 100; ++j)
            if (i * j <= 100)
                ++cnt;
    cout << cnt << endl;
    //solve();
    return 0;
}
