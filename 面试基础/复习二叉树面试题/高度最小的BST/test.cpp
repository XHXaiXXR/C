class MinimalBST {
public:
    int buildMinimalBST(vector<int> vals) {
        // write code here
        if(vals.size() < 2){
            return vals.size();
        }
        
        return _buildMinimalBST(vals, 0, vals.size()-1);
    }
    
    int _buildMinimalBST(vector<int> vals,int left, int right){
        if(left > right){
            return 0;
        }
        
        int mid = left + (right - left) / 2;
        int leftH = _buildMinimalBST(vals, left, mid-1) + 1;
        int rightH = _buildMinimalBST(vals, mid+1, right) + 1;
        
        return leftH > rightH ? leftH : rightH;
    }
};