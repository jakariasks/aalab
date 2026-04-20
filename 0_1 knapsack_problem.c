#include <bits/stdc++.h>
using namespace std;

// Recursive 0/1 Knapsack Function
int knapsack(int n, int wt[], int val[], int capacity)
{
    // Base Case: No items left or capacity is 0
    if (n == 0 || capacity == 0)
        return 0;

    // If current item weight is less than or equal to capacity
    if (wt[n - 1] <= capacity)
    {
        // Option 1: Take the item
        int take = val[n - 1] +
                   knapsack(n - 1, wt, val, capacity - wt[n - 1]);

        // Option 2: Skip the item
        int skip = knapsack(n - 1, wt, val, capacity);

        // Return maximum of take and skip
        return max(take, skip);
    }
    else
    {
        // If item is heavier than capacity, skip it
        return knapsack(n - 1, wt, val, capacity);
    }
}

int main()
{
    int n;

    cout << "Enter number of items: ";
    cin >> n;

    int wt[n], val[n];

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++)
        cin >> wt[i];

    cout << "Enter values of items:\n";
    for (int i = 0; i < n; i++)
        cin >> val[i];

    int capacity;
    cout << "Enter capacity of knapsack: ";
    cin >> capacity;

    int result = knapsack(n, wt, val, capacity);

    cout << "\nMaximum value in Knapsack = " << result << endl;

    return 0;
}



//memorizition technique


#include <bits/stdc++.h>
using namespace std;

int dp[1005][1005];  // DP table (adjust size as needed)

// Memoized Knapsack
int knapsack(int n, int wt[], int val[], int capacity)
{
    // Base case
    if (n == 0 || capacity == 0)
        return 0;

    // If already calculated, return stored value
    if (dp[n][capacity] != -1)
        return dp[n][capacity];

    // If item can be taken
    if (wt[n - 1] <= capacity)
    {
        int take = val[n - 1] +
                   knapsack(n - 1, wt, val, capacity - wt[n - 1]);

        int skip = knapsack(n - 1, wt, val, capacity);

        // Store result
        return dp[n][capacity] = max(take, skip);
    }
    else
    {
        // Store result when skipping
        return dp[n][capacity] =
               knapsack(n - 1, wt, val, capacity);
    }
}

int main()
{
    int n;
    cin >> n;

    int wt[n], val[n];

    for (int i = 0; i < n; i++)
        cin >> wt[i];

    for (int i = 0; i < n; i++)
        cin >> val[i];

    int capacity;
    cin >> capacity;

    // Initialize DP table with -1
    memset(dp, -1, sizeof(dp));

    cout << knapsack(n, wt, val, capacity) << endl;

    return 0;
}
