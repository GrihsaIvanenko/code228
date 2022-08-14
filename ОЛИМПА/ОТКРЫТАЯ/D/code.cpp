#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1001000, MAXC = 20;

int sorted[MAXN], nakop[3][MAXN], cnt_nakop[3], suf_mas_timer = 1, pos_in_sufmas[MAXN];
int my_class[MAXN], new_cls[MAXN], cnt_by_class[MAXN], new_sorted[MAXN], m;
char s[MAXN];


void sufmas() {
    for (int i = 0; i < m; ++i) {
        nakop[s[i] - 'a'][cnt_nakop[s[i] - 'a']++] = i;
        my_class[i] = s[i] - 'a' + 1;
    }
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < cnt_nakop[i]; ++j)
            sorted[suf_mas_timer++] = nakop[i][j];
    sorted[0] = m++;
    int len = 1, vsego = 30;
    while (len < m) {
        memset(cnt_by_class, 0, sizeof(cnt_by_class));
        for (int i = 0; i < m; ++i)
            ++cnt_by_class[my_class[i]];
        for (int i = 1; i < vsego; ++i)
            cnt_by_class[i] += cnt_by_class[i - 1];
        for (int i = m - 1; i >= 0; --i) {
            int me = sorted[i];
            int mt = me - len;
            while (mt < 0)
                mt += m;
            new_sorted[--cnt_by_class[my_class[mt]]] = mt;
        }
        vsego = -1;
        long long prev = -1;
        for (int i = 0; i < m; ++i) {
            int me = new_sorted[i];
            int mt = me + len;
            while (mt >= m)
                mt -= m;
            long long nw = (long long)my_class[me] * m + my_class[mt];
            vsego += (nw != prev);
            prev = nw;
            new_cls[me] = vsego;
        }
        ++vsego;
        len += len;
        swap(new_cls, my_class);
        swap(new_sorted, sorted);
    }
    for (int i = 1; i < m; ++i)
        sorted[i - 1] = sorted[i];
    --m;
    for (int i = 0; i < m; ++i)
        pos_in_sufmas[sorted[i]] = i;
}

long long pw[MAXN], hesh[MAXN];

constexpr long long MOD = 1e9 + 9, P = 5;

void calc_heshi() {
    pw[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        hesh[i] = (hesh[i - 1] * P + (s[i - 1] - 'a' + 1)) % MOD;
        pw[i] = (pw[i - 1] * P) % MOD;
    }
}

char kriv_in_me[MAXN], in_me[MAXN];

vector<int> kriv_g[MAXN], g[MAXN];

int time_in[MAXN], timer_euler = 0;

void dfs_euler(int v, int p = -1) {
    time_in[v] = timer_euler++;
    for (auto x : kriv_g[v])
        if (x != p)
            dfs_euler(x, v);
}

int go[MAXN][3], timer = 0, prior[MAXN], anc[MAXN][MAXC], deep_d[MAXN], sz[MAXN];

long long hesh_up[MAXN], hesh_down[MAXN];

int dfs_find_my_cen(int v, int level, int C, int p = -1) {
    for (auto x : g[v])
        if (x != p && prior[x] < level && sz[x] + sz[x] > C)
            return dfs_find_my_cen(x, level, C, v);
    return v;
}

void dfs_cen(int v, int level, int p = -1) {
    sz[v] = 1;
    for (auto x : g[v])
        if (x != p && prior[x] < level) {
            dfs_cen(x, level, v);
            sz[v] += sz[x];
        }
}

long long get_hash(int l, int r) {
    return (hesh[r] + (MOD - hesh[l]) * pw[r - l]) % MOD;
}

int cnt_ravn[MAXN], pos_first[MAXN], timer_pos = 0, cnt_les[MAXN], timer_les = 0;

