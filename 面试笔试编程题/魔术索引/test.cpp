//二分查找类似法
class MagicIndex {
public:
    bool findMagicIndex(vector<int> A, int n) {
        // write code here
        int left = 0;
        int right = A.size() - 1;
        
        while(left <= right){
            int mid = (left + right) / 2;
            
            if(A[mid] > mid)
                left = mid + 1;
            else if(A[mid] < mid)
                right = mid - 1;
            else 
                return true;
        }
        
        return false;
    }
};

//暴力法
class MagicIndex {
public:
    bool findMagicIndex(vector<int> A, int n) {
        // write code here
        for(int i = 0 ;i < n;i++){
            if(A[i] == i)
                return true;
        }
        
        return false;
    }
};