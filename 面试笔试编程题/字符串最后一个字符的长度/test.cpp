#include<iostream>  
using namespace std;  
#include<string>  
  
void test()  
{  
    string str;  
    getline(cin,str);  
  
    if(str.length() >= 5000 || str.length() == 0)  
    {  
        return;  
    }  
    string::iterator it = str.begin();  
  
    int count = 0;  
    while(it != str.end())  
    {  
        ++count;  
  
        if(*it == ' ')  
        {  
            count = 0;  
        }  
          
        ++it;  
    }  
  
    cout<<count<<endl;  
}  
int main()  
{  
    test();  
    system("pause");  
    return 0;  
}