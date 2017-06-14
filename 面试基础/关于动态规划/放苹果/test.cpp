// write your code here cpp
#include<iostream>
using namespace std;
//�ݹ�
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


//��̬�滮
// write your code here cpp
#include<iostream>
using namespace std;

int arr[200][200] = {0};

int PlackApple(int m, int n){
    arr[0][0] = 1;
    
    for(int i = 0;i <= m; ++i){
        for(int j = 1;j <= n; ++j){
        	if(i >= j){
                //ƻ���������ӵ�����ַ�������
                //��һ�֣�ÿ�����ӷ���һ����ʣ��ƻ���ٵ�������������䣨arr[i-j][j]��
                //�ڶ��֣�ÿ�ζ�������һ�������ӣ�arr[i][j-1]��
                arr[i][j] = arr[i - j][j] + arr[i][j - 1];
            }    
            else{
                //ƻ���������ޣ������ٶ�Ҳ���ã�ƻ������һ�����ַ����������ӹ���������ı�
                //��ÿ�θı�Ķ������ӵı���
                arr[i][j] = arr[i][j-1];
            }
        }
    }
    
    return arr[m][n];
}

int main(){
    int m = 0;//ƻ��
    int n = 0;//����
    
    while(cin>>m>>n){
        cout<<PlackApple(m, n)<<endl;
    }
    return 0;
}