#include<bits/stdc++.h>

    using namespace std;

    int  sizet = 1;

    int gcd(int a, int b){
        if(b == 0)return a;
        return gcd(b, a % b);
    }

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
                tree[i] = gcd(tree[i * 2] , tree[i * 2 + 1]);
            }
        }
        int gcd1(int l, int r, int n = 1, int tl = 0, int tr = sizet)
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
            return gcd(gcd1(l, r, n * 2, tl, mid), gcd1(l, r, 2 * n + 1, mid, tr));
        }
        void update(int pos){
            pos /= 2;
            tree[pos] = gcd(tree[pos * 2], tree[pos * 2 + 1]);
            if(pos == 1){
                return;
            }
            update(pos);
        }
    };

    int main()
    {
        int n;
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++)
        {
            cin >> v[i];
        }
        Tree x(v);
        int q;
        cin >> q;
        for (int i = 0; i < q; i++)
        {
            char c;
            cin >> c;
            if (c == 'u')
            {
                int a, b;
                cin >> a >> b;
                a--;
                x.tree[sizet + a] = b;
                x.update(sizet + a);
            }
            else
            {
                int a, b, k;
                cin >> a >> b;
                a--;
                //b--;
                cout <<x.gcd1(a, b) << endl;
            }
        }

    }

