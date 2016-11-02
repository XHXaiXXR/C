
class Gift {
public:
    int getValue(vector<int> gifts, int n) {
        // write code here
        if(gifts.size() == 0 || gifts.size() != n)
            return 0;
        
        //先给红包数组排序  algorithm
        sort(gifts.begin(),gifts.end());
        //取数组中间值
        int value = gifts[n/2];
        //取中间值出现的次数 algorithm
        int _count = count(gifts.begin(),gifts.end(),value);
        
        //如果中间值出现的次数不超过红包总数的一半
        //则不符合条件，反之
        if(_count >= (n/2)+1)
            return value;
        else
            return 0;
    }
};