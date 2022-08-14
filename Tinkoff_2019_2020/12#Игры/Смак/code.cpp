#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    if (n == 1 || n == 3) {
        cout << "Ivan Urgant\nDraw\n";
        return 0;
    }
    if (n == 2) {
        cout << "Ivan Safonov\n";
        return 0;
    }
    if (n == 4) {
        cout << "Ivan Urgant\nMix\n";
        return 0;
    }
    if (n % 2) {
        cout << "Ivan Safonov\n";
        return 0;
    }
    cout << "Ivan Urgant\nDraw\n";
    return 0;
}
