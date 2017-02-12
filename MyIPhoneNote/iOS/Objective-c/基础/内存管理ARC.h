1，
ARC 是新 LLVM 3.0 编译器的特性,完全消除了手动内 存管理的烦琐。它可以用在iOS4以上版本，而非iOS5新特性。
在你的项目中使用 ARC 是非常简单的,所有的编程都 和以前一样,除了你不再调用 retain, release, autorelease。
启用 ARC 之后,编译器会自动在适当的地方插入适当的 retain, release, autorelease 语句。
你不再需要担心内存管理,因为编译器为你处理了一切。
注意 ARC 是编译器特性,而不是 iOS 运行时特性(除了 weak 指针系统),
它也不是其它语言中的垃圾收集器。
因此 ARC 和手动内存 管理性能是一样的,有些时候还能更加快速,因为编译器还可以执行某些优化。

ARC使用准则

为了比秒程序秒退的尴尬，ARC有效时，我们的代码必须遵循下面的准则。

不能使用 retain/release/retainCount/autorelease
不能使用 NSAllocateObject/NSDeallocateObject
不能使用 NSZone
不能明示调用dealloc
内存管理相关的函数必须遵循命名规则
使用@autoreleasepool代替NSAutoreleasePool
Objective-C 对象不能作为C语言结构体（struct/union）的成员
【id】与【void*】之间需要明示cast
建议使用Objective-C的class来管理数据格式，来代替C语言的struct。不能隐式转换 id 和 void *。

2,“weak”指针,weak 变量仍然指向一个对象,但不是对 象的拥有者:
__weak NSString *weakName = self.textField.text;

当weakName指向的对象发生变化时，weakName 会自动变成 nil,称为 “zeroing” weak pointer。
//当对象释放时会自动设置为 nil
这样阻止了weakName指向已经释放的对象。
3，
__weak NSString *str = [[NSString alloc] initWithFormat:...];
￼NSLog(@"%@", str); // will output "(null)"
￼String 对象没有拥有者(weak 指针),在创建之后就会被立即释放。
Xcode 会给出警告("Warning: assigning retained object to weak variable;object will be released after assignment")

变量默认就是__strong 类型的,因此一般我们对于 strong 变量不加 __strong 修饰
4，
以下代码在 ARC 之前是不可能的,在手动内存管理中,从 Array 中
移除一个对象会使对象不可用,对象不属于 Array 时会立即被释放。
随 后 NSLog()打印该对象就会导致应用崩溃。
id obj = [array objectAtIndex:0];
￼[array removeObjectAtIndex:0];
￼NSLog(@"%@", obj);
￼//因为 obj 变量是一个 strong 指针, 它成为了对象的拥有者,从 Array 中移除该对象也不会导致对象被释放。
5,ARC 只能工作于 Objective-C 对象,如果 应用使用了 Core Foundation 或 malloc()/free(),此时需要你来管理内 存

6,
property 的修饰符总结如下:

• strong:等同于"retain",属性成为对象的拥有者
• weak:属性是 weak pointer,当对象释放时会自动设置为 nil,记住 Outlet
应该使用 Weak
• unsafe_unretained:等同于之前的"assign",只有iOS 4才应该使用,因为iOS4中弱引用__weak不可用。
• copy:和之前的 copy 一样,复制一个对象并创建 strong 关联
• assign:对象不能使用 assign,但原始类型(BOOL、int、float)仍然可以使用
__strong是默认的修饰符。

__weak修饰了一个自动nil的weak引用。

__unsafe_unretained声明了一个不会自动nil的weak引用。当变量被释放，那么它就变成了一个野指针了。

__autoreleasing 用来修饰一个声明为 (id *) 的函数的参数，当函数返回值时被释放。

