int PartSort(int *arr, int start, int end)
{
    int left = start;
    int right = end;
    int key = arr[end];   //ѡȡ�ؼ���
    while (left < right)
    {
        while (left < right && arr[left] <= key)  //����ұ�key���ֵ
        {
            ++left;
        }
        while (left < right && arr[right] >= key)  //�ұ��ұ�keyС��ֵ
        {
            --right;
        }
        if (left < right)
        {
            swap(arr[left], arr[right]);  //�ҵ�֮�󽻻����ҵ�ֵ
        }
    }
    swap(arr[right], arr[end]);
    return left;
}
//��һ�������������λ��
int GetMidNumNoSort1(int *arr,int size)
{
    assert(arr);
    int start = 0;
    int end = size - 1;
    int mid = (size - 1) / 2;
    int div = PartSort(arr,start,end);
    while (div != mid)
    {
        if (mid < div)   //���������
            div = PartSort(arr, start, div - 1);
        else    //���������
            div = PartSort(arr, div + 1, end);
    }
    return arr[mid];   //�ҵ���
}