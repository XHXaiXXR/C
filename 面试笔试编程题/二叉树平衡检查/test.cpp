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
    bool isBalance(TreeNode* root) {
        // write code here
        if(Height(root) <= 1) return true;
        
        int Left = Height(root->left);
        int Right = Height(root->right);
        
        if(abs(Left - Right) > 1) return false;
        
        return isBalance(root->left) && isBalance(root->right);
    }
    int Height(TreeNode* root){
        if(root == NULL) return 0;
        
        int Left = Height(root->left) + 1;
        int Right = Height(root->right) + 1;
        
        return Left > Right ? Left : Right;
    }
};