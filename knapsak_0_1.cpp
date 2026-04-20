#include <bits/stdc++.h>
using namespace std;


int knapsack(int n,int wt[],int val[],int capacity)
{

    if(n== 0||capacity ==0)
        return 0;

    if(wt[n- 1]<=capacity)
    {
        int take=knapsack(n - 1, wt,val,capacity -wt[n - 1])+ val[n - 1];
        int skip=knapsack(n - 1, wt, val,capacity);


        return max(take, skip);
    }
    else
    {

        return knapsack(n - 1, wt, val, capacity);
    }
}

int main()
{

    int wt[]= {1, 3, 4, 5};
    int val[]= {1, 4, 5, 7};
    int n =4;
    int capacity =7;

    cout<<"Maximum value: "<<knapsack(n, wt, val, capacity)<<endl;

    return 0;
}
