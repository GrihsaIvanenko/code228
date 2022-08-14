#include <bits/stdc++.h>

using namespace std;

struct Node {
    vector<int> go;
    int anc, suf;
    Node() {
        go.assign(26, -1);
        anc = 0;
        suf = -1;
    }
};

vector<Node> v;

int last = 0;

void add(char c) {
    c -= 'a';
    int A = last;
    int B = v.size();
    v.push_back(Node());
    v[B].anc = A;
    v[B].suf = 0;
    for (; A != -1; A = v[A].suf) {
        if (v[A].go[c] == -1) {
            v[A].go[c] = B;
            continue;
        }
        int C = v[A].go[c];
        if (v[C].anc == A) {
            v[B].suf = C;
            break;
        }
        int D = v.size();
        v.push_back(Node());
        v[D].go = v[C].go;
        v[D].suf = v[C].suf;
        v[D].anc = A;
        v[C].suf = D;
        v[B].suf = D;
        for (; A != -1 && v[A].go[c] == C; A = v[A].suf)
            v[A].go[c] = D;
        break;
    }
    last = B;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    v.push_back(Node());
    char t;
    string s;
    while (cin >> t) {
        cin >> s;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] >= 'A' && s[i] <= 'Z')
                s[i] = s[i] - 'A' + 'a';
        }
        if (t == '?') {
            bool fail = false;
            int id = 0;
            for (auto x : s) {
                id = v[id].go[x - 'a'];
                if (id == -1)  {
                    fail = true;
                    break;
                }
            }
            if (fail) {
                cout << "NO\n";
            } else {
                cout << "YES\n";
            }
        } else {
            for (auto x : s)
                add(x);
        }
    }
    return 0;
}
