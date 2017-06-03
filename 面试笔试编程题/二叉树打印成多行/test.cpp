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
        vector<vector<int> > Print(TreeNode* pRoot) {
        	vector<vector<int>> v;
            
            if(pRoot == NULL){
                return v;
            }
            
            //pRoot != NULL
            queue<TreeNode*> q;
            q.push(pRoot);
            
            while(!q.empty()){
                vector<int> v1;
                int size = q.size();
                TreeNode* pFront = q.front();
                
                while(size--){
                    pFront = q.front();
                    v1.push_back(pFront->val);
                    
                    if(pFront->left){
                        q.push(pFront->left);
                    }
                    if(pFront->right){
                        q.push(pFront->right);
                    }
                    
                    q.pop();
                }
                
                v.push_back(v1);
            }
            
            return v;
        }
    
};