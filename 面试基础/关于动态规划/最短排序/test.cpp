class ShortSubsequence {
public:
    int findShortest(vector<int> A, int n) {
        // write code here
        vector<int> Atmp = A;
        sort(Atmp.begin(),Atmp.end());
        
        int begin = 0;
        int end = A.size()-1;
        bool flag = true;
        
        while(begin < A.size() && A[begin] == Atmp[begin]){
            begin++;
            flag = false;
        }
        
        while(end >= 0 && A[end] == Atmp[end]){
            end--;
        }
        
        
        if(flag){
            //每个位置都不相等
            return A.size();
        }
        else if(begin < end){
            //找到不相等的区间的个数
            return end - begin + 1; 
        }
        else{
            //每一个位置都相等
            return 0;
        }
        
    }
};