class Rearrange {
public:
    vector<int> findSegment(vector<int> A, int n) {
        // write code here
        vector<int> Atmp = A;
        sort(Atmp.begin(), Atmp.end());
        
        int begin = 0;
        int end = A.size() - 1;
        bool flag = true;
        
        while(begin < A.size() && A[begin] == Atmp[begin]){
            flag = false;
            begin++;
        }
        while(end >= 0 && A[end] == Atmp[end]){
            end--;
        }
        
        vector<int> arr;
        if(flag == true){
            arr.push_back(0);
            arr.push_back(A.size());
        }
        else if(begin < end){
            arr.push_back(begin);
            arr.push_back(end);
        }
        else{
            arr.push_back(0);
            arr.push_back(0);
        }
        
        return arr;
    }
};