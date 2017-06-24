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
            //ÿ��λ�ö������
            return A.size();
        }
        else if(begin < end){
            //�ҵ�����ȵ�����ĸ���
            return end - begin + 1; 
        }
        else{
            //ÿһ��λ�ö����
            return 0;
        }
        
    }
};