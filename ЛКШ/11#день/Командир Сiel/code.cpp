#include <iostream>
#include <vector>

using namespace std;

int main(){
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int q;
    cin >> q;
    vector<int> v;
    int sk = 0;
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            cout << v.size() - sk << endl;
        }
        if (t == 2) {
            cout << v[sk] << endl;
            sk = sk + 1;
        }
        if (t == 3) {
            int id;
            cin >> id;
            v.push_back(id);
            cout << v.size() - sk << endl;
        }
        if (t == 4) {
            int x;
            cin >> x;
            if (x + sk - 1 >= v.size())
                cout << "-1" << endl;
            else
                cout << v[x + sk - 1] << endl;
        }
    }
    return 0;
}
