#include<bits/stdc++.h>

    using namespace std;

    int  sizet = 1;

    struct Tree
    {
        vector<int> tree;
        Tree(vector<int> &v)
        {
            while (sizet < v.size())sizet *= 2;

            tree.resize(2 * sizet);
            for (int i = sizet; i < sizet + v.size(); i++)
            {
                tree[i] = v[i - sizet];
            }
            for (int i = sizet - 1; i > 0; i--)
            {
                tree[i] = tree[i * 2] + tree[i * 2 + 1];
            }
        }
        int sums(int l, int r, int n = 1, int tl = 0, int tr = sizet)
        {
            if (tl >= r || tr <= l)
            {
                return 0;
            }
            if (tl >= l && tr <= r)
            {
                return tree[n];
            }
            int mid = (tl + tr) / 2;
            return sums(l, r, n * 2, tl, mid) +sums(l, r, 2 * n + 1, mid, tr);
        }
        void update(int pos){
            pos /= 2;
            tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
            if(pos == 1){
                return;
            }
            update(pos);
        }
        int lover_bound(int a, int l = 0, int r = sizet){
            if(l + 1 == r){
                return l;
            }
            int mid = (l + r) / 2;
          //  cout << sums(max(l, a), mid) << " " << l << " " << mid << " " << r << endl;
            if(mid > a && sums(max(l, a), mid) > 0){
                return lover_bound(a, l, mid);
            }
            else{
                return lover_bound(a, mid, r);
            }
        }
    };

    int main()
    {
        int n;
      //  cin >> n;
        vector<int> v(1000000, 1);
        Tree x(v);
        int q;
        cin >> q;
        for(int i = 0; i < q; i++)
        {
            int a;
            cin >> a;
            if(a < 0){
                a++;
                x.tree[sizet - a] = 1;
                x.update(sizet - a);
            }
            else{
                int xe = 0;
                xe = x.lover_bound(a - 1);
                cout << xe + 1 << endl;
                x.tree[sizet + xe] = 0;
                x.update(sizet + xe);
                for(int i = 0; i < 10; ++i){
                   // cout << x.tree[i + sizet] << " ";
                }
               // cout << endl;
            }
        }
    }
