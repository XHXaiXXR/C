class Palindrome {
public:
    string addToPalindrome(string A, int n) {
        // write code here
        //�����ַ���-->ԭ�ַ���==��ת�ַ���
        //A�� abcddrfrdd
        //B:     ddrfrddcba
        //˼�룺�洢A�ķ�ת�ַ�����C���ҵ���Ļ����ַ����������з�ת���ԭ�ַ�������ͬ�Ĳ��֣�,c�ַ�����ȥ�����ַ�����ʣ����ַ���������Ҫ��ӵ��ַ���
        string B = A;
        reverse(B.begin(), B.end());//BΪ��ת�ַ���
        
        for(int i = 0;i < n;i++){
            //str.substr(��ʼ��λ�ã��ַ����ĳ���)
            if(A.substr(i, n-i) == B.substr(0, n-i)){
                return B.substr(n-i, i);
            }
        }
        
        return "";
    }
};