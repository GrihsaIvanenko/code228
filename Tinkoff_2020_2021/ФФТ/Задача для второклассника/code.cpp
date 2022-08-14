#include <bits/stdc++.h>

using namespace std;

const int K = 19;
const int MAXN = 1 << K;
const long double pi = atan2(0.0, -1.0);
vector<complex<long double>> roots(MAXN);
int to_swap[MAXN];


void precalc() {
    for (int i = 0; i < MAXN; ++i) {
        long double angle = ((pi + pi) * (long double)i) / (long double)MAXN;
        roots[i] = complex<long double>(cos(angle), sin(angle));
    }
    to_swap[0] = 0;
    for (int i = 1; i < MAXN; ++i)
        to_swap[i] = (to_swap[i >> 1] >> 1) | ((i & 1) << (K - 1));
}

void fft(vector<complex<long double>> & mas) {
    for (int i = 0; i < (int)mas.size(); ++i)
        if (i < to_swap[i])
            swap(mas[i], mas[to_swap[i]]);
    for (int level = 0; level < K; ++level) {
        for (int fpos = 0; fpos < MAXN; fpos += (1 << (level + 1))) {
            for (int i = 0; i < (1 << level); ++i) {
                complex<long double> A = mas[fpos + i], B = mas[fpos + i + (1 << level)] * roots[i * (1 << (K - level - 1))];
                mas[fpos + i] = A + B;
                mas[fpos + i + (1 << level)] = A - B;
            }
        }
    }
}

vector<long long> FFT(vector<complex<long double>> &M1, vector<complex<long double>> &M2, vector<long long> &v) {
    fft(M1);
    fft(M2);
    vector<complex<long double>> res(MAXN);
    for (int i = 0; i < MAXN; ++i)
        res[i] = M1[i] * M2[i];
    fft(res);
    reverse(res.begin() + 1, res.end());
    for (int i = 0; i < MAXN; ++i) {
        v[i] = round(res[i].real() / (long double)MAXN);
    }
    return v;
}

string mult(string &a, string &b) {
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    bool mins = false;
    if (a.back() == '-') {
        mins = !mins;
        a.pop_back();
    }
    if (b.back() == '-') {
        mins = !mins;
        b.pop_back();
    }
    vector<complex<long double>> firstm(MAXN), secondm(MAXN);
    for (int i = 0; i < (int)a.size(); ++i) {
        firstm[i] = complex<long double>(a[i] - '0', 0.0);
    }
    for (int i = a.size(); i < MAXN; ++i)
        firstm[i] = complex<long double>(0.0, 0.0);
    for (int i = 0; i < (int)b.size(); ++i)
        secondm[i] = complex<long double>(b[i] - '0', 0.0);
    for (int i = b.size(); i < MAXN; ++i)
        secondm[i] = complex<long double>(0.0, 0.0);
    vector<long long> v(MAXN);
    FFT(firstm, secondm, v);
    for (int i = 0; i < MAXN; ++i) {
        v[i + 1] += v[i] / 10;
        v[i] %= 10;
    }
    while (v.back() == 0)
        v.pop_back();
    reverse(v.begin(), v.end());
    string ans;
    if (mins && v.size() != 0)
        ans.push_back('-');
    if (v.size() == 0)
        ans.push_back('0');
    for (auto x : v)
        ans.push_back('0' + x);
    return ans;
}

int main() {
    precalc();
    string a, b;
    cin >> a >> b;
    string c = mult(a, b);
    cout << c << endl;
    return 0;
}
