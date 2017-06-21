struct ListNode
{
      int m_nKey;
      ListNode* m_pNext;
}ListNode;


ListNode* FindKthToTail(ListNode* pListHead, unsigned int k){
    if(k < 1){
        return NULL;
    }
    
    ListNode* prev = pListHead;
    ListNode* cur = prev;
    while(--k && cur){
        cur = cur->m_pNext;
    }
    
    if(cur == NULL){
        return NULL;
    }
    
    while(cur->m_pNext){
        prev = prev->m_pNext;
        cur = cur->m_pNext;
    }
    
    return prev;
}