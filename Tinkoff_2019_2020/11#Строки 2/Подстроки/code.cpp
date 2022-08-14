#include <bits/stdc++.h>

using namespace std;

const long long P = 29, MOD = 1e9, MAXN = 10001;

long long p[MAXN];
vector<vector<long long>> hashs;
vector<vector<int>> suffs;
vector<string> mem;

vector<int> suffix_array(string &s) {
    vector<vector<int>> count_sort(P);
    vector<int> cls(s.size() + 1);
    for (int i = 0; i < (int)s.size(); ++i) {
        count_sort[s[i] - 'a' + 1].push_back(i);
        cls[i] = (s[i] - 'a' + 1);
    }
    vector<int> now_ans(cls.size());
    now_ans[0] = s.size();
    int poss = 1;
    for (int i = 1; i < P; ++i) {
        for (auto x : count_sort[i])
            now_ans[poss++] = x;
    }
    int timer = 0;
    s.push_back('$');
    for (int i = 1; i < (int)now_ans.size(); ++i) {
        if (s[now_ans[i - 1]] != s[now_ans[i]])
            ++timer;
        cls[now_ans[i]] = timer;
    }
    count_sort.clear();
    count_sort.shrink_to_fit();
    vector<int> new_cls(s.size()), kolvo(s.size()), new_ans(s.size());
    int len = 1;
    while (len < (int)s.size()) {
        kolvo.assign(s.size(), 0);
        for (int i = 0; i < (int)s.size(); ++i)
            ++kolvo[cls[i]];
        for (int i = 1; i < (int)kolvo.size(); ++i) {
            kolvo[i] += kolvo[i - 1];
        }
       for (int pos = (int)s.size() - 1; pos >= 0; --pos) {
            int now = now_ans[pos];
            int my_good = now - len;
            while (my_good < 0)
                my_good += (int)s.size();
            new_ans[--(kolvo[cls[my_good]])] = my_good;
        }
        timer = 0;
        pair<int, int> last;
        for (int i = 0; i < (int)s.size(); ++i) {
            int pss = new_ans[i];
            int mt = pss + len;
            while (mt >= (int)s.size())
                mt -= (int)s.size();
            if (i == 0) {
                last = {cls[pss], cls[mt]};
            } else {
                if (last.first != cls[pss] || last.second != cls[mt]) {
                    ++timer;
                    last = {cls[pss], cls[mt]};
                }
            }
            new_cls[pss] = timer;
        }
        swap(cls, new_cls);
        swap(new_ans, now_ans);
        len += len;
    }
    s.pop_back();
    for (int i = 1; i < (int)now_ans.size(); ++i)
        now_ans[i - 1] = now_ans[i];
    now_ans.pop_back();
    return now_ans;
}

int get_hash(int pos, int lb, int rb) {
    return (hashs[pos][rb] + (MOD - hashs[pos][lb]) * p[rb - lb]) % MOD;
}

int main() {
    p[0] = 1;
    for (int i = 1; i < MAXN; ++i)
        p[i] = (p[i - 1] * P) % MOD;
    //freopen("input.txt", "r", stdin);
    int k;
    cin >> k;
    hashs.resize(k);
    suffs.resize(k);
    mem.resize(k);
    for (int i = 0; i < k; ++i) {
        string s;
        cin >> s;
        mem[i] = s;
        hashs[i].resize(s.size() + 1);
        for (int j = 1; j <= (int)s.size(); ++j) {
            hashs[i][j] = (hashs[i][j - 1] * P + (s[j - 1] - 'a' + 1)) % MOD;
        }
        suffs[i] = suffix_array(s);
        mem[i].push_back('$');
    }
    if (k == 1) {
        mem[0].pop_back();
       cout << mem[0] << endl;
        return 0;
    }
    vector<int> uks(k);
    int pos_ans = -1, good_len = 0;
    while (true) {
        int lb = -1, rb = MAXN;
        for (int i = 0; i < k; ++i) {
            rb = min(rb, (int)mem[i].size() - suffs[i][uks[i]]);
        }
        while (rb - lb > 1) {
            int mid = (lb + rb) >> 1;
            bool podoshlo = true;
            int obr = get_hash(0, suffs[0][uks[0]], suffs[0][uks[0]] + mid);
            for (int i = 1; i < k; ++i) {
                if (get_hash(i, suffs[i][uks[i]], suffs[i][uks[i]] + mid) != obr)
                   podoshlo = false;
            }
            if (podoshlo)
                lb = mid;
            else
                rb = mid;
        }
        if (lb > good_len) {
            good_len = lb;
            pos_ans = suffs[0][uks[0]];
        }
        int pos_min = 0;
        for (int i = 1; i < k; ++i) {
            if (mem[pos_min][suffs[pos_min][uks[pos_min]] + lb] > mem[i][suffs[i][uks[i]] + lb])
                pos_min = i;
        }
        ++uks[pos_min];
        if (uks[pos_min] == (int)mem[pos_min].size() - 1)
            break;
    }
    for (int i = pos_ans; i < pos_ans + good_len; ++i)
        cout << mem[0][i];
    cout << '\n';
    return 0;
}
