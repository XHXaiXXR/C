class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
    	vector<int> max(array.size());
        max[0] = array[0];
        
        int newmax = max[0];
        for(int i = 1;i < array.size();i++){
            if(array[i] + max[i-1] > array[i])
                max[i] = array[i] + max[i-1];
            else
                max[i] = array[i];
            
            if(max[i] > newmax)
                newmax = max[i];
        }
        
        return newmax;
    }
};