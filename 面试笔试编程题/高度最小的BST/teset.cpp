class MinimalBST {
public:
    //思路：取有序数组中间数值作为二叉搜索树的根，这样高度最小。确定根之后，递归依次确定根的左子树的根，右子树的根。。。
    int buildMinimalBST(vector<int> vals) {
        // write code here
        if(vals.size() <= 1) return vals.size();
        
        return Height(buildBST(vals,0,vals.size()-1));
    }
    int Height(TreeNode* root){
        if(root == NULL) return 0;
        
        int Left = Height(root->left) + 1;
        int Right = Height(root->right) + 1;
        
        return Left > Right ? Left : Right;
    }
    TreeNode* buildBST(vector<int> vals,int l,int r){
        if(l > r) return NULL;
        
        int mid = l + (r - l) / 2;
        TreeNode* root = new TreeNode(vals[mid]);
        root->left = buildBST(vals,l,mid-1);
        root->right = buildBST(vals,mid+1,r);

        return root;
    }
};