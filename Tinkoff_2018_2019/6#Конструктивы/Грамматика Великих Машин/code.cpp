#include <bits/stdc++.h>

using namespace std;

int main(){
    string s;
    cin >> s;
    int eater = 1;
    int credit = 0;
    for(int i = 0; i < s.size(); ++i){
        //cout << eater << " ";
        if(eater <= 0){
           credit++;
           eater++;
        }
        eater += s[i] - '0';
        eater--;
    }
    while(credit != 0){
        credit++;
        cout << min(credit, 7);
        credit -= min(credit, 7);
    }
    cout << s;
    for(int i = 0; i < eater; ++i){
        cout << 0;
    }
    return 0;
}


