class Palindrome {
private:
    bool _Equal(string str){
        string strtmp = str;
        reverse(str.begin(), str.end());
        
        if(str == strtmp){
            return true;
        }
        return false;
    }
public:
    string addToPalindrome(string A, int n) {
        // write code here
        string addstr;
        reverse(A.begin(), A.end());
        
        while(!A.empty()){
            addstr.push_back(A.back());
            A.pop_back();
            
            if(_Equal(A)){
                break;
            }
        }
        
        reverse(addstr.begin(), addstr.end());
        
        return addstr;
    }
};