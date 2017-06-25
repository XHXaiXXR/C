class Palindrome {
public:
    int getLongestPalindrome(string A, int n) {
        // write code here
        int** arr = new int*[n];
        
        for(int i = 0;i < n;i++){
            arr[i] = new int[n];
            memset(arr[i], 0, sizeof(int) * n);//��ʼ����̬���ٵ����飬�������Ҫ���ܶ�����ͳ�����û�г�ʼ����
            arr[i][i] = 1;//ÿһ���������ַ�����һ�������ַ���������������Ĵ����ַ�Ϊ1��
        }
        
        int max = -1;
        
        //ÿ�ζ��Ƚϳ��ȵ������ַ����Ƿ��ǻ����ַ���
        for(int len = 2;len <= n;len++){
            //i��ǰ�߽�
            for(int i = 0;i <= n-len;i++){
                int j = i + len - 1;//jΪ��߽�
                
                if(len == 2 && A[i] == A[j]){
                    arr[i][j] = len;
                    max = len;//��Ϊlenһ��������ģ����Բ���Ҫif(max < len)max = len;
                	continue;//��������ѭ����Ϊ�˲���ִ�������if��䣬�Է�һ�����������ж����ж�������ô�п����������
                }
                
                //arr[i][j]��ʾ���Ǵ�i-j�������������ַ����ǲ��ǻ����Ӵ�������ǣ�arr[i][j]���ڻ��Ĵ��ĳ��ȣ�������ǣ���ֵΪ0
                //arr[i+1][j-1]���ǵ������ڽ����䡾i-j�������䡾i+1 - j-1�������䡣���A[i]==A[j]����ô�����i-j�������������
                //��i+1 - j-1��Ҳ�ǻ����ַ����Ļ���arr[i+1][j-1] !=0������ô��i-j������Ҳ�ǻ����ַ�������֮����i-j���Ͳ��ǻ����ַ���
                if(A[i] == A[j] && arr[i+1][j-1] != 0){
                    arr[i][j] = len;
                    max = len;
                }
            }
        }
        
        delete[] arr;//�������õı��ϰ�ߣ��ֶ��ͷ��Լ����ٵĿռ�
        return max;
    }
};