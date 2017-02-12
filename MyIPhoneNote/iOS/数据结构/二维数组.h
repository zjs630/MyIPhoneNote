1,打印二维数组
void printArray()
{
    int x = 2, y = 3;
    int array[x][y]={1,2,3,4,5,6};
    
    for (int i = 0; i<x; i++) {
        for (int j = 0; j<y; j++) {
            printf("%d ",array[i][j]);
        }
        printf("\n");
    }
}
2，用一个for循环打印二维数组.
二维数组在内存中中是按着行存储的，所以可以将二维数组看成一个一维数组。
行号和列号分别为[i/x],[i%y];
void printArray()
{
    int x = 2, y = 3;
    int array[x][y]={1,2,3,4,5,6};

    for (int j = 0; j<x*y; j++) {
        printf("%d ",array[j/y][j%y]);
        if (j ==2) {
            printf("\n");
        }
    }
    printf("\n");
}
