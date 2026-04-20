
#include <bits/stdc++.h>
using namespace std;

const int N = 100;

vector<pair<int, int>> g[N];
int dist[N];



void dijkstra(int src)
{

    priority_queue<pair<int,int>,vector<pair<int, int>>,greater<pair<int,int>>>pq;

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty())
    {
        auto[cost, node]=pq.top();
        pq.pop();


        if(cost > dist[node])
            continue;


        for(auto [nextNode, edgeCost] : g[node])
        {

            if(cost + edgeCost < dist[nextNode])
            {

                dist[nextNode] = cost + edgeCost;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }
}




int main()
{

    int n = 6;


    vector<tuple<int, int, int>> edges =
    {
        {0, 1, 4},          //u,v,w
        {0, 2, 2},
        {1, 2, 5},
        {1, 3, 10},
        {2, 4, 3},
        {4, 3, 4},
        {3, 5, 11}
    };




    for(auto [a, b, c] : edges)
    {
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }



    for(int i = 0; i < n; i++)
        dist[i] = INT_MAX;




    dijkstra(0);


    for(int i = 0; i < n; i++)
    {
        cout<<i<< " -> "<< dist[i]<<endl;
    }



    return 0;
}

