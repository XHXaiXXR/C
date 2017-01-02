class Different {
public:
    bool checkDifferent(string iniString) {
        // write code here
        vector<int> count(256,0);
        
        for(int i = 0;i < iniString.size();++i){
            count[iniString[i]]++;
        }
        for(int i = 0;i < count.size();++i){
            if(count[i] > 1) return false;
        }
        
        return true;
    }
};