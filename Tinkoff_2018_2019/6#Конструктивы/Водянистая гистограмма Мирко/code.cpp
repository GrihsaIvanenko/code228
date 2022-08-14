#include <bits/stdc++.h>

using namespace std;

int main(){
ios::sync_with_stdio(false);
  long long a, b;
  cin >> a >> b;

  vector<int> ans, lol;
  //ans.push_back(a);
  for(int i = 0; i < a - 2; ++i){
    if(b >= a - i - 2){
        ans.push_back(i + 1);
        b -= (a - i - 2);
    }
    else{
        lol.push_back(-i - 1);
    }
  }
  if(b != 0){
    cout << -1 << endl;
    return 0;
  }
  sort(lol.begin(), lol.end());
  cout << a << " ";
  for(auto x : ans){
    cout << x << " ";
  }
  cout << a - 1 << " ";
  for(int i = 0; i < lol.size(); ++i){
    cout << -lol[i] << " ";
  }
}
