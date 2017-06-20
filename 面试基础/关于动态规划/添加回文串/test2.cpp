class Palindrome {
public:
    string addToPalindrome(string A, int n) {
        // write code here
        //回文字符串-->原字符串==翻转字符串
        //A： abcddrfrdd
        //B:     ddrfrddcba
        //思想：存储A的翻转字符串于C，找到最长的回文字符串（就是有翻转后和原字符串还相同的部分）,c字符串减去回文字符串，剩余的字符串就是需要添加的字符串
        string B = A;
        reverse(B.begin(), B.end());//B为翻转字符串
        
        for(int i = 0;i < n;i++){
            //str.substr(开始的位置，字符串的长度)
            if(A.substr(i, n-i) == B.substr(0, n-i)){
                return B.substr(n-i, i);
            }
        }
        
        return "";
    }
};