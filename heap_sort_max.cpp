#include <bits/stdc++.h>
using namespace std;


void heapifyDown(vector<int>& heap, int idx)
{
    int n = heap.size();

    while(true)
    {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int largest = idx;

        if(left< n && heap[left] > heap[largest])
            largest = left;

        if(right< n && heap[right] > heap[largest])
            largest = right;

        if(largest== idx)
            break;

        swap(heap[idx], heap[largest]);
        idx = largest;
    }
}

// Inser
void insertHeap(vector<int>& heap, int val)
{
    heap.push_back(val);
    int curr = (int)heap.size() - 1;


    while(curr> 0)
    {
        int parent=(curr - 1) / 2;


        if (heap[parent] < heap[curr])
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

// Delete
int deleteRoot(vector<int>& heap)
{
    int removed = heap[0];
    heap[0] = heap.back();
    heap.pop_back();

    if(!heap.empty())
        heapifyDown(heap, 0);

    return removed;
}

// Heap sort
vector<int> heapSort(const vector<int>& arr)
{
    vector<int>heap;
    for(int x: arr)
        insertHeap(heap, x);

    vector<int> sorted;
    while(!heap.empty())
        sorted.push_back(deleteRoot(heap));

    reverse(sorted.begin(), sorted.end());
    return sorted;
}

int main()
{
    int n;
    cout<<"Enter number of elements: ";
    cin>> n;

    vector<int> arr(n);
    cout<< "Enter values:\n";
    for (int i = 0; i < n; i++)
        cin>> arr[i];

    vector<int>sorted = heapSort(arr);

    cout<< "\n\nSorted (Ascending): ";
    for (int x : sorted)
        cout << x << " ";
    cout<< endl;

    return 0;
}
