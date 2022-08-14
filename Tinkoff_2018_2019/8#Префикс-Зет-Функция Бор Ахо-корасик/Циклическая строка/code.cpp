#include <bits/stdc++.h>

using namespace std;

vector<int> pref (string s) {
	int n = s.size();
	vector<int> ans (n);
	//int max_ = 0;
	for (int i = 1; i < n; ++i) {
		int j = ans[i - 1];
		while (j > 0 && s[i] != s[j])
			j = ans[j - 1];
		if (s[i] == s[j]){
            ++j;
		}
		ans[i] = j;
		//max_ = max(j, max_);
	}
	//ans.push_back(max_);
	return ans;
}

int main()
{
    string s;
    cin >> s;
    vector<int> prefi = pref(s);
    cout << s.size() - prefi[prefi.size() - 1] << endl;
    return 0;
}

