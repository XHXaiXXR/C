// write your code here cpp
#include<iostream>
using namespace std;
//递归
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


//动态规划
// write your code here cpp
#include<iostream>
using namespace std;

int arr[200][200] = {0};

int PlackApple(int m, int n){
    arr[0][0] = 1;
    
    for(int i = 0;i <= m; ++i){
        for(int j = 1;j <= n; ++j){
        	if(i >= j){
                //苹果多余盘子的情况分法有两种
                //第一种，每个盘子放上一个，剩余苹果再到盘子里继续分配（arr[i-j][j]）
                //第二种，每次都至少有一个空盘子（arr[i][j-1]）
                arr[i][j] = arr[i - j][j] + arr[i][j - 1];
            }    
            else{
                //苹果个数有限，盘子再多也无用，苹果个数一定，分法不会因盘子过多而有所改变
                //故每次改变的都是盘子的变量
                arr[i][j] = arr[i][j-1];
            }
        }
    }
    
    return arr[m][n];
}

int main(){
    int m = 0;//苹果
    int n = 0;//盘子
    
    while(cin>>m>>n){
        cout<<PlackApple(m, n)<<endl;
    }
    return 0;
}