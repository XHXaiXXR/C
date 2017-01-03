class Zipper {
public:
    string zipString(string iniString) {
        // write code here
        string strtmp;
        int size = iniString.size();
        int i = 0;
        int j = i + 1;
        while(i < size){
            while(iniString[i] == iniString[j]){
                ++j;
            }
            
            strtmp += iniString[i];
            //to_string(num)  直接显示长度数字
            strtmp += to_string(j - i);
            
            i = j;
            j = i + 1;
        }
        
        if(strtmp.size() >= size) return iniString;
        else return strtmp;
    }
};