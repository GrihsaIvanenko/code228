#include <bits/stdc++.h>

using namespace std;

const int MAXN = 42;

int main() {
    long long n;
    cin >> n;
    long long dp[MAXN][10][10];
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < 10; ++j)
            for (int k = 0; k < 10; ++k)
                dp[i][j][k] = 0;
    for (int i = 1; i < 10; ++i)
        dp[1][i][i] = 1;
    for (int i = 2; i < MAXN; ++i)
        for (int j = 0; j < 10; ++j)
            for (int k = 0; k < 10; ++k)
                for (int l = 0; l <= k; ++l)
                    dp[i][j][k] += dp[i - 1][j][l];
    long long sum = 0;
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < 10; ++j)
            for (int k = 0; k < 10; ++k)
                sum += dp[i][j][k];
    int good_id = 1;
    long long N = n;
    while (N > 0) {
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                N -= dp[good_id][i][j];
        if (N > 0)
            ++good_id;
    }
    for (int iter = 1; iter < good_id; ++iter) {
            for (int i = 0; i < 10; ++i)
                for (int j = 0; j < 10; ++j)
                    n -= dp[iter][i][j];
    }
    //cout << good_id << " " << n << endl;
    int last = 0;
    for (int iter = 0; iter < good_id; ++iter) {
        int firid = last;
        long long N = n;
        while (N > 0) {
            for (int i = 0; i < 10; ++i)
                N -= dp[good_id - iter][firid][i];
            //cout << N << "F" << endl;
            if (N > 0) {
                for (int i = 0; i < 10; ++i)
                    n -= dp[good_id - iter][firid][i];
                ++firid;
            }
        }
        cout << firid;
        last = firid;
    }
    cout << '\n';
    return 0;
}
