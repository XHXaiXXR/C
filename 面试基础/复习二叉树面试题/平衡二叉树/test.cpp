class Solution {
public:
    bool IsBalanced_Solution(TreeNode* root) {
		if(root == NULL)
            return true;
        
        int leftH = Height(root->left);
        int rightH = Height(root->right);
        
        if(abs(leftH - rightH) > 1)
            return false;
        
        return true;
    }
    
    int Height(TreeNode* root){
        if(root == NULL)
            return 0;
        
        int leftH = Height(root->left) + 1;
        int rightH = Height(root->right) + 1;
		
        return leftH > rightH ? leftH : rightH;
    }
};