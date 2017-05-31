class Solution {
public:
    int minNumberInRotateArray(vector<int> arr) {
        int left = 0;//指向递增数据的第一个数
        int right = arr.size()-1;//指向递减数据的最后一个数
        int mid = (left + right) >> 1;//中间值
        
        while((right - left) != 1){
            if(arr[left] <= arr[mid]){
                //mid位于递增数据段
                left = mid;
            }
            else//left > mid
            {
                //mid位于递减数据段
                right = mid;
            }
            
            mid = (left + right) >> 1;
        }
        
        return arr[right];
    }
};