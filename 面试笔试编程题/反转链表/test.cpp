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
    ListNode* ReverseList(ListNode* pHead) {
		ListNode* newpHead = NULL;
        ListNode* cur = NULL;
        ListNode* prev = pHead;
        
        while(prev){
            newpHead = prev;
            prev = prev->next;
            newpHead->next = cur;
            cur = newpHead;
        }
        
        return newpHead;
    }
};