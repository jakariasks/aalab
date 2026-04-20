#include <bits/stdc++.h>
using namespace std;


void heapifyDown(vector<int>& heap, int idx)
{
    int n= heap.size();

    while(true)
    {
        int left= 2 * idx + 1;
        int right= 2 * idx + 2;
        int largest= idx;

        if(left< n && heap[left]> heap[largest])
            largest= left;

        if(right< n && heap[right] > heap[largest])
            largest = right;

        if(largest == idx)
            break;


        swap(heap[idx], heap[largest]);
        idx = largest;
    }
}


void insertHeap(vector<int>& heap, int val)
{
    heap.push_back(val);
    int curr = (int)heap.size() - 1;

    while(curr > 0)
    {

        int parent = (curr - 1) / 2;

        if(heap[parent] < heap[curr])
        {
            swap(heap[parent], heap[curr]);
            curr = parent;
        }


        else
        {
            break;
        }
    }
}

// Delete root
int deleteRoot(vector<int>& heap)
{
    if(heap.empty())
    {

        cout << "Heap is empty!\n";
        return -1;
    }

    int removed = heap[0];

    heap[0] = heap.back();
    heap.pop_back();

    if(!heap.empty())
        heapifyDown(heap, 0);

    return removed;
}

int main()
{
    vector<int> heap;
    int n;

    cout<<"Enter number of elements: ";
    cin>>n;

    cout<<"Enter values: ";
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        insertHeap(heap, x);
    }

    cout<<"\nHeap before delete: ";
    for(int x : heap)
        cout<< x << " ";
    cout<<endl;



    int removed= deleteRoot(heap);
    cout<<"Deleted root (max): "<<removed<<endl;



    cout<<"Heap after delete: ";
    for(int x : heap)
        cout<< x << " ";
    cout<< endl;



    return 0;
}

