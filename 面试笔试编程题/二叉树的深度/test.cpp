/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    int Height(TreeNode* root){
        if(root == NULL)
            return 0;
        
        int left = Height(root->left) + 1;
        int right = Height(root->right) + 1;
  		
        return left > right ? left : right;
    }
    int TreeDepth(TreeNode* pRoot)
    {
    	return Height(pRoot);
    }
};