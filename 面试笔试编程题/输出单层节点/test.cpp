/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};*/

/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};*/
class TreeLevel {
public:
    ListNode* getTreeLevel(TreeNode* root, int dep) {
        // write code here
        if(root == NULL || dep < 1) return NULL;
        
        L = new ListNode(-1);
        ListNode* head = L;
        Link(root,dep);
        
        return head->next;
    }
    void Link(TreeNode* root,int dep){
        if(root == NULL) return;
        
        if(dep == 1){
            L->next = new ListNode(root->val);
            L = L->next;
        }
        
        Link(root->left,dep-1);
        Link(root->right,dep-1);
    }
private:
    ListNode* L;
};