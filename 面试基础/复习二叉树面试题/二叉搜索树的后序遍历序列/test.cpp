class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
		//BST�ĺ������еĺϷ������ǣ�����һ������S�����һ��Ԫ����x ��Ҳ���Ǹ�����
        //���ȥ�����һ��Ԫ�ص�����ΪT����ôT���㣺T���Էֳ����Σ�ǰһ�Σ���������
        //С��x����һ�Σ�������������x���������Σ����������ǺϷ��ĺ������С������ĵݹ鶨�� : ) ��
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