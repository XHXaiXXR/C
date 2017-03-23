/* 
struct RandomListNode { 
    int label; 
    struct RandomListNode *next, *random; 
    RandomListNode(int x) : 
            label(x), next(NULL), random(NULL) { 
    } 
}; 
*/  
  
class Solution {  
public:  
        
    void CloneNodeNext(RandomListNode* pHead) {  
        RandomListNode* pNow = pHead;  
            
        while (pNow != NULL) {          
                RandomListNode* pNode = new RandomListNode(pNow->label);  
                pNode->next = pNow->next;  
                pNow->next = pNode;  
                pNow = pNode->next;  
        }  
            
    }  
        
    void CloneNodeRandom(RandomListNode* pHead) {  
        RandomListNode* pNow = pHead;  
        while (pNow != NULL) {  
            if (pNow->random != NULL) {  
                pNow->next->random = pNow->random->next;  
                    
            }  
            pNow = pNow->next->next;  
        }  
    }  
        
    RandomListNode* CloneList(RandomListNode* pHead) {  
        RandomListNode* pCloneList = pHead->next;  
            
        RandomListNode* pClone = pCloneList;  
            
        RandomListNode* pNow = pHead;  
            
        while (pNow != NULL) {  
                pNow->next = pClone->next;  
                 
                if (pClone->next != NULL) {  
                    pClone->next = pNow->next->next;  
                    pClone = pNow->next->next;    
                }  
                    
                pNow = pNow->next;  
    
        }  
            
        return pCloneList;  
    }  
        
    RandomListNode* Clone(RandomListNode* pHead)  
    {  
        if (pHead == NULL) {  
            return NULL;  
        }  
        CloneNodeNext(pHead);  
        CloneNodeRandom(pHead);  
        return CloneList(pHead);  
    }  
};  