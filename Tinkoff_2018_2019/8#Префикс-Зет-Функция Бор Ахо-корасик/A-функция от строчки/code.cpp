#include <bits/stdc++.h>

using namespace std;

vector<int> z_function (string s) {
	int n = (int) s.length();
	vector<int> z (n);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = min (r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
	return z;
}
int main()
{
    int n;
    cin >> n;
    n--;
    string s, s1, s2;
    cin >> s;
    s1 = s;
    reverse(s.begin(), s.end());
    for(auto x : s){
        s1.push_back(x);
    }
    //cout << s1 << endl;
    vector<int> prefi = z_function(s1);
    //prefi[0] = s.size();
   for(int i = prefi.size() - 1; i > n; --i){
        cout << prefi[i] << " ";
   }
    return 0;
}
