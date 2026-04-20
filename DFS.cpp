#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
vector<int> g[N];
bool vis[N];


// DFS
void dfs(int src)
{
    vis[src]=true;
    cout<<src<<" ";

    for(int nxt:g[src])
    {
        if(!vis[nxt])
        {
            dfs(nxt);
        }
    }
}

int main()
{

    int n=6;

    vector<pair<int,int>>edges=
    {
        {0, 1},
        {0, 2},
        {1, 3},
        {1, 4},
        {2, 5},
        {3, 4},
        {4, 5}
    };


    for(auto[a, b]:edges)
    {
        g[a].push_back(b);
        g[b].push_back(a);
    }


    for(int i =0;i<n;i++)
        sort(g[i].begin(),g[i].end());

    memset(vis,false,sizeof(vis));

    int src=0;
    cout<<"DFS Travarsal: ";
    dfs(src);
    cout<<endl;

    return 0;
}
