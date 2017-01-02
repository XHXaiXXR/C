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
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        ListNode* cur = pListHead;
        ListNode* prev = pListHead;
        
        while(k--){
            if(cur == NULL) return NULL;
            cur = cur->next;
        }
        
        while(cur != NULL){
            prev = prev->next;
            cur = cur->next;
        }
        
        return prev;
    }
};