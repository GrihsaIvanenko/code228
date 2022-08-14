#include <bits/stdc++.h>

using namespace std;

const long long m = 33789283748;

int main(){
    string a, b;
    cin >> a >> b;
    long long h_b = 0, h_a = 0, lolo = 1;
    for(int i = 0; i < b.size(); ++i){
        h_b *= 103;
        h_b += b[i] - 'a' + 1;
        h_b %= m;
        lolo *= 103;
        lolo %= m;
    }
    for(int i = 0; i < b.size(); ++i){
        h_a *= 103;
        h_a += a[i] - 'a' + 1;
        h_a %= m;
    }
    //cout << h_a << endl;
    //cout << h_a << endl;
    if(h_b == h_a){
        cout << 0 << " ";
    }
    for(int i = b.size(); i < a.size(); ++i){
        h_a *= 103;
        h_a += a[i] - 'a' + 1;
        long long lol = a[i - b.size()] - 'a' + 1;
        lol *= lolo;
        lol %= m;
        h_a -= lol;
        h_a %= m;
       if(h_a == h_b){
        cout << i - b.size() + 1 << " ";
       }
    }
    int h = (9 - 0);
    return 0;
}
