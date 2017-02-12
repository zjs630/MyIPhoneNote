1,for（表达式1；循环条件；表达式2）{
    //语句；
}

//打印1-200内不能被3整除的数
for（int i = 1；i<200；i++）{
    if(i % 3 != 0){
        NSLog(@"%d不能被3整除",i);
    }
}

用for循环写一个 乘法口诀表

for(int i = 1; i <=9; i++){
    for (int j = 1;j <= i; j++){
        printf(" %d*%d = %d",i,j,i*j);
    }
    printf("\n");
}