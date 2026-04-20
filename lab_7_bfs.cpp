#include <bits/stdc++.h>

using namespace std;

vector<int> v[1005];

bool vis[1005];

void bfs(int src)

{

    queue<int> q;

    q.push(src);

    vis[src] = true;

    while (!q.empty())

    {

        int par = q.front();

        q.pop();

        cout << par << endl;

        for (int child : v[par])

        {

            if (vis[child] == false)

            {

                q.push(child);

                vis[child] = true;

            }

        }

    }

}

int main()

{
    cout << " enter number of node and edge:" << endl;

    int n, e;

    cin >> n >> e;

    while (e--)

    {

        int a, b;

        cout << " enter edges:" << endl;


        cin >> a >> b;

        v[a].push_back(b);

        v[b].push_back(a);

    }

    int src;

    cin >> src;

    memset(vis, false, sizeof(vis));

    bfs(src);

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
0

output
0
1
2
3
4
5
