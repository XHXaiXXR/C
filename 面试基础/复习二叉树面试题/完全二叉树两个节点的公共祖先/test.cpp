// write your code here cpp
#include<iostream>
using namespace std;

//˼·����ȫ�����������ӽڵ�Ϊx�����ڵ�һ����x/2
int main(){
    int x = 0;
    int y = 0;
    
    while(cin>>x>>y){
        while(x != y){
            if(x > y){
         	   x = x/2;
        	}
        	else{
            	y = y/2;
        	}
        }
        
        cout<<x<<endl;
    }
}