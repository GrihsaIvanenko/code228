#include <bits/stdc++.h>

using namespace std;

int ans = 0;

const char k = 26;

struct Vertex{
    bool is_terminal = false;
    Vertex *lol[k] = {0};
    void add(string s){
        if(s.size() == 0){
            is_terminal = true;
            return;
        }
        int to = s[0] - 'a';
        if(!lol[to]){
            lol[to] = new Vertex();
        }
        lol[to]->add(s.substr(1));
    }
    void dfs(int d){
        if(is_terminal)d = d + 1;
        ans = max(ans, d);
        for(auto x : lol){
            if(x != 0){
                x->dfs(d);
            }
        }
    }
};

Vertex *root = new Vertex();

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i){
        string s;
        cin >> s;
        root->add(s);
    }
    root->dfs(0);
    cout << ans << endl;
    return 0;
}

