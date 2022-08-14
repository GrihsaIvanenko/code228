#include <bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin >> n;
    if(n % 6 == 2){
        for(int i = 2; i <= n; i += 2){
            cout << i << " ";
        }
        for(int i = 1; i < n; i += 4){
            cout << i + 2 << " " << i << " ";
        }
        cout << endl;
        return 0;
    }
    if(n % 2 == 0){
        for(int i = 2; i <= n; i += 2){
            cout << i << " ";
        }
        for(int i = 1; i <= n; i += 2){
            cout << i << " ";
        }
        cout << endl;
        return 0;
    }
    if(n % 6 == 3){
        if(n % 4 == 3){
            cout<<1<<" "<<3<<" "<<5<<" "<< 2<< " "<<10<< " "<<12<< " "<<14<< " "<<4<<" "<<13<<" "<<9<<" "<<6<<" "<<15<<" "<<7<<" "<<11<<" "<<8<< endl;
            return 0;
        }
        for(int i = 1; i <= n; i += 2){
            cout << i << " ";
        }
        for(int i = 4; i < n; i += 4){
            cout << i << " " << i - 2 << " ";
        }
          cout << endl;
           return 0;
    }
    if(n % 4 == 3){
        for(int i = 2; i <= n; i += 2){
            cout << i << " ";
        }
        for(int i = 1; i <= n; i += 2){
            cout << i << " ";
        }
        cout << endl;
        return 0;
    }
    if(n % 4 == 1){
         for(int i = 0; i < n / 2; ++i){
            cout << n / 2 - i + 1 << " " << n  - n % 2 - i  + 1 << " ";
        }
        cout << 1 << endl;
        return 0;
    }
    return 0;
}
