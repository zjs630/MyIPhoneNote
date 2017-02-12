1，指针是一种保存变量地址的变量。但数组名不是变量。
int *pa;
int a[10];
pa = &a[0];//指针pa指向数组a的第1个元素a[0];//pa和a具有相同的值。可简写为pa = a;是合法的。但a=pa是不合法的。
pa+1//将指向数组的下一个元素
2，一元运算符&可以取一个对象的地址。
char *p;//ip is a pointer to char
char c = 'a';
p = &c;//把c的地址赋值给变量p，我们称p为“指向”c的指针。地址运算符&只能应用于内存中的对象，即变量与数组元素。

一元运算符*是间接寻址活间接引用运算符。当它作用于指针时，将访问指针所指向的对象。
3，在函数中,形式参数char s[]和char *s是等价的。
计算一个字符串的长度
int strlen(char *s){
    int n;
    for (n=0; *s!='\0'; s++) {
        n++;
    }
    return n;
}
4，char amessage[] = "now is the time";//定义一个数组
char *pmessage = "now is the time";//定义一个指针