class GrayCode {  
public:  
    vector<string> getGray(int n) {  
        // write code here  
        vector<string> gray;  
          
        if(n == 1){  
            gray.push_back("0");  
            gray.push_back("1");  
            return gray;  
        }  
          
        vector<string> tmp = getGray(n-1);  
        for(int i = 0;i < tmp.size();i++){  
            gray.push_back("0" + tmp[i]);  
        }  
          
        for(int i = tmp.size()-1;i >= 0;i--){  
            gray.push_back("1" + tmp[i]);  
        }  
          
        return gray;  
    }  
};  