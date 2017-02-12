1,#define语句
	用于给符号名称指派程序常量。（没有局部变量的说法，在定义一个名称之后，随后就可以在程序的任何地方使用它。）
例如：
#define TRUE 1		//一般常放在程序的开始，＃import或＃include语句之后。大多数人都放在头文件中。它也可以出现在程序的任何地方。
#define FALSE 0     //语句末尾没有分号

预定义名称不是变量，因此不能为它赋值。

为了区分预定义名称和变量。一般预定义变量都是大写字母组合，或在定义之前加字母k，如：kMaximumValuse

预定义通常称作“宏”

2，常量声明方法一：

#define kDetailKey @"detail text" //定义字符串，和c，c++代码不同，注意要加“@"符号
#define TIMEOUT 60.0 //定义数字
#define degreesToRadian(x) (M_PI*(X)/180.0) //定义函数

常量声明方法二：//使用枚举定义常量
typedef enum {
    kStyle1 = 1,
    kStyle2,
    kStyle3,
}StyleTags;

常量声明方法三：
在.m文件中使用静态常量声明
static NSString *Key = @"keyValue";

3,预处理宏声明
#define NETWORK_SUPPORT 1

定义宏常量，可以在程序代码中简单的进行条件编译。
#if NETWORK_SUPPORT
//some network support code here
#else
//some none network support code here
#endif

4,想去掉所有的NSLog(),可以将其定义为空。
#define NSLog()


5.pch文件
pch原理：pch文件中的内容被所有文件所共有。
pch作用：
（1）存放一些公用的宏。如 #define ABC 10
 (2) 存放一些公用的头文件。如 #import "UIImage+MyImage.h"
 (3) 自定义Log（输出日志）
#ifdef DEBUG //调试
//...表示宏里面的可变参数
//__VA_ARGS__表示函数中的可变参数
#define ZJSLog(...) NSLog(__VA_ARGS__)
#else //发布
//(可以在模拟器中运行release模式下的代码，需要选择Edit Schemo.. -> RUN -> Info ->build configuration ->release)
#define ZJSLog(...)
#endif

pch注意：
（1）如果项目中有C文件，就不要导入OC的代码，
    可以做下判断，防止C文件中导入OC代码。
//因为每个OC文件都会自动定义__OBJC__这个宏，非OC文件不会。
#ifdef __OBJC__

//OC的头文件

#endif

