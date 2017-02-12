//
//  数据类型.h

1，char 类型
	char 变量可存储单个字符，将单个字符放入一对单引号中，表示字符常量。

	字符常量和字符串的区别:
	字符常量是放在单引号中的单个字符.//注：字符常量'\n'（即换行符）是合法的字符常量。尽管它有两个字符组成，但编译器将'\n'看为单个字符。
	字符串则是放在双引号中的任意个数的字符。
例如：	
char  charVar = 'Z';
NSLog(@"%c",charVar);

2,BOOL值初始化，默认为NO。
	BOOL my;//NO
	if (my) {
		NSLog(@"Yes");
	}
	else {
		NSLog(@"NO");
	}

3，const关键字把数据标记为常量，以便它不会被修改。
4,
//数据类型：
//整形（int、short int、long int、unsigned int、unsigned short、unsigned long）
NSLog(@"整形:");
NSLog(@"%lu",sizeof(int));//整形4个字节
NSLog(@"%lu",sizeof(short int));//短整形2
NSLog(@"%lu",sizeof(long int));//长整形8
NSLog(@"%lu",sizeof(unsigned int));//无符号整形4
NSLog(@"%lu",sizeof(unsigned short));//无符号短整形2
NSLog(@"%lu",sizeof(unsigned long));//无符号长整形8
//实形（float 、double 、long double）
NSLog(@"实形:");
NSLog(@"%lu",sizeof(float));//浮点形4
NSLog(@"%lu",sizeof(double));//双精度形8
NSLog(@"%lu",sizeof(long double));//长精度形16
//字符型和字符串形
char a='a';
char b=100;
NSLog(@"%c,%c",a,b);
NSLog(@"%i,%i",a,b);
NSLog(@"我是字符串");//字符串形：@“我是字符串”

5, instancetype和id的区别
//instancetype, unlike id, can only be used as the result type in a method declaration.
（1）相同点，都可以作为方法的返回类型。
（2）不同点
①instancetype可以返回和方法所在类相同类型的对象，id只能返回未知类型的对象；
②instancetype只能作为返回值，不能像id那样作为参数。

6, nil和Nil

nil 和C 语言的NULL 相同，在objc/objc.h 中定义。nil 表示一个Objctive-C 对象，这个对象的指针指向空（没有东西就是空），具体定义如下：

#define nil 0 /* id of Nil instance */
首字母大写的Nil 和nil 有一点不一样，Nil 定义一个指向空的类（是Class，而不是对象）。具体定义如下：

#define Nil 0 /* id of Nil class */ 
【例2-18】nil实例。

#import <Foundation/Foundation.h> 
@interface ClassA : NSObject {  
}  
- (void) print;  
@end  
@implementation ClassA  
- (void) print{  
    NSLog (@"I'm ClassA.") ;  
}  
@end  
int main (int argc, const char * argv[]) {  
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];  
    ClassA *classA = [[ClassA alloc]init];  
    classA = nil;  
    if (classA == nil) {  
        NSLog (@"classA is nil") ;  
    }  
    [classA release];  
    [pool drain];  
    return 0;  
} 
【程序结果】

classA is nil 

上面代码创建了一个ClassA 的对象classA，并且正常初始化，这时候，classA 对象不为空，
接着使用一条语句将它设置为空，然后判断该对象是否为nil，如果这个对象为空，就会打印出一条语句到控制台上。

7，nil和NULL的区别
nil用来给对象赋值，NULL则给任何指针赋值，NULL和nil不能互换，


