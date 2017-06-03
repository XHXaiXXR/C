/*
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};
*/
class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        TreeLinkNode* pNext = NULL;
        if(pNode->right != NULL){
            //该结点有右子树，那么该节点的下一个节点为右子树的最左节点
            pNode = pNode->right;
            while(pNode->left != NULL){
                pNode = pNode->left;
            }
            
            pNext = pNode;
        }
        else if(pNode->next != NULL){
            //该结点没有右子树且父节点不为空，有两种情况
            //第一种：该结点为父节点的左节点，那么该节点的下一个节点为该节点的父节点
            //第二种：该结点为父节点的右节点，那么该节点的下一个节点为该节点的父节点的父节点的父节点的父。。。
            
            while(pNode->next != NULL && pNode->next->right == pNode){
                pNode = pNode->next;
            }
            
            pNext = pNode->next;
        }
        
        return pNext;
    }
};