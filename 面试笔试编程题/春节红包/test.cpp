
class Gift {
public:
    int getValue(vector<int> gifts, int n) {
        // write code here
        if(gifts.size() == 0 || gifts.size() != n)
            return 0;
        
        //�ȸ������������  algorithm
        sort(gifts.begin(),gifts.end());
        //ȡ�����м�ֵ
        int value = gifts[n/2];
        //ȡ�м�ֵ���ֵĴ��� algorithm
        int _count = count(gifts.begin(),gifts.end(),value);
        
        //����м�ֵ���ֵĴ������������������һ��
        //�򲻷�����������֮
        if(_count >= (n/2)+1)
            return value;
        else
            return 0;
    }
};