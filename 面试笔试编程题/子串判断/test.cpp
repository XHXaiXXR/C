class Substr {
public:
    vector<bool> chkSubStr(vector<string> p, int n, string s) {
        // write code here
        vector<bool> IsSub(n,false);//记录状态，判断p中的对应字符串是否为s的子串
        
        for(int i = 0;i < n;++i){
            string substr = p[i];//p中对应字符串
            
            int num = s.find(substr);//查找substr是否在s中，如果不在，num为负数
            if(num >= 0){
                IsSub[i] = true;
            }
        }
        
        return IsSub;
    }
};