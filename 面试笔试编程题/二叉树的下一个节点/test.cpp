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
            //�ý��������������ô�ýڵ����һ���ڵ�Ϊ������������ڵ�
            pNode = pNode->right;
            while(pNode->left != NULL){
                pNode = pNode->left;
            }
            
            pNext = pNode;
        }
        else if(pNode->next != NULL){
            //�ý��û���������Ҹ��ڵ㲻Ϊ�գ����������
            //��һ�֣��ý��Ϊ���ڵ����ڵ㣬��ô�ýڵ����һ���ڵ�Ϊ�ýڵ�ĸ��ڵ�
            //�ڶ��֣��ý��Ϊ���ڵ���ҽڵ㣬��ô�ýڵ����һ���ڵ�Ϊ�ýڵ�ĸ��ڵ�ĸ��ڵ�ĸ��ڵ�ĸ�������
            
            while(pNode->next != NULL && pNode->next->right == pNode){
                pNode = pNode->next;
            }
            
            pNext = pNode->next;
        }
        
        return pNext;
    }
};