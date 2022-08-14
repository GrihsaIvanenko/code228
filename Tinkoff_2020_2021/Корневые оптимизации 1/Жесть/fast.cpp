#include <bits/stdc++.h>

using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

template<typename T>
using vec = std::vector<T>;

const int BLOCK_SIZE = 1000;
const int STEP = 1688;

struct Block {
  bool rev = false;
  int agn = -1;
  int size = 0;
  int ordered[BLOCK_SIZE];
  pair<int, int> sorted[BLOCK_SIZE];
};

list<Block*> build(vec<int> &a) {
  list<Block*> ans;
  for (unsigned i = 0; i < a.size(); i++) {
    if (i % BLOCK_SIZE == 0) {
      if (i > 0) {
        sort(ans.back()->sorted, ans.back()->sorted + ans.back()->size);
      }
      ans.push_back(new Block);
      ans.back()->size = 0;
    }
    ans.back()->ordered[ans.back()->size++] = a[i];
    ans.back()->sorted[ans.back()->size - 1] = {a[i], i % BLOCK_SIZE};
  }
  sort(ans.back()->sorted, ans.back()->sorted + ans.back()->size);
  return ans;
}

void push(Block *t) {
  if (t->agn != -1) {
    t->rev = false;
    for (auto &x : t->ordered) {
      x = t->agn;
    }
    for (int i = 0; i < t->size; i++) {
      t->sorted[i].first = t->agn;
      t->sorted[i].second = i;
    }
    t->agn = -1;
  } else if (t->rev) {
    reverse(t->ordered, t->ordered + t->size);
    for (auto &[val, idx] : t->sorted) {
      idx = t->size - idx - 1;
    }
    t->rev = false;
  }
}

list<Block*> rebuild(list<Block*> &t, int n) {
  vec<int> a;
  a.reserve(n);
  for (auto it : t) {
    push(it);
    for (auto el : it->ordered) {
      a.push_back(el);
    }
    delete it;
  }
  return build(a);
}



pair<Block*, Block*> split(Block *t, int size) {
  push(t);
  auto *t1 = new Block, *t2 = new Block;
  for (int i = 0; i < t->size; i++) {
    auto [val, idx] = t->sorted[i];
    if (idx < size) {
      t1->sorted[t1->size++] = {val, idx};
    } else {
      t2->sorted[t2->size++] = {val, idx - size};
    }
  }
  for (int i = 0; i < t->size; i++) {
    if (i < size) {
      t1->ordered[i] = (t->ordered[i]);
    } else {
      t2->ordered[i] = (t->ordered[i]);
    }
  }
  return {t1, t2};
}

int get(Block *t, int x) {
    if (t->agn != -1) {
        if (t->agn >= x)
        return t->size;
        else
        return 0;
    }
  return t->size - (lower_bound(t->sorted, t->sorted + t->size, pair<int, int>{x, -1}) - t->sorted);
}

Block *merge(Block *t1, Block *t2) {
    Block *t = new Block;
    push(t1);
    push(t2);
    for (int i = 0; i < t1->size; i++) {
        int x = t1->ordered[i];
        t->ordered[t->size++] = (x);
    }
    for (int i = 0; i < t2->size; i++) {
        int x = t2->ordered[i];
        t->ordered[t->size++] = (x);
    }
    for (auto &[val, idx] : t2->sorted) {
        idx += t1->size;
    }
    merge(t1->sorted, t1->sorted + t1->size, t2->sorted, t2->sorted + t2->size, t->sorted);
    delete t1;
    delete t2;
    return t;
}

list<Block*>::iterator split(list<Block*> &t, list<Block*>::iterator iter, int p) {
    while (p > (*iter)->size) {
        while (next(iter) != t.end() && (*iter)->size + (*next(iter))->size <= BLOCK_SIZE && (*iter)->size+ (*next(iter))->size <= p) {
            *iter = merge(*iter, *next(iter));
            t.erase(next(iter));
        }
        if (p == ((*iter)->size)) break;
        p -= (*iter)->size;
        ++iter;
    }
    if (p == (*iter)->size) {
        return next(iter);
    }
    auto [t1, t2] = split(*iter, p);
    delete *iter;
    *iter = t1;
    t.insert(next(iter), t2);
    return next(iter);
}

void solve() {
    int n;
    cin >> n;
    vec<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    list<Block*> t = build(a);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        string query;
        cin >> query;
        if (query[0] == 'g') {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            list<Block*>::iterator bg, nd;
            if (l > 0) {
                bg = split(t, t.begin(), l);
            } else {
                bg = t.begin();
            }
            nd = split(t, bg, r - l);
            int ans = 0;
            while (bg != nd) {
                ans += get(*bg, x);
                bg++;
            }
            cout << ans << '\n';
        } else if (query[0] == 's') {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            list<Block*>::iterator bg, nd;
            if (l > 0)
                bg = split(t, t.begin(), l);
            else
                bg = t.begin();
            nd = split(t, bg, r - l);
            while (bg != nd) {
                (*bg)->agn = x;
                bg++;
            }
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            list<Block*>::iterator bg, nd;
            if (l > 0) {
                bg = split(t, t.begin(), l);
            } else {
                bg = t.begin();
            }
            nd = split(t, bg, r - l);
            auto bgg = bg;
            while (bg != nd) {
                (*bg)->rev ^= true;
                bg++;
            }
            reverse(bgg, nd);
        }
    }
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    while (t--)
        solve();
  return 0;
}

