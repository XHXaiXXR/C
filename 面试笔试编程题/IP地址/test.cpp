#include <stdio.h>
int main(){
    int n, a, b, c, d;
    scanf("%d", &n);
    while(n--){
      scanf("%d.%d.%d.%d", &a, &b, &c, &d);
        if (a < 0 || b < 0 || c < 0 || d < 0 || a > 255 || b > 255 || c > 255 || d > 255)
            printf("No!\n");
        else
            printf("Yes!\n");
    }
    return 0;
}