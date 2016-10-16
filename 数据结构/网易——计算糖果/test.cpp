#include<iostream>
using namespace std;

void test()
{
    int x,y,j,k;
    cin>>x;
    cin>>y;
    cin>>j;
    cin>>k;
    
    int a = 0;
    if((x + j) % 2 == 0)
    {
        a = (x + j) / 2;
    }
    
    int b = 0;
    if((y + k) % 2 == 0)
    {
        b = (y + k) / 2;
    }
    
    int c = 0;
    if((a + b) == j)
    {
        c = k - b;
    }
    else
    {
        cout<<"No"<<endl;
        return;
    }
    
    cout<<a<<" "<<b<<" "<<c<<endl;
}
int main()
{
    test();
    return 0;
}