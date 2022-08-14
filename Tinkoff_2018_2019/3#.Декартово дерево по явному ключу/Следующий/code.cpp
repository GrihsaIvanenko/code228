#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9;

struct Node{
    int key, prior, l, r;
    Node(int x, int y) {
        key = x;
        prior = y;
        l = -1;
        r = -1;
    }
};

vector<Node*> decart;

int merg(int A, int B) {
    if  (A == -1) {
        return B;
    }
    if (B == -1) {
       return A;
    }
    if (decart[A]->prior > decart[B]->prior) {
       decart[A]->r = merg(decart[A]->r, B);
       return A;
    }
    decart[B]->l = merg(A, decart[B]->l);
    return B;
}

pair<int, int> split(int A, int x) {
    if (A == -1) {
       return {-1, -1};
    }
    if (decart[A]->key < x) {
        pair<int, int> p = split(decart[A]->r, x);
        decart[A]->r = p.first;
        return {A, p.second};
    } else {
        pair<int, int> p = split(decart[A]->l, x);
        decart[A]->l = p.second;
        return {p.first, A};
    }
}

int go_left(int v) {
    if (v == -1) {
       return -1;
    }
    if(decart[v]->l != -1) {
        return go_left(decart[v]->l);
    }
    return decart[v]->key;
}

void print(int v) {
    if(v == -1) {
        return;
    }
    print(decart[v]->l);
    cout << decart[v]->key << " " << decart[v]->l << " " << decart[v]->r << '\n';
    print(decart[v]->r);
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    srand(0);
    int last = 0, root = -1;
    for (int i = 0; i < n; ++i) {
        char t;
        int tmp;
        cin >> t >> tmp;
        pair<int, int> p;
        if (t == '?') {
            p = split(root, tmp);
            last = go_left(p.second);
            cout << last << '\n';
        } else {
            tmp = ((last + MOD) % MOD + tmp) % MOD;
            p = split(root, tmp);
            last = go_left(p.second);
            if (last != tmp) {
                decart.push_back(new Node(tmp, rand()));
                p.second = merg(decart.size() - 1, p.second);
            }
            last = 0;
        }
        root = merg(p.first, p.second);
       // print(root);cout << '\n';
    }
    return 0;
}
