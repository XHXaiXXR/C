class FirstRepeat {
public:
    char findFirstRepeat(string A, int n) {
        // write code here
        if(n > 500)
            return 0;
        
        int ch[256] = {0};
        for(int i = 0;i < A.size();i++)
        {
            if(++ch[A[i]] == 2)
                return A[i];
        }
        
        return 0;
    }
};