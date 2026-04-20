#include <bits/stdc++.h>
using namespace std;

int main()
{

    int n = 4;

    int adj[4][4] =
    {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };


    for(int k= 0; k < n; k++)
    {
        for(int i= 0;i < n; i++)
        {
            for(int j= 0;j < n; j++)
            {
                adj[i][j]= adj[i][j] || (adj[i][k] && adj[k][j]);
            }
        }
    }

    cout << "Transitive Closure Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
