class Rearrange {
public:
    vector<int> findSegment(vector<int> A, int n) {
        // write code here
        vector<int> tmp(A);
        sort(tmp.begin(),tmp.end());
        
        vector<int> B(2,0);
        
        for(int i = 0;i < n;++i){
            if(A[i] != tmp[i]){
                B[0] = i;
                break;
            }
        }
        
        for(int i = n - 1;i >= 0;--i){
            if(A[i] != tmp[i]){
                B[1] = i;
                break;
            }
        }
        
        return B;
        
    }
};
