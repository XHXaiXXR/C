/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};*/

class Successor {
public:
    int findSucc(TreeNode* root, int p) {
        // write code here
        InOrder(root);
        
        for(int i = 0;i < v.size();++i){
            if(v[i] == p){
                return v[i + 1];
            }
        }
        
        return -1;
    }
    void InOrder(TreeNode* root){
        if(root == NULL) return;
        
        InOrder(root->left);
        v.push_back(root->val);
        InOrder(root->right);
    }
private:
    vector<size_t> v;
};