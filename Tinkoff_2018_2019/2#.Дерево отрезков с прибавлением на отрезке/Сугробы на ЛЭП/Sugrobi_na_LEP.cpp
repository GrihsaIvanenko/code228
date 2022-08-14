#include <bits/stdc++.h>

using namespace std;

int sizet = 1;

struct Tree
{
    vector<int> tree;
    vector<int> push;
    Tree(vector<int> & v)
    {


        while(sizet < v.size())
            sizet *= 2;
        tree.resize(2 * sizet);
        push.resize(2 * sizet);

        for(int i = sizet; i < sizet + v.size(); ++i)
            tree[i] = v[i - sizet];

        for(int i = sizet - 1; i > 0; --i)
        {
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
        }
    }
    void update(int n, int tl, int tr){
        if(n < sizet){
            tree[n] = tree[n * 2] + tree[n * 2 + 1] + (push[n * 2] * (tr - tl) / 2) + (push[n * 2 + 1] * (tr - tl) / 2);
            push[n * 2] += push[n];
            push[n * 2 + 1] += push[n];
        }
        tree[n] += push[n] * (tr - tl);
        push[n] = 0;
    }
    int sums(int l, int r, int n = 1, int tl = 0, int tr = sizet)
    {
        if(tl >= r || tr <= l)
        {
            return 0;
        }
        update(n, tl, tr);

        if(tl >= l && tr <= r)
        {
            return tree[n];
        }

        int mid = (tl + tr) / 2;
        return sums(l, r, 2 * n, tl, mid) + sums(l, r, 2 * n + 1, mid, tr);
    }
    void plus_(int l, int r, int x, int n = 1, int tl = 0, int tr = sizet){
        if(tl >= r || tr <= l)
        {
            return;
        }

        if(tl >= l && tr <= r)
        {
            push[n] += x;
            return;
        }
        int mid = (tl + tr) / 2;
        plus_(l, r, x, n * 2, tl, mid);
        plus_(l, r, x, n * 2 + 1, mid, tr);
        update(n, tl, tr);
        return;
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> v;
    v.assign(n, 0);
    Tree x = Tree(v);
    int m;
    cin >> m;
    for(int i = 0; i < m; ++i){
        int k;
        cin >> k;
        if(k % 2){
            int left, right, to;
            cin >> left >> right >> to;
            x.plus_(left, right, to);

        }
        else{
            int left, right;
            cin >> left >> right;
            cout << x.sums(left, right) << endl;
        }
    }
}
