#include <bits/stdc++.h>

using namespace std;

const int maxn = 2500;

void dtitch(int x){return;}

vector<int> g[maxn]; // ����� ������� ������ ���� �� ����� ���� � ������
int mt[maxn]; // � ����� �������� �������� ������� ������ ���� (-1, ���� �� � �����)
bool used[maxn]; // ��������������� ������ ��� ������ ���� dfs-��

// dfs ����������, ����� �� ����� ���� �� ������� v
// � �����-������ ������� ������ ����
// ���� �����, �� ��� � �������� �����������
bool dfs (int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int u : g[v]) {
        // ���� ������� ��������, �� ����� ����� � ��� �����������
        // ���� ��� ������, �� � �������� ����������� ������ �����,
        // ����� �� � ������� ���� ����� ����� �����-������ ������ �������
        if (mt[u] == -1 || dfs(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; ++i){
        int x;
        cin >> x;
        --x;
        while(x > -1){
            g[i].push_back(x);
            cin >> x;
            --x;
        }
    }
    for(int i = 0; i < maxn; ++i)mt[i] = -1;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
       for(int j = 0; j < maxn; ++j)used[j] = 0;
        if (dfs(i))
            cnt++;
    }
    cout << cnt << endl;
    for(int i = 0; i < m; ++i){
        if(mt[i] != -1){cout << mt[i] + 1 << ' ' << i + 1 << endl;
        cnt--;
        if(cnt == 0)return 0;
        }
    }
    return 0;
    return 0;
}
