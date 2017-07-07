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
        if(root == NULL){
            return true;
        }
        
        if(root->left){
            if(root->left->val > root->val){
                return false;
            }
            if(root->left->right && (root->left->right->val > root->val)){
                return false;
            }
        }
        
        if(root->right){
            if(root->right->val < root->val){
                return false;
            }
            if(root->right->left && (root->right->left->val < root->val)){
                return false;
            }
        }
        
        return checkBST(root->left) && checkBST(root->right);
    }
};