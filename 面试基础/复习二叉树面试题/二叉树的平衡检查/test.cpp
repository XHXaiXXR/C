/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};*/

class Balance {
public:
    int Height(TreeNode* root){
        if(root == NULL){
            return 0;
        }
        
        int left = Height(root->left) + 1;
        int right = Height(root->right) + 1;
        
        return left > right ? left : right;
    }
    
    bool isBalance(TreeNode* root){
        if(root == NULL){
            return true;
        }
        
        int left = Height(root->left);
        int right = Height(root->right);
        if(abs(left-right) > 1){
            return false;
        }
        
        return true;
    }
};