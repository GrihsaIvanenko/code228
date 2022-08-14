#include <bits/stdc++.h>

using namespace std;

vector<string> thu;

const char k = 26;

struct Vertex{
    int is_terminal = 0;
    Vertex *lol[k] = {0};
    void add(string s){
        if(s.size() == 0){
            is_terminal++;
            return;
        }
        int to = s[0] - 'a';
        if(!lol[to]){
            lol[to] = new Vertex();
        }
        lol[to]->add(s.substr(1));
    }
    void dfs(string s){
        for(int i = 0; i < is_terminal; ++i){
            thu.push_back(s);
        }
        for(int i = 0; i < 26; ++i){
            if(lol[i] != 0){
                lol[i]->dfs(s + char('a' + i));
            }
        }
    }
};

Vertex *root = new Vertex();

int main(){
    string s;
    cin >> s;
    map<int, int> points;
    int ch = 0;
    for(int i = 0; i < s.size();){
        string s1 = "";
        while(i < s.size() && s[i] >= 'a' && s[i] <= 'z'){
            s1.push_back(s[i]);
            i++;
        }
        thu.push_back(s1);
        ch++;
        while(i < s.size() && s[i] == '.'){
            points[ch]++;
            i++;
        }
    }
    //root->dfs("");
    sort(thu.begin(), thu.end());
    for(int i = 0; i < thu.size(); ++i){
        for(int j = 0; j < points[i]; ++j){
            cout << '.';
        }
        cout << thu[i];
    }
    for(int j = 0; j < points[thu.size()]; ++j){
            cout << '.';
        }
    return 0;
}

