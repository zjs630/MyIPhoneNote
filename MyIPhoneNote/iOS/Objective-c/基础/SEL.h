1,
//SEL is the Objective-C "type" for a selector
//SEL类型的变量，可以通过@selector(方法名)来取得，只要方法名一样，它的值就是一样的，不管这个方法定义于哪个类，
SEL shootSelector = @selector(shoot);
//SEL它不是一个函数指针，实际的类型是const char*
2,If you have a SEL,you can also ask an object to perform it ...


[obj performSelector:shootSelector];
[obj performSelector:shootSelector  withObject:coordinate];

在NSArray中使用makeObjectsperformSelector:方法
[array makeObjectsPerformSelector:shootSelector];
[array makeObjectsPerformSelector:shootSelector withObject:target];

在UIButton中使用
[button addTarget:self action:@selector(digitPressed:) ...];

3,Objective C可以动态添加方法...
用class_addMethod()就行了.
- (void)setUp
{
    [super setUp];
    
    [self addSelector@selector(firstName) toClass:[User class]];
    [self addSelector@selector(lastName) toClass:[User class]];
}

- (void)addSelector:(SEL)selector toClass:(Class)class
{
    NSString *uniqueName = [NSString stringWithFormat:@"%@-%@", NSStringFromClass(class), NSStringFromSelector(selector)];
    SEL sel = sel_registerName([uniqueName UTF8String]);
    IMP theImplementation = [class methodForSelector:sel];
    class_addMethod(class, selector, theImplementation, "v@:@");
}

4，
（1）SEL数据类型：它是编译器运行Objective-C里的方法的环境参数。
（2）IMP数据类型：它其实就是一个 编译器内部实现时候的函数指针。当Objective-C编译器去处理实现一个方法的时候，就会指向一个IMP对象，这个对象是C语言表述的类型。
//http://www.winddisk.com/2012/06/13/objective-c-method-imp/
5，SEL是什么？
SEL不是函数指针，IMP才是，

这个才是函数指针，IMP可以从 对象 & SEL的方法得到：

IMP imp = [self methodForSelector:selector];

SEL是“selector”的一个类型，表示一个方法的名字。比如以下方法：
-[Foo count] 和 -[Bar count] 使用同一个selector，它们的selector叫做count。
在上面的头文件里我们看到，SEL是指向 struct objc_selector的指针，但是objc_selector是什么呢？那么实际上，你使用GNU Objective-C的运行时间库和NeXT Objective-C的运行运行时间库（Mac OS X使用NeXT的运行时间库）时,它们的定义是不一样的。实际上Mac OSX仅仅将SEL映射为C字符串。比如，我们定义一个Foo的类，这个类带有一个- (int) blah方法，那么以下代码：
NSLog (@”SEL=%s”, @selector(blah));
会输出为 SEL=blah。
说白了SEL就是返回方法名。