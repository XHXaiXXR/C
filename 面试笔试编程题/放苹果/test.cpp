// write your code here cpp
#include<iostream>
using namespace std;

int PlackApple(int m, int n){
    if(m == 0 || n == 1){
        //返回条件是，当苹果没了（m == 0） 或者 只剩下一个盘子（n == 1）的情况下
        return 1;
    }
    
    if(n > m){
        //当盘子大于苹果的情况下，那么只有m个盘子和m个苹果有多种不同的分法
        return PlackApple(m, m);
    }
    else{
        //当苹果比较多的时候，有两种情况
        //第一种：如果每次都有一个空盘子多余出来
        //第二种：每个盘子至少放一个，剩下的苹果再在当前的盘子里重新放置
        return PlackApple(m, n-1) + PlackApple(m-n, n);
    }
}

int main(){
    int m = 0;
    int n = 0;
    
    while(cin>>m>>n){
        cout<<PlackApple(m, n)<<endl;
    }
    return 0;
}