class GoUpstairs {  
public:  
    int countWays(int n) {  
        // write code here  
        vector<int> arr(n+1);  
        arr[0] = 0;  
        arr[1] = 0;  
        arr[2] = 1;  
        arr[3] = 2;  
          
        for(size_t i = 4;i < n + 1;i++){  
            arr[i] = (arr[i-1]+arr[i-2]) % 1000000007;  
        }  
          
        return arr[n];  
    }  
};