int comp(int versh, int pos_st) {
    if (in_me[versh] != s[pos_st]) {
        if (in_me[versh] < s[pos_st])
            return -1;
        return 1;
    }
    int vcopy = versh;
    for (int i = MAXC - 1; i >= 0; --i)
        if (anc[vcopy][i] != -1)
            if (deep_d[versh] - deep_d[anc[vcopy][i]] <= m - pos_st)
                if ((get_hash(pos_st, pos_st + deep_d[versh] - deep_d[anc[vcopy][i]]) * pw[deep_d[anc[vcopy][i]] + 1]) % MOD ==
                    (hesh_down[versh] + (MOD - hesh_down[anc[vcopy][i]])) % MOD)
                        vcopy = anc[vcopy][i];
    if (pos_st + deep_d[versh] - deep_d[vcopy] == m)
        return 1;
    assert(in_me[vcopy] != s[pos_st + deep_d[versh] - deep_d[vcopy]]);
    if (in_me[vcopy] < s[pos_st + deep_d[versh] - deep_d[vcopy]])
        return -1;
    return 1;
}

int bors[MAXN], order_path[MAXN], timer_bor = 0, cnt_ravn_all[MAXN];

void dfs_part(int level, int v, int p, int deep, long long hesh_up_p, long long hesh_down_p, int order_child) {
    order_path[timer_bor] = order_child;
    bors[timer_bor++] = v;
    anc[v][0] = p;
    for (int i = 1; i < MAXC; ++i)
        if (anc[v][i - 1] != -1)
            anc[v][i] = anc[anc[v][i - 1]][i - 1];
        else
            anc[v][i] = -1;
    deep_d[v] = deep;
    hesh_up_p = (hesh_up_p * P + (in_me[v] - 'a' + 1)) % MOD;
    hesh_down_p = (hesh_down_p + pw[deep] * (in_me[v] - 'a' + 1)) % MOD;
    hesh_up[v] = hesh_up_p;
    hesh_down[v] = hesh_down_p;
    if (deep_d[v] + 1 <= m && get_hash(0, deep + 1) == hesh_down_p) {
        ++cnt_ravn_all[deep - 1];
        ++cnt_ravn[deep - 1 + pos_first[timer_pos]];
    } else if (comp(v, 0) == -1)
        ++cnt_les[timer_les];
    for (auto x : g[v])
        if (x != p && prior[x] < level && in_me[x] == 'a')
            dfs_part(level, x, v, deep + 1, hesh_up_p, hesh_down_p, order_child);
    for (auto x : g[v])
        if (x != p && prior[x] < level && in_me[x] == 'b')
            dfs_part(level, x, v, deep + 1, hesh_up_p, hesh_down_p, order_child);
    for (auto x : g[v])
        if (x != p && prior[x] < level && in_me[x] == 'c')
            dfs_part(level, x, v, deep + 1, hesh_up_p, hesh_down_p, order_child);
}

long long ans = 0;

char has_this_len[MAXN];

int KOLVO_DLIN = 0, suffixes[MAXN], mensh[MAXN];

bool cmp(int a, int b) {
    return pos_in_sufmas[a] < pos_in_sufmas[b];
}

