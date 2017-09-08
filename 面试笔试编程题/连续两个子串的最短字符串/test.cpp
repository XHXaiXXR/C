#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[100];
int main(){
    scanf("%s",s);
    int n = strlen(s);
    int ans = n;
    for(int j=1;j<n;j++){
        if(strncmp(s,s+j,n-j)==0){
            ans = j;
            break;
        }
    }
    for(int i=0;i<ans;i++){
        printf("%c",s[i]);
    }
    printf("%s\n",s);
    return 0;
}