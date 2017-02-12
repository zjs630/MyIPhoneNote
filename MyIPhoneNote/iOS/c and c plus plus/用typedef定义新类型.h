1,typedef 声明新的类型名来替代已有的类型名,不能创造新的类型。
2，typedef与#define的区别
相似之处：type int COUNT;和#define COUNT int 的作用都是用COUNT代表int。但事实上，它们使不同的。
不同之处：#define 是在预编译时处理的，它只能作简单的字符串替换，而typedef时在编译时处理的，也并不是简单的字符串替换。
3，符号常量,（宏替换）通常用大写字母拼写。
#define 名字 替换文本
#define LOWER 0

使用：
int abc = LOWER;
4,字符串常量是一个字符数组。在字符串的内部表示中，字符串数组以空字符'\0'结尾。
