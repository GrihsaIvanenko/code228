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
        tree[0] = 0;
    }
    int k_th_null(int l, int r,  int k, int n = 1,  int tl = 0, int  tr = sizet)
    {
        if (r <= tl || l >= tr || n >= tree.size())
        {
            //cout << "jdfhsdjfsdjks";
            return sizet - 2;
        }
        if (tl + 1 == tr && k == tree[n])
        {
            return n;
        }
        int  mid = (tl + tr) / 2;
        if (tl <= l && r <= mid)
        {
            return k_th_null(l, r, k, n * 2, tl, mid);
        }
        else if(mid <= l && r <= tr)
        {
            return k_th_null(l, r, k, n * 2 + 1, mid, tr);
        }
        else if (mid >= l && mid <= r)
        {
            int h = sums(l, mid, n * 2, tl, mid);
            if (h >= k)
            {
                return k_th_null(l, mid, k, n * 2, tl, mid);
            }
            else
            {
                return k_th_null(mid, r, k - h, n * 2 + 1, mid, tr);
            }
        }
        else
        {
            return sizet - 2;
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
        return sums(l, r, n * 2, tl, mid) + sums(l, r, 2 * n + 1, mid, tr);
    }
    void change(int pos, int x, int n = 1, int tl = 0, int tr = sizet)
    {
        if (pos < tl || pos >= tr)
        {
            return;
        }
        if (tl + 1 == tr)
        {
            tree[n] = x;
            return;
        }
        int mid = (tl + tr) / 2;
        change(pos, x, 2 * n, tl, mid); change(pos, x, 2 * n + 1, mid, tr);
        tree[n] = tree[n * 2] + tree[n * 2 + 1];
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
        if (v[i] != 0)
        {
            v[i] = 0;
        }
        else
        {
            v[i] = 1;
        }
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
            cin >> a >> b; a--;
            if (b != 0)
            {
                v[a] = 0;
                x.change(a, 0);
            }
            else
            {
                v[a] = 1;
                x.change(a, 1);
            }
        }
        else
        {
            int a, b, k;
            cin >> a >> b >> k; a--;
            cout <<1 + x.k_th_null(a, b, k) - sizet << " ";
        }
    }

}

