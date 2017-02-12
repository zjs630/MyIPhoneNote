NSObject声明了一个成员变量叫isa。因为NSObject是整个类继承树的根类，
所以所有的对象都会有一个 isa指针，指向创建对象的类结构。
而该isa变量指向该对象的类。
类结构中包含了类定义的成员变量的名字和类型，以及实现了哪些方法。


1,判断某一对象是否能够相应某一选择器
Car *car = [[Car alloc] init];
BOOL a= [car respondsToSelector:@selector(setEngine:)];// 判断car对象是否能够相应setEngine：方法。

2,
-（id）init    在分配内存空间后对对象进行初始化。

-（NSString*）description   返回一个NSString对象来描述接收者。

-（BOOL）isEqual:（id）anObject   当接收者和anObject相等时返回YES，否则返回NO。

3,If you have a SEL,you can ask an object to perform it
using the performSelector: or performSelector:withObject: methods in NSObject 

[object performSelector:oneSel];
[object performSelector:oneSel withObject:coordingnate];

Using makeObjectsPerformSelector: methods in NSArray
[array makeObjectsPerformSelector:oneSel];

4，
- (NSString *)description is a useful method to override (it’s %@ in NSLog()). Example ... NSLog(@“array contents are %@”, myArray);
The %@ is replaced with the results of invoking [myArray description].








