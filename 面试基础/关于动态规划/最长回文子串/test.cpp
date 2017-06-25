class Palindrome {
public:
    int getLongestPalindrome(string A, int n) {
        // write code here
        int** arr = new int*[n];
        
        for(int i = 0;i < n;i++){
            arr[i] = new int[n];
            memset(arr[i], 0, sizeof(int) * n);//初始化动态开辟的数组，这个很重要，很多问题就出现在没有初始化上
            arr[i][i] = 1;//每一个单独的字符都是一个回文字符串，所以这个回文串的字符为1；
        }
        
        int max = -1;
        
        //每次都比较长度递增子字符串是否是回文字符串
        for(int len = 2;len <= n;len++){
            //i是前边界
            for(int i = 0;i <= n-len;i++){
                int j = i + len - 1;//j为后边界
                
                if(len == 2 && A[i] == A[j]){
                    arr[i][j] = len;
                    max = len;//因为len一定是增大的，所以不需要if(max < len)max = len;
                	continue;//跳出本次循环是为了不在执行下面的if语句，以防一个区间两种判断且判断两次那么有可能引起错误
                }
                
                //arr[i][j]表示的是从i-j的这块区间里的字符串是不是回文子串，如果是，arr[i][j]等于回文串的长度，如果不是，其值为0
                //arr[i+1][j-1]便是的是最邻近区间【i-j】的区间【i+1 - j-1】的区间。如果A[i]==A[j]，那么如果【i-j】的最大子区间
                //【i+1 - j-1】也是回文字符串的话（arr[i+1][j-1] !=0），那么【i-j】区间也是回文字符串，反之，【i-j】就不是回文字符串
                if(A[i] == A[j] && arr[i+1][j-1] != 0){
                    arr[i][j] = len;
                    max = len;
                }
            }
        }
        
        delete[] arr;//养成良好的编程习惯，手动释放自己开辟的空间
        return max;
    }
};