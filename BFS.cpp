#include <bits/stdc++.h>

using namespace std;


vector<int>g[1005];
bool vis[1005];

// BFS
void bfs(int src)
{
    queue<int>q;
    q.push(src);
    vis[src]=true;


    while(!q.empty())
    {

        int node=q.front();
        q.pop();


        cout<<node <<" ";

        for(int nxt:g[node])
        {

            if(!vis[nxt])
            {
                vis[nxt]=true;
                q.push(nxt);
            }
        }
    }
}

int main()
{

    int n =6;

    vector<pair<int,int>>edges =
    {
        {0, 1},
        {0, 2},
        {1, 3},
        {1, 4},
        {2, 5},
        {3, 4},
        {4, 5}
    };


    // Build the graph
    for(auto[a, b]:edges)
    {
        g[a].push_back(b);
        g[b].push_back(a);
    }


    for(int i=0;i<n; i++)
        sort(g[i].begin(),g[i].end());

    memset(vis,false,sizeof(vis));

    int src =0;
    cout<<"BFS Travarsal:" ;
    bfs(src);
    cout<<endl;



    return 0;
}

