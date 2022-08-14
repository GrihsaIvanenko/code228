#include <bits/stdc++.h>

using namespace std;

const unsigned long long pe = 60, q = 100000000000000013;

int main() {
    map<int, int> shir;
    map<string, int> cash;
    unsigned long long p[13];
    p[0] = 1;
    for(int i = 1; i < 13; ++i){
        p[i] = p[i - 1] * pe;
    }
    unordered_map<unsigned long long, pair<string,unordered_set<int>>>mm;
    int a, b;
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> a >> b;
    for(int i = 0; i < a; ++i){
        string s;
        cin >> s;
        if(cash.find(s) != cash.end()){
            shir[cash[s]]++;
            //cout <<cash[s] << endl;
            continue;
        }
        cash[s] = i;
        for(int k = 0; k <= s.size(); ++k){
            unsigned long long hash = 0;
            int ch = 0;
            for(int j = 0; j < s.size(); ++j){
                if(j != k - 1){
                    hash += p[ch++] * (s[j] - 'A' + 1);
                  //  hash %= q;
                }
            }

            mm[hash].first = s;
            mm[hash].second.insert(i);
        }

    }
    map<string, pair<int, string>> answer;
    for(int i = 0;  i < b; ++i){
        unordered_map<unsigned long long, int> mem_hash;
        string s;
        cin >> s;
        if(answer.find(s) != answer.end()){
            if(answer[s].second != ""){
                cout << s << " " << answer[s].first << " " << answer[s].second << endl;
            }
            else{
                cout << s << " " << answer[s].first << endl;
            }
            continue;
        }
        set<int> ans;
        long long troll_ans = 0;
        unsigned long long last_hash = 0;
        for(int k = 0; k <= s.size(); ++k){
            unsigned long long hash = 0;
            int ch = 0;
            for(int j = 0; j < s.size(); ++j){
                if(j != k - 1){
                    hash += p[ch++] * (s[j] - 'A' + 1);
                   // hash %= q;
                }
            }
                for(auto g = mm[hash].second.begin(); g != mm[hash].second.end() &&ans.size() != a; g++){
                    if(ans.find(*g) == ans.end()){
                        troll_ans += shir[*g];
                    }
                    ans.insert(*g);
                    last_hash = hash;
                }
        }
        cout << s << " " << ans.size() + troll_ans;
        string baseans = "";
        if(ans.size() + troll_ans == 1){
            cout << " " << mm[last_hash].first;
            baseans = mm[last_hash].first;
        }
        answer[s] = {ans.size() + troll_ans, baseans};
        cout << '\n';
    }
}
