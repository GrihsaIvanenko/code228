#include <bits/stdc++.h>

using namespace std;

int sizet = 1;

struct Tree1
{
    vector<pair<int,int>> tree;
    Tree1( vector<pair<int,int>> & v)
    {
        sizet = 1;
        while(sizet < v.size())
            sizet *= 2;
        tree.resize(2 * sizet);
        for(int i = 0; i < 2 * sizet; ++i)
        {
            tree[i] = {0,0};
        }
    }
    int change1(int a, int b)
    {
        int num = a + sizet - 1;
        if(b == 1)
        {
            tree[num].first = 1;
        }
        else
        {
            tree[num].second = 1;
        }
        num /= 2;
        while(num >= 1)
        {
            //cout << num << endl;
            bool may = true;
            if(tree[num * 2].first == 0 && tree[num * 2].second == 0)
            {
                tree[num] = tree[num * 2 + 1];
                may = false;
            }
            if(tree[num * 2 + 1].first == 0 && tree[num * 2 + 1].second == 0 && may)
            {
                tree[num] = tree[num * 2];

                may = false;
            }
            if(may)
            {
                /*int x = tree[num * 2].first - tree[num * 2 + 1].second;

                tree[num] = {0, 0};
                if(x >= 0){
                    //cout << x << "sdij";
                    tree[num].second = x;
                }
                else{
                    //tree[num].first += x;
                }
                tree[num].first += tree[num * 2 + 1].first;
                tree[num].second += tree[num * 2].second;*/
                if(tree[num * 2].first >= tree[num * 2 + 1].second)
                {
                    tree[num].first = tree[num * 2 + 1].first + tree[num * 2].first - tree[num * 2 + 1].second;
                    tree[num].second = tree[num * 2].second;
                }
                else
                {
                    tree[num].first = tree[num * 2 + 1].first;
                    tree[num].second = tree[num * 2].second + tree[num * 2 + 1].second - tree[num * 2].first;
                }
            }

            num /= 2;
        }
        /*for(int i = 0; i < tree.size(); ++i)
        {
            cout << tree[i].first << " " << tree[i].second << endl;
        }*/
        return tree[1].first;
    }

};
struct Tree2
{
    vector<pair<int,int>> tree;
    Tree2( vector<pair<int,int>> & v)
    {
        sizet = 1;
        while(sizet < v.size())
            sizet *= 2;
        tree.resize(2 * sizet);
        for(int i = 0; i < 2 * sizet; ++i)
        {
            tree[i] = {0,0};
        }
    }
    int change2(int a, int b)
    {
        int num = a + sizet - 1;
        if(b == 2)
        {
            tree[num].first = 1;
        }
        else
        {
            tree[num].second = 1;
        }
        num /= 2;
        while(num >= 1)
        {
            //cout << num << endl;
            bool may = true;
            if(tree[num * 2].first == 0 && tree[num * 2].second == 0)
            {
                tree[num] = tree[num * 2 + 1];
                may = false;
            }
            if(tree[num * 2 + 1].first == 0 && tree[num * 2 + 1].second == 0 && may)
            {
                tree[num] = tree[num * 2];

                may = false;
            }
            if(may)
            {
                /*int x = tree[num * 2].first - tree[num * 2 + 1].second;

                tree[num] = {0, 0};
                if(x >= 0){
                    //cout << x << "sdij";
                    tree[num].second = x;
                }
                else{
                    //tree[num].first += x;
                }
                tree[num].first += tree[num * 2 + 1].first;
                tree[num].second += tree[num * 2].second;*/
                if(tree[num * 2].first >= tree[num * 2 + 1].second)
                {
                    tree[num].first = tree[num * 2 + 1].first + tree[num * 2].first - tree[num * 2 + 1].second;
                    tree[num].second = tree[num * 2].second;
                }
                else
                {
                    tree[num].first = tree[num * 2 + 1].first;
                    tree[num].second = tree[num * 2].second + tree[num * 2 + 1].second - tree[num * 2].first;
                }
            }

            num /= 2;
        }
        /*for(int i = 0; i < tree.size(); ++i)
        {
            cout << tree[i].first << " " << tree[i].second << endl;
        }*/
        return tree[1].first;
    }

};

int main()
{
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);
    Tree1 x = Tree1(v);
    Tree2 y = Tree2(v);
    for(int i = 0; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;
        int c, d;
        c = x.change1(a, b);
        d = y.change2(a, b);
        // cout << c << " " << d << endl;
        if(c * d > 0)
        {
            cout << '?' << endl;
        }
        else
        {
            if(c > 0)
            {
                cout << '>' << endl;
            }
            else
            {
                cout << '<' << endl;
            }
        }

    }
    return 0;
}