void solver(int v) {
    hesh_up[v] = hesh_down[v] = in_me[v] - 'a' + 1;
    for (int i = 0; i < MAXC; ++i)
        anc[v][i] = -1;
    deep_d[v] = 0;
    int before = 0;
    int HAHAHA = 0;
    for (auto x : g[v]) {
        if (prior[x] < prior[v] && in_me[x] == 'a') {
            dfs_part(prior[v], x, v, 1, in_me[v] - 'a' + 1, in_me[v] - 'a' + 1, HAHAHA);
            timer_les++;
            before += sz[x];
            pos_first[++timer_pos] = before;
        }
        if (prior[x] < prior[v])
            ++HAHAHA;
    }
    HAHAHA = 0;
    for (auto x : g[v]) {
        if (prior[x] < prior[v] && in_me[x] == 'b') {
            dfs_part(prior[v], x, v, 1, in_me[v] - 'a' + 1, in_me[v] - 'a' + 1, HAHAHA);
            timer_les++;
            before += sz[x];
            pos_first[++timer_pos] = before;
        }
        if (prior[x] < prior[v])
            ++HAHAHA;
    }
    HAHAHA = 0;
    for (auto x : g[v]) {
        if (prior[x] < prior[v] && in_me[x] == 'c') {
            dfs_part(prior[v], x, v, 1, in_me[v] - 'a' + 1, in_me[v] - 'a' + 1, HAHAHA);
            timer_les++;
            before += sz[x];
            pos_first[++timer_pos] = before;
        }
        if (prior[x] < prior[v])
            ++HAHAHA;
    }
    /*for (int i = 0; i < timer_pos; ++i) {
        for (int j = pos_first[i]; j < pos_first[i + 1]; ++j) {
            cout << cnt_ravn[j] << " cnt_ravn ";
        }
        cout << endl;
    }*/
    for (int i = 0; i < timer_les; ++i)
        ans += (long long)(sz[v] - sz[g[v][i]]) * cnt_les[i];
    if (in_me[0] < s[0])
        ans += sz[v];
    for (int i = 0; i < timer_pos; ++i)
        for (int j = pos_first[i]; j < pos_first[i + 1]; ++j)
            if (cnt_ravn[j]) {
                if (has_this_len[j - pos_first[i] + 1] == 0)
                    suffixes[KOLVO_DLIN++] = j - pos_first[i] + 1;
                has_this_len[j - pos_first[i] + 1] = 1;
            }
    /*for (int i = 0; i < KOLVO_DLIN; ++i)
        cout << suffixes[i] << " suf_bef_sor ";
    cout << endl;*/
    sort(suffixes, suffixes + KOLVO_DLIN, cmp);
    /*for (int i = 0; i < KOLVO_DLIN; ++i)
        cout << suffixes[i] << " suf_aft_sor ";
    cout << endl;
    for (int i = 0; i < timer_bor; ++i)
        cout << bors[i] << " " << order_path[i] << "; ";
    cout << endl;*/
    int uk_suf = 0, uk_bor = 0;
    while (uk_suf < KOLVO_DLIN || uk_bor < timer_bor) {
        int suf_fe = 0, bor_re = 0;
        if (uk_suf == KOLVO_DLIN)
            bor_re = 1;
        if (uk_bor == timer_bor)
            uk_suf = 1;
        if (!uk_bor && !uk_suf) {
            int res = comp_down(bors[uk_bor], suffixes[uk_suf]);
            if (res == 1)
        }
    }
    for (int i = 0; i < timer_pos; ++i)
        for (int j = pos_first[i]; j < pos_first[i + 1]; ++j)
            if (cnt_ravn[j])
                has_this_len[j - pos_first[i] + 1] = 0;
    KOLVO_DLIN = 0;
    timer_bor = 0;
    for (int i = 0; i < sz[v]; ++i)
        cnt_ravn_all[i] = cnt_les[i] = cnt_ravn[i] = pos_first[i] = 0;
    timer_pos = 0;
    timer_les = 0;
}

void build(int v = 0, int level = 30) {
    dfs_cen(v, level);
    int C = sz[v];
    int nw_v = dfs_find_my_cen(v, level, C);
    prior[nw_v] = level;
    dfs_cen(nw_v, level);
    solver(nw_v);
    /*for (auto x : g[nw_v])
        if (prior[x] < level)
            build(x, level - 1);
            */
}

void solve() {
    int n;
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
        cin >> s[i];
    sufmas();
    calc_heshi();
    for (int i = 0; i < n; ++i)
        cin >> kriv_in_me[i];
    int tmp;
    for (int i = 1; i < n; ++i) {
        cin >> tmp;
        --tmp;
        kriv_g[i].push_back(tmp);
        kriv_g[tmp].push_back(i);
    }
    dfs_euler(0);
    for (int i = 0; i < n; ++i) {
        g[time_in[i]] = kriv_g[i];
        for (int j = 0; j < g[time_in[i]].size(); ++j)
            g[time_in[i]][j] = time_in[kriv_g[i][j]];
        in_me[time_in[i]] = kriv_in_me[i];
    }
    /*for (int i = 0; i < n; ++i) {
        cout << i << " " << in_me[i] << ": ";
        for (auto x : g[i])
            cout << x << " g ";
        cout << endl;
    }*/
    build();
    cout << ans << '\n';
}

int main() {
    freopen("t.cpp", "r", stdin);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
