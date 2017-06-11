/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        ListNode* node1 = pHead1;
        ListNode* node2 = pHead2;
        int len1 = 0;
        int len2 = 0;
        
        //求出两个链表的长度
        while(node1 || node2){
            if(node1){
                len1++;
                node1 = node1->next;
            }
            
            if(node2){
                len2++;
                node2 = node2->next;
            }
        }
        
        ListNode* shortlist = pHead1;
        ListNode* longlist = pHead2;
        if(len1 > len2){
            longlist = pHead1;
            shortlist = pHead2;
        }
        
        //长的链表先走上len步
        int len = abs(len1-len2);
        while(len--){
            longlist = longlist->next;
        }
        
        //然后两个指针一块走，每走一步判断两个节点是否相等
        while(shortlist && longlist){
            if(shortlist == longlist){
                return shortlist;
            }
            
            shortlist = shortlist->next;
            longlist = longlist->next;
        }
        
        return NULL;
    }
};