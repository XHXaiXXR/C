/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/
class Solution {
public:
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        int count = 0;
        return _KthNode(pRoot, k, count);
    }
    
    TreeNode* _KthNode(TreeNode* root, int k,int& count){
        if(root == NULL)
            return NULL;
        
        TreeNode* left = _KthNode(root->left, k, count);
        
        if(left != NULL){
            return left;
        }
        
        ++count;
        
        if(count == k){
            return root;
        }
        
        return _KthNode(root->right, k, count);
    }
};