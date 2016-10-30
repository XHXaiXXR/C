#include<iostream>  
using namespace std;  
#include<string>  
  
int main(){  
    string str;  
  
    while(cin>>str){  
        int count[4] = {0};  
          
        if(str.size() <= 8)  
            goto NG;  
  
        for(size_t i = 0;i < str.size();i++){  
            if(str[i] >= 'a' && str[i] <= 'z')  
                count[0] = 1;  
            else if(str[i] >= 'A' && str[i] <= 'Z')  
                count[1] = 1;  
            else if(str[i] >= '0' && str[i] <= '9')  
                count[2] = 1;  
            else  
                count[3] = 1;  
        }  
        if(count[0] + count[1] + count[2] + count[3] < 3)  
            goto NG;  
  
        for(int i = 0; i <= str.size()-6; i++)  
            for(int j = i+3;j < str.size();j++)  
                if(str[i] == str[j] && str[i+1] == str[j+1] &&str[i+2] == str[j+2])   
                    goto NG;  
  
        cout<<"OK"<<endl;  
        continue;  
  
        NG:  
            cout<<"NG"<<endl;  
    }  
    return 0;  
}  