#include <bits/stdc++.h>

using namespace std;

int main() {
    srand(time(nullptr));
    int len = 70;
    for (int i = 0; i < len; ++i) {
        int c = rand() % 3;
        if (c == 0)
            cout << '0';
        else if (c == 1)
            cout << '1';
        else if (true)
            cout << '?';
    }
    return 0;
}
