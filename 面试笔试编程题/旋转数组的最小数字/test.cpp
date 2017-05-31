class Solution {
public:
    int minNumberInRotateArray(vector<int> arr) {
        int left = 0;//ָ��������ݵĵ�һ����
        int right = arr.size()-1;//ָ��ݼ����ݵ����һ����
        int mid = (left + right) >> 1;//�м�ֵ
        
        while((right - left) != 1){
            if(arr[left] <= arr[mid]){
                //midλ�ڵ������ݶ�
                left = mid;
            }
            else//left > mid
            {
                //midλ�ڵݼ����ݶ�
                right = mid;
            }
            
            mid = (left + right) >> 1;
        }
        
        return arr[right];
    }
};