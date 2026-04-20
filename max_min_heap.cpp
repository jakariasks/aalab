#include <bits/stdc++.h>
using namespace std;



int main()
{
    vector<int>heap;
    int n;
    cout<<"Enter number of elements: ";
    cin>>n;

    cout<<"Enter values:\n";
    for(int i = 0; i < n; i++)
    {
        int val;
        cin>>val;

        //end
        heap.push_back(val);


        int curr=heap.size()- 1;

        while(curr>0)
        {
            int parent=(curr -1)/2;


            // Max
            if (heap[parent]<heap[curr])
            {
                swap(heap[parent],heap[curr]);
                curr=parent;
            }

            else
            {

                break;
            }
        }
    }



    cout<<"\nHeap elements: ";

    for(int x:heap)
    {
        cout<<x<<" ";
    }

    cout<<endl;



    return 0;
}