7,
dealloc 方法
另外启用 ARC 之后,dealloc 方法在大部分时候都不再需要了,因为你不能 调用实例对象的 release 方法,也不能调用[super dealloc]。假如原先的 dealloc 方法只是释放这些对象,Xcode 就会把 dealloc 方法完全移除。你不再 需要手动释放任何实例变量。
如果你的 dealloc 方法处理了其它资源(非内存)的释放,如定时器、Core Foundation 对象,则你仍然需要在 dealloc 方法中进行手动释放,如 CFRelease(), free()等。这时 Xcode 会保留 dealloc 方法,但是移除所有的 release 和[super dealloc]调用。如下:
- (void)dealloc
{
    AudioServicesDisposeSystemSoundID(soundID);
}
8,
除了 strong 和 weak,还有另外一个 unsafe_unretained 关键字,一般你不 会使用到它。声明为 unsafe_unretained 的变量或 property,编译器不会为其 自动添加 retain 和 release。unsafe_unretained 只是为了兼容 iOS 4,因为 iOS 4 没有 weak pointer system。
"unsafe"表示这种类型的指针可能指向不存在的对象。使用这样的指针很可 能导致应用崩溃

unsafe_unretained 指针和 weak 指针不一样的是,当相关联的对象释放时, 指针不会被设置为 nil,因此它实际上指向不存在的对象。有时候你的应用看上 去没有问题,但更大的可能是应用会崩溃。

ARC 主要是 LLVM 3.0 编译器(而不是 iOS 5)的新特性,因此你也可以在 iOS 4.0之后的系统中使用ARC,不过需要注意的是,weak 指针需要iOS5才能使用。 如果你要在 iOS 4 中部署 ARC 应用,你就不能使用 weak property 和__weak 变 量。
既然 iOS 4 不能使用 __weak 和 weak,你就得分别替换
为 __unsafe_unretained 和 unsafe_unretained,记住这些变量在对象被释
放时不会自动设置为 nil,因此如果你不够小心,你的变量就可能会指向不存在 的对象。
9,
如果你需要在 ARC 环境中使用 Block,并且想避免捕获 self,推荐采 用如下代码模式:

__weak id weakSelf = self;
￼block = ^()
{
    ￼￼id strongSelf = weakSelf;
    ￼if (strongSelf != nil)
    ￼{
    ￼// do stuff with strongSelf
    ￼}
￼}
10，为什么iOS中没有GC

我们已经知道ARC并不是GC（垃圾回收）了，那么，为什么iOS中不支持该机能呢？还特意搞出个ARC来。以下是我的分析：

消耗CPU时间的处理尽量避免，以节约电池电量
GC执行的后，会停掉运行时库；这是最大的心结
嵌入式设备本身内存就不是很大，如果GC不停的在后台运行，执行的频率会很高，严重影响性能
UI动画处理是iOS的一大卖点，而有了GC后可能会引起不必要的性能损失

11， ARC之对象转型
//将所有权从Core Fundation转移到Objective-c时，需要使用CFBridgingRelease();
//将所有权从Objective-c转移到Core Fundation时，需要使用CFBridgingRetain();
//当你想将一种类型临时当做另一种类型使用，而不需要转移所有权时，需要使用__bridge.

我们先来看一下ARC无效的时候，我们写id类型转void*类型的写法：

1
id obj = [[NSObject alloc] init];
void *p = obj;
反过来，当把void*对象变回id类型时，只是简单地如下来写，
2
id obj = p;
[obj release];
但是上面的代码在ARC有效时，就有了下面的错误：

error: implicit conversion of an Objective-C pointer
to ’void *’ is disallowed with ARC
void *p = obj;
^

error: implicit conversion of a non-Objective-C pointer
type ’void *’ to ’id’ is disallowed with ARC
id o = p;
^
__bridge

为了解决这一问题，我们使用 __bridge 关键字来实现id类型与void*类型的相互转换。看下面的例子。

id obj = [[NSObject alloc] init];

void *p = (__bridge void *)obj;

id o = (__bridge id)p;
将Objective-C的对象类型用 __bridge 转换为 void* 类型和使用 __unsafe_unretained 关键字修饰的变量是一样的。被代入对象的所有者需要明确对象生命周期的管理，不要出现异常访问的问题。

除过 __bridge 以外，还有两个 __bridge 相关的类型转换关键字：

__bridge_retained
__bridge_transfer
