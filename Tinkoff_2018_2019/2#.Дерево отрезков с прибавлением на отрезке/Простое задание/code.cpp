#include <bits/stdc++.h>

using namespace std;

const int MAXL = 26;

struct segtree{
    int lb, mid, rb, sorted;
    vector<int> letters;
    segtree *l = nullptr, *r = nullptr, *dad = nullptr;
    segtree(int lb_, int rb_, string &s) {
        lb = lb_;
        rb = rb_;
        mid = (lb + rb) >> 1;
        sorted = 0;
        letters.resize(MAXL);
        for (int i = lb; i < rb; ++i) {
            ++letters[s[i] - 'a'];
        }
        if (lb + 1 != rb) {
           l = new segtree(lb, mid, s);
           l->dad = this;
           r = new segtree(mid, rb, s);
           r->dad = this;
        }
    }
};

void push(segtree *root) {
    if (root->lb + 1 == root->rb || root->sorted == 0) {
       return;
    }
    root->l->letters.assign(MAXL, 0);
    root->r->letters.assign(MAXL, 0);
    if (root->sorted == -1) {
        int MAX = root->r->rb - root->r->lb;
        for(int i = 0; i < MAXL; ++i) {
            if (MAX >= root->letters[i]) {
                root->r->letters[i] = root->letters[i];
                MAX -= root->letters[i];
            } else {
                root->r->letters[i] = MAX;
                root->l->letters[i] = root->letters[i] - MAX;
                MAX = 0;
            }
        }
    } else {
        int MAX = root->l->rb - root->l->lb;
        for(int i = 0; i < MAXL; ++i) {
            if (MAX >= root->letters[i]) {
                root->l->letters[i] = root->letters[i];
                MAX -= root->letters[i];
            } else {
                root->l->letters[i] = MAX;
                root->r->letters[i] = root->letters[i] - MAX;
                MAX = 0;
            }
        }
    }
    root->l->sorted = root->sorted;
    root->r->sorted = root->sorted;
}


void update(segtree *root) {
    bool ch = root->sorted != 0;
    while (root->dad) {
        root = root->dad;
        if (ch) {
            root->sorted = 0;
        }
        if (root->lb + 1 != root->rb) {
            for (int i = 0; i < MAXL; ++i) {
                root->letters[i] = root->l->letters[i] + root->r->letters[i];
            }
        }
    }
}

vector<segtree*> cash;

void down(segtree *root, int le, int re) {
    if (root->rb <= le || root->lb >= re) {
       return;
    }
    if (le <= root->lb && root->rb <= re) {
       cash.push_back(root);
       return;
    }
    push(root);
    down(root->l, le, re);
    down(root->r, le, re);
}

void sort_(segtree *root, int le, int re, int good) {
    cash.resize(0);
    down(root, le, re);
    vector<int> res_letters(MAXL);
    for (int i = 0; i < cash.size(); ++i) {
        for (int j = 0; j < MAXL; ++j) {
                res_letters[j] += cash[i]->letters[j];
        }
        cash[i]->letters.assign(MAXL, 0);
    }
    int it;
    if (good == 1) {
       it = 0;
    } else {
        it = MAXL - 1;
    }
    for (int i = 0; i < cash.size(); ++i) {
        int MAX = cash[i]->rb - cash[i]->lb;
        while (MAX > 0) {
            if (MAX > res_letters[it]) {
               cash[i]->letters[it] = res_letters[it];
               MAX -= res_letters[it];
               it += good;
            } else {
                cash[i]->letters[it] = MAX;
                res_letters[it] -= MAX;
                MAX = 0;
            }
        }
        cash[i]->sorted = good;
        update(cash[i]);
    }
}

void print_ans(segtree *root) {
    if (root->lb + 1 == root->rb) {
       for (int i = 0; i < MAXL; ++i) {
            if (root->letters[i] != 0) {
               cout << char('a' + i);
               return;
            }
       }
       cout << 1 / 0 << endl;
    }
    push(root);
    print_ans(root->l);
    print_ans(root->r);
}

int main() {
    int n, m;
    string s;
    cin >> n >> m >> s;
    segtree *root = new segtree(0, n, s);
    for (int i = 0; i < m; ++i) {
        int a, b, k;
        cin >> a >> b >> k;
        --a;
        if(k == 0) {
            --k;
        }
        sort_(root, a, b, k);
    }
    print_ans(root);
    return 0;
}
