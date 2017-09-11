int PartSort(int *arr, int start, int end)
{
    int left = start;
    int right = end;
    int key = arr[end];   //选取关键字
    while (left < right)
    {
        while (left < right && arr[left] <= key)  //左边找比key大的值
        {
            ++left;
        }
        while (left < right && arr[right] >= key)  //右边找比key小的值
        {
            --right;
        }
        if (left < right)
        {
            swap(arr[left], arr[right]);  //找到之后交换左右的值
        }
    }
    swap(arr[right], arr[end]);
    return left;
}
//求一个无序数组的中位数
int GetMidNumNoSort1(int *arr,int size)
{
    assert(arr);
    int start = 0;
    int end = size - 1;
    int mid = (size - 1) / 2;
    int div = PartSort(arr,start,end);
    while (div != mid)
    {
        if (mid < div)   //左半区间找
            div = PartSort(arr, start, div - 1);
        else    //左半区间找
            div = PartSort(arr, div + 1, end);
    }
    return arr[mid];   //找到了
}