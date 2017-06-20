/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};*/
class PalindromeList {
public:
    bool chkPalindrome(ListNode* A) {
        // write code here
        ListNode* cur = A;
        vector<int> v;
        
        while(cur != NULL){
            v.push_back(cur->val);
            cur = cur->next;
        }
        
        vector<int> vt = v;
        reverse(vt.begin(), vt.end());
        
        if(vt == v){
            return true;
        }
        return false;
    }
};