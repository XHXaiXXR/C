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
        //二叉搜索树的中序遍历必定是升序的，我们只需要一个数组将树的中序遍历结果保存起来，然后检查保存的数组元素是否是升序的就可以了
        //时间复杂度为O（n），空间复杂度为O（n）
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