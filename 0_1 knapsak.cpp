#include <bits/stdc++.h>
using namespace std;

// 0/1 Knapsack (Recursive)
int knapsack(int n, int wt[], int val[], int capacity)
{
    // Base case
    if (n == 0 || capacity == 0)
        return 0;

    // If current item can be taken
    if (wt[n - 1] <= capacity)
    {
        // Option 1: take the item
        int take =
            knapsack(n - 1, wt, val, capacity - wt[n - 1]) + val[n - 1];

        // Option 2: skip the item
        int skip =
            knapsack(n - 1, wt, val, capacity);

        return max(take, skip);
    }
    else
    {
        // Item too heavy → must skip
        return knapsack(n - 1, wt, val, capacity);
    }
}

int main()
{
    int n;
    cin >> n;

    int wt[n], val[n];

    // Input weights
    for (int i = 0; i < n; i++)
        cin >> wt[i];

    // Input values
    for (int i = 0; i < n; i++)
        cin >> val[i];

    int capacity;
    cin >> capacity;

    cout << knapsack(n, wt, val, capacity) << endl;

    return 0;
}
[]
