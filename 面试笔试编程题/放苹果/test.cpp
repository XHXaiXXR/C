// write your code here cpp
#include<iostream>
using namespace std;

int PlackApple(int m, int n){
    if(m == 0 || n == 1){
        //���������ǣ���ƻ��û�ˣ�m == 0�� ���� ֻʣ��һ�����ӣ�n == 1���������
        return 1;
    }
    
    if(n > m){
        //�����Ӵ���ƻ��������£���ôֻ��m�����Ӻ�m��ƻ���ж��ֲ�ͬ�ķַ�
        return PlackApple(m, m);
    }
    else{
        //��ƻ���Ƚ϶��ʱ�����������
        //��һ�֣����ÿ�ζ���һ�������Ӷ������
        //�ڶ��֣�ÿ���������ٷ�һ����ʣ�µ�ƻ�����ڵ�ǰ�����������·���
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