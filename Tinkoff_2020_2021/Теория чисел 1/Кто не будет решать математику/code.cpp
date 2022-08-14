#include <bits/stdc++.h>

using namespace std;

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

const int MAXN = 300001;

int nol[MAXN], odi[MAXN], counted[MAXN], used[MAXN];

string s;

int kolvo(int l, int n, int print) {
    if (l == -1)
        return -1;
    if (used[l] && print == 0)
        return counted[l];
    int max_from_beg_to_0 = -1, min_from_beg_to_1 = l;
    for (int i = 0; i < n; i += l) {
        max_from_beg_to_0 = max(max_from_beg_to_0, nol[min(i + l - 1, n - 1)] - i);
        min_from_beg_to_1 = min(min_from_beg_to_1, odi[i] - i);
    }
    if (max_from_beg_to_0 >= min_from_beg_to_1)
        return -1;
    int ans = 0, kolvo_v_1 = l;
    if (max_from_beg_to_0 != -1)
        kolvo_v_1 = l - max_from_beg_to_0 - 1;
    ans += kolvo_v_1 * (n / l);
    if (max_from_beg_to_0 == -1)
        ans = n;
    else
        ans += max(0, n % l - max_from_beg_to_0 - 1);
    counted[l] = ans;
    used[l] = 1;
    if (print == 0)
        return ans;
    for (int i = 0; i < n; i += l) {
        int fin = min(n - i, l);
        for (int j = 0; j < fin; ++j)
            if (j <= max_from_beg_to_0)
                writeChar('0');
            else
                writeChar('1');
    }
    flush();
    return 2;
}

void solve() {
    cin >> s;
    if (s[0] == '1') {
        cout << "-1\n";
        return;
    }
    s[0] = '0';
    nol[0] = -1;
    if (s[0] == '0')
        nol[0] = 0;
    for (int i = 1; i < s.size(); ++i)
        if (s[i] == '0')
            nol[i] = i;
        else
            nol[i] = nol[i - 1];
    odi[s.size() - 1] = s.size() * 100;
    if (s.back() == '1')
        odi[s.size() - 1] = s.size() - 1;
    int BBBGGG = s.size();
    BBBGGG -= 2;
    for (int i = BBBGGG; i >= 0; --i)
        if (s[i] == '1')
            odi[i] = i;
        else
            odi[i] = odi[i + 1];
    int best_len = -1;
    for (int i = 1; i <= s.size(); ++i)
        if (kolvo(best_len, s.size(), 0) < kolvo(i, s.size(), 0))
            best_len = i;
    if (best_len == -1) {
        cout << "-1\n";
        return;
    }
    BBBGGG = kolvo(best_len, s.size(), 1);
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
