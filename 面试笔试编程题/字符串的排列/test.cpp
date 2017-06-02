class Solution {
public:
    vector<string> Permutation(string str) {
        vector<string> res;
        if(str.empty())
            return res;
        fun(res,str,0);
        return res;
    }
    
        void fun(vector<string>& res, string str,int pos){
        if(pos==str.size()){
            res.push_back(str);
            return;
        }
        for(int i=pos;i<str.size();i++){
            if(i!=pos && str[i]==str[pos])
                continue;
            swap(str[pos],str[i]);
            fun(res,str,pos+1);
            //swap(str[pos],str[i]);
             
        }
    }
};