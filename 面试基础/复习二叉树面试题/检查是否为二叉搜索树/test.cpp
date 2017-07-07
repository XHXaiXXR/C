/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};*/

class Checker {
public:
    bool checkBST(TreeNode* root) {
        // write code here
        //��������������������ض�������ģ�����ֻ��Ҫһ�����齫������������������������Ȼ���鱣�������Ԫ���Ƿ�������ľͿ�����
        //ʱ�临�Ӷ�ΪO��n�����ռ临�Ӷ�ΪO��n��
        vector<int> arr;
        
        BSTarr(root, arr);
        
        for(int i = 0;i < arr.size()-1;i++){
            if(arr[i] > arr[i+1]){
                return false;
            }
        }
        return true;
    }
    void BSTarr(TreeNode* node, vector<int>& arr){
        if(node == NULL){
            return;
        }
        
        BSTarr(node->left, arr);
        arr.push_back(node->val);
        BSTarr(node->right,arr);
    }
};