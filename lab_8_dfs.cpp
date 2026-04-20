#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> v[N];
bool vis[N];


void dfs(int src)
{
    cout << src << endl;
    vis[src] = true;

    for (int child : v[src])   
    {
         if(vis[child] == false)
        {
            dfs(child);
        }               
    }
}


int main()
{
        int n, e;

        cout << " enter number of node and edge:" << endl;

        cin >> n >> e;

        while (e--)
           
    {
                int a, b;

                cout << " enter edges:" << endl;

                cin >> a >> b;
                v[a].push_back(b);
                v[b].push_back(a);
           
    }
        memset(vis, false, sizeof(vis));
        dfs(0);
        return 0;
}
/*
6 7
0 1
0 2
1 3
1 4
2 5
3 4
4 5
output
0
1
3
4
5
2

