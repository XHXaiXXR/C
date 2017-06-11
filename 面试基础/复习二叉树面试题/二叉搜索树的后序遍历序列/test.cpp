class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
		//BST的后序序列的合法序列是，对于一个序列S，最后一个元素是x （也就是根），
        //如果去掉最后一个元素的序列为T，那么T满足：T可以分成两段，前一段（左子树）
        //小于x，后一段（右子树）大于x，且这两段（子树）都是合法的后序序列。完美的递归定义 : ) 。
		if(!sequence.size())
            return false;
        
        return Segmentation(sequence, 0, sequence.size()-1);
    }
    
    bool Segmentation(const vector<int>& s, int left, int right){
        if(left >= right)
            return true;
        
        int index = right;
        while(index > left && s[index-1] > s[right])
            index--;
        
        for(int i = index-1; i >= left; --i){
            if(s[i] > s[right])
                return false;
        }
        
        return Segmentation(s, left, index-1) && Segmentation(s, index, right-1);
    }
};