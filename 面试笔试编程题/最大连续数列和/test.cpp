class MaxSum {
public:
    int getMaxSum(vector<int> A, int n) {
        // write code here
        vector<int> maxnum(n);	//���������Ž������
        maxnum[0] = A[0];
        
        for(int i = 1;i < n;++i){
            maxnum[i] = max(A[i],maxnum[i-1]+A[i]);//�ҳ�����������Ž�
        }
        
        int max = -1;
        for(int i = 0;i < n;++i){
            if(max < maxnum[i])
                max = maxnum[i];//�ҳ��������е�����
        }
        
        return max;
    }
};