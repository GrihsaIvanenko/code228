#include <bits/stdc++.h>

using namespace std;

int sizet = 1;

struct Tree
{
    vector<pair<int,int>> tree;

    Tree(vector<pair<int,int>> & v)
    {
        sizet = 1;

        while(sizet < v.size())sizet *= 2;
        tree.resize(2 * sizet);

        for(int i = sizet; i < sizet + v.size(); ++i)
            tree[i] = {v[i - sizet].first, i - sizet + 1};

        for(int i = sizet - 1; i > 0; --i){
            tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    pair<int,int> sums(int l, int r, int n = 1, int tl = 0, int tr = sizet){
        if(tl >= r || tr <= l){
            return {0, 0};
        }

        if(tl >= l && tr <= r){
            return tree[n];
        }

        int mid = (tl + tr) / 2;
        return max(sums(l, r, 2 * n, tl, mid), sums(l, r, 2 * n + 1, mid, tr));
    }

    void change(int pos, int x, int n = 1, int tl = 0, int tr = sizet){
        if(pos >= tr || pos < tl){
            return;
        }

        if(tl == tr){
          //   tree[n] = x;
             return;
        }

        int mid = (tl + tr) / 2;
        change(pos, x, 2 * n, tl, mid), change(pos, x, 2 * n + 1, mid, tr);
       // tree[n] = tree[2 * n] + tree[2 * n + 1];

    }
};

int main()
{
    int n;
    cin >> n;
    vector<pair<int,int>> v;

    for(int i = 0; i < n; ++i){
        int x;
        cin >> x;

        v.push_back({x, i + 1});
    }
    Tree x = Tree(v);
    cin >> n;
    for(int i = 0; i < n; ++i){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        pair<int,int> ans = x.sums(a, b + 1);


        cout << ans.first << " " << ans.second << endl;
    }

    return 0;
}
