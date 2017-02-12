1,实现数组的求和，用递归调用。
int GetSum(int *a,int n)
{
    return (n == 0)?0:GetSum(a, n-1)+a[n-1];
}
int main{
    int a[] = {1,2,3};
    int len = sizeof(a)/sizeof(a[0]);
    printf("%d",GetSum(a, len));
}

