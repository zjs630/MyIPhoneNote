1,类变量，即类的每个对象都共享同样的变量。如果一个对象改变了此变量的值=5，其它对象访问到的是变量的值也是5。
我们使用static 关键字来创建类变量。用途：记录特定类创建对象的数目。
@interface TheClass:NSObject
static int count;
+(int)getCount;
@end
@implementation TheClass
-(id)init{
    self = [super init];
    count++;
    return self;
}
+(int)getCount{
    return count;
}
@end

2，外部变量。
在函数外定义变量。
int gNumber = 0;
其它类或文件要使用此变量。需要先声明变量。加extern关键字。
extern int gNumber;
gNumber = 5;

3,实例变量作用域。@protected,@private,@public的区别。
@protected,这个指令后面的实例变量可被该类及任何子类中定义的方法直接访问。这是默认的。
@private，这个指令后面的实例变量可被定义在该类的方法直接访问，但是不能被子类中定义的方法直接访问。
@public,这个指令后面的实例变量可被该类中定义的方法直接访问，也可被其它类的或模块中定义的方法直接访问。

4，oc 语法
Local object variables are automatically initialized to nil.

alocalvariableisallocatedonthe stack, while objects are allocated on the heap.