#include <bits/stdc++.h>

using namespace std;

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
    if (decart[A]->prior < decart[B]->prior) {
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

vector<int> anc;

void count_(int p, int v) {
    anc[v] = p;
    //cout << v + 1 << ": " << decart[v]->l + 1 << " " << decart[v]->r + 1 << " (" << p + 1 << ")" << endl;
    if (decart[v]->l != -1) {
       count_ (v, decart[v]->l);
    }
    if(decart[v]->r != -1) {
        count_(v, decart[v]->r);
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    anc.resize(n);
    int root = -1;
    for(int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        decart.push_back(new Node(x, y));
        pair<int, int> p = split(root, x);
        root = merg(p.first, merg(i, p.second));
    }
    count_(-1, root);
    printf("YES\n");
    for(int i = 0; i < n; ++i) {
        printf("%d %d %d\n", anc[i] + 1, decart[i]->l + 1, decart[i]->r + 1);
    }
    return 0;
}

