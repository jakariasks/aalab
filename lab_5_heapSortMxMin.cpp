#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> v;
    int n;
    cin >> n;

    for (int i = 0; i< n; i++)
    {
        int x;
        cin >> x;

        v.push_back(x);

        int curr = v.size()-1;

        while (curr != 0)
        {
            int par = (curr-1)/2;

            if (v[par] <= v[curr]) // for minheap use===>>> if (v[par] >= v[curr])
            {
               swap(v[par], v[curr]);
            }

            else
            {
               break;
            }

            curr = par;
        }
    }

    for (int val : v)
    {
        cout << val << " ";
    }


    return 0;
}

