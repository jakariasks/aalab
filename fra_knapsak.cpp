
#include <bits/stdc++.h>
using namespace std;

struct Item
{
    int weight;
    int profit;
};

bool cmp(const Item& a,const Item& b)
{
    double r1=(double)a.profit / a.weight;
    double r2=(double)b.profit / b.weight;
    return r1> r2;
}


int main()
{
    int capacity = 40;

    vector<Item>items = {
        {1, 6},
        {2, 10},
        {3, 12}
    };



    sort(items.begin(),items.end(),cmp);

    double maxProfit = 0.0;

    for(auto item : items)
    {
        if(item.weight<=capacity)
        {
            capacity -=item.weight;
            maxProfit +=item.profit;
        }


        else
        {
            maxProfit+= item.profit *((double)capacity / item.weight);
            break;
        }
    }

    cout<<"Maximum Profit = "<<maxProfit<<endl;


    return 0;
}
