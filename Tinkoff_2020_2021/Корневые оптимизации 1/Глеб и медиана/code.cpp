#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,tune=native")
#pragma GCC optimize("fast-math")
#pragma warning(disable:4996)


template <class T = int> inline T readInt();
inline double readDouble();
inline int readUInt();
inline int readChar();
inline void readWord(char *s);
inline bool readLine(char *s);
inline bool isEof();
inline int peekChar();
inline bool seekEof();

template <class T> inline void writeInt(T x, int len = -1);
template <class T> inline void writeUInt(T x, int len = -1);
inline void writeChar(int x);
inline void writeWord(const char *s);
inline void writeDouble(double x, int len = 0);
inline void flush();

/** Read */

static const int buf_size = 4096;

static char buf[buf_size];
static int buf_len = 0, buf_pos = 0;

inline bool isEof() {
    if (buf_pos == buf_len) {
        buf_pos = 0, buf_len = fread(buf, 1, buf_size, stdin);
        if (buf_pos == buf_len)
            return 1;
    }
    return 0;
}

inline int getChar() {
    return isEof() ? -1 : buf[buf_pos++];
}

inline int peekChar() {
    return isEof() ? -1 : buf[buf_pos];
}

inline bool seekEof() {
    int c;
    while ((c = peekChar()) != -1 && c <= 32)
        buf_pos++;
    return c == -1;
}

inline int readChar() {
    int c = getChar();
    while (c != -1 && c <= 32)
        c = getChar();
    return c;
}

inline int readUInt() {
    int c = readChar(), x = 0;
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return x;
}

template <class T>
inline T readInt() {
    int s = 1, c = readChar();
    T x = 0;
    if (c == '-')
        s = -1, c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}

inline double readDouble() {
    int s = 1, c = readChar();
    double x = 0;
    if (c == '-')
        s = -1, c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    if (c == '.') {
        c = getChar();
        double coef = 1;
        while ('0' <= c && c <= '9')
            x += (c - '0') * (coef *= 1e-1), c = getChar();
    }
    return s == 1 ? x : -x;
}

inline void readWord(char *s) {
    int c = readChar();
    while (c > 32)
        *s++ = c, c = getChar();
    *s = 0;
}

inline bool readLine(char *s) {
    int c = getChar();
    while (c != '\n' && c != -1)
        *s++ = c, c = getChar();
    *s = 0;
    return c != -1;
}

/** Write */

static int write_buf_pos = 0;
static char write_buf[buf_size];

inline void writeChar(int x) {
    if (write_buf_pos == buf_size)
        fwrite(write_buf, 1, buf_size, stdout), write_buf_pos = 0;
    write_buf[write_buf_pos++] = x;
}

inline void flush() {
    if (write_buf_pos)
        fwrite(write_buf, 1, write_buf_pos, stdout), write_buf_pos = 0;
}

template <class T>
inline void writeInt(T x, int output_len) {
    if (x < 0)
        writeChar('-'), x = -x;
    char s[24];
    int n = 0;
    while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
    while (n < output_len)
        s[n++] = '0';
    while (n--)
        writeChar(s[n]);
}

template <class T>
inline void writeUInt(T x, int output_len) {
    char s[24];
    int n = 0;
    while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
    while (n < output_len)
        s[n++] = '0';
    while (n--)
        writeChar(s[n]);
}

inline void writeWord(const char *s) {
    while (*s)
        writeChar(*s++);
}

inline void writeDouble(double x, int output_len) {
    if (x < 0)
        writeChar('-'), x = -x;
    int t = (int)x;
    writeUInt(t), x -= t;
    writeChar('.');
    for (int i = output_len - 1; i > 0; i--) {
        x *= 10;
        t = std::min(9, (int)x);
        writeChar('0' + t), x -= t;
    }
    x *= 10;
    t = std::min(9, (int)(x + 0.5));
    writeChar('0' + t);
}

const int MAXN = 200000, SZ = 6000;

const int MAXM = (MAXN + SZ - 1) / SZ + 2;

int val[MAXN];

vector<pair<int, int>> vals[MAXM];

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n = readInt();
    int p1 = 0, p2 = 0;
    for (int i = 0; i < n; ++i) {
        if (p2 == 0)
            vals[p1].resize(min(SZ, n - i));
        val[i] = readInt();
        vals[p1][p2] = {val[i], i};
        ++p2;
        if (p2 == SZ) {
            ++p1;
            p2 = 0;
        }
    }
    for (int i = 0; i < p1 + 1; ++i)
        sort(vals[i].begin(), vals[i].end());
    int q = readInt();
    for (int w = 0; w < q; ++w) {
        int t = readInt();
        if (t == 1) {
            int p, x;
            p = readInt();
            x = readInt();
            --p;
            int id = p / SZ;
            vals[id].erase(lower_bound(vals[id].begin(), vals[id].end(), make_pair(val[p], p)));
            val[p] = x;
            vals[id].insert(lower_bound(vals[id].begin(), vals[id].end(), make_pair(val[p], p)), {val[p], p});
        } else {
            int m, l, r, answ = 0;
            m = readInt();
            l = readInt();
            r = readInt();
            --l;
            --r;
            if (l / SZ == r / SZ) {
                int id = l / SZ, fin = lower_bound(vals[id].begin(), vals[id].end(), make_pair(m, -1)) - vals[id].begin();
                for (int i = 0; i < fin; ++i)
                    if (l <= vals[id][i].second && vals[id][i].second <= r)
                        ++answ;
            } else {
                int id = l / SZ;
                int fin = lower_bound(vals[id].begin(), vals[id].end(), make_pair(m, -1)) - vals[id].begin();
                for (unsigned i = 0; i < fin; ++i)
                    if (l <= vals[id][i].second && vals[id][i].second <= r)
                        ++answ;
                int id1 = r / SZ;
                int fin1 = lower_bound(vals[id1].begin(), vals[id1].end(), make_pair(m, -1)) - vals[id1].begin();
                for (int i = 0; i < fin1; ++i)
                    if (l <= vals[id1][i].second && vals[id1][i].second <= r)
                        ++answ;
                for (int i = id + 1; i < id1; ++i)
                    answ += lower_bound(vals[i].begin(), vals[i].end(), make_pair(m, -1)) - vals[i].begin();
            }
            writeInt(max(0, r - l + 1 - answ - answ));
            writeChar('\n');
        }
    }
    flush();
    return 0;
}
