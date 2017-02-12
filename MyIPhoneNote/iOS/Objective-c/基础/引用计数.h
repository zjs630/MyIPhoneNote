1，当引用计数为0时，release方法会调用对象的dealloc方法来销毁对象。
2，NSString *myString = @"abc";
	以@“...”结构构建的NSString对象是有效常量，向它们发送retain或者release没有用。但是非常量字符串，还是有效的。
NSString *str = [[NSString alloc] init];
NSLog(@"%lu", (unsigned long)[str retainCount]);//18446744073709551615
NSLog(@"%d",[str retainCount]);//-1

3,在ARC中获取引用计数值的函数

NSLog(@"retain count = %d",_objc_rootRetainCount(obj));
4,@autoreleasepool块结束时，释放已注册对象。
例如：
id __strong obj = [[NSObject alloc] init];
@autoreleasepool {
    id __autoreleasing o = obj;
    NSLog(@" retain count = %d in @autoreleasepool",_objc_rootRetainCount(o));
    //retain count = 2
}
NSLog(@" retain count = %d",_objc_rootRetainCount(obj));//retain count = 1
5,
NSObject * per = [[NSObject alloc] init];  //retain count  = 1
[per retain]; //retain count  = 2
[per release]; //retain count  = 1
[per release];//retain count  = 1
NSLog(@"%lu", (unsigned long)[per retainCount]);//retain count  = 1
retainCount的值并不是Obj-C Object的固有属性，而是一个单独存放在一张全局的表里的值。当全局表中不存在符合该对象指针的特征值的项时（例如对象被dispose了），Obj-C Runtime永远返回1。

6.自动释放池是什么,如何工作



当您向一个对象发送一个autorelease消息时，Cocoa就会将该对象的一个引用放入到最新的自动释放池。它仍然是个正当的对象，因此自动释放池定义的作用域内的其它对象可以向它发送消息。当程序执行到作用域结束的位置 时，自动释放池就会被释放，池中的所有对象也就被释放。

1.  ojc-c 是通过一种"referring counting"(引用计数)的方式来管理内存的, 对象在开始分配内存(alloc)的时候引用计数为一,以后每当碰到有copy,retain的时候引用计数都会加一, 每当碰到release和autorelease的时候引用计数就会减一,如果此对象的计数变为了0, 就会被系统销毁.
2. NSAutoreleasePool 就是用来做引用计数的管理工作的,这个东西一般不用你管的.
3. autorelease和release没什么区别,只是引用计数减一的时机不同而已,autorelease会在对象的使用真正结束的时候才做引用计数 减一.
7，autorelease对象什么时候释放？
在没有手加Autorelease Pool的情况下，Autorelease对象是在当前的runloop迭代结束时释放的，而它能够释放的原因是系统在每个runloop迭代中都加入了自动释放池Push和Pop。
