class Substr {
public:
    vector<bool> chkSubStr(vector<string> p, int n, string s) {
        // write code here
        vector<bool> IsSub(n,false);//��¼״̬���ж�p�еĶ�Ӧ�ַ����Ƿ�Ϊs���Ӵ�
        
        for(int i = 0;i < n;++i){
            string substr = p[i];//p�ж�Ӧ�ַ���
            
            int num = s.find(substr);//����substr�Ƿ���s�У�������ڣ�numΪ����
            if(num >= 0){
                IsSub[i] = true;
            }
        }
        
        return IsSub;
    }
};