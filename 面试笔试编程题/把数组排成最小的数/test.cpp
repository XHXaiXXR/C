class Solution {
public:
     static bool comp(int a,int b){
            string A = "";
            string B = "";
            
            //ab > ba --> a > b
            //ba < ba --> a < b
            //ab == ba -->a == b
            //a = "3"   b = "31"   "331" > "313"  --> a > b
            
            A += to_string(a);
            A += to_string(b);
            
            B += to_string(b);
            B += to_string(a);
            
            return A < B;
    }
    string PrintMinNumber(vector<int> numbers) {
        
        sort(numbers.begin(), numbers.end(), comp);
        string str = "";
        for(int i = 0;i < numbers.size();i++){
            str += to_string(numbers[i]);
        }
        
        return str;
    }
};