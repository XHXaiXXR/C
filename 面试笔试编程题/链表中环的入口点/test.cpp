/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        if(pHead == NULL){
            return NULL;
        }
		ListNode* slow = pHead;
        ListNode* fast = pHead;
        
        //找到环中的相汇点
        while(fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;
            
            if(fast == slow){
                fast = pHead;
                
                while(fast != slow){
                    fast = fast->next;
                    slow = slow->next;
                }
                
                return fast;
            }
        }
        
        return NULL;
    }
};