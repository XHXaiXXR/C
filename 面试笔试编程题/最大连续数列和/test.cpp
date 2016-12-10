class MaxSum {
public:
    int getMaxSum(vector<int> A, int n) {
        // write code here
        vector<int> maxnum(n);	//子问题最优解的数组
        maxnum[0] = A[0];
        
        for(int i = 1;i < n;++i){
            maxnum[i] = max(A[i],maxnum[i-1]+A[i]);//找出子问题的最优解
        }
        
        int max = -1;
        for(int i = 0;i < n;++i){
            if(max < maxnum[i])
                max = maxnum[i];//找出连续数列的最大和
        }
        
        return max;
    }
};