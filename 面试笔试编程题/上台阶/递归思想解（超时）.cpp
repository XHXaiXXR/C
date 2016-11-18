class GoUpstairs {  
public:  
    int countWays(int n) {  
        // write code here  
        if(n == 0 || n == 1){  
            return 0;  
        }  
        else if(n == 2){  
            return 1;  
        }  
        else if(n == 3){  
            return 2;  
        }  
          
        return countWays(n-1) + countWays(n-2);  
    }  
};