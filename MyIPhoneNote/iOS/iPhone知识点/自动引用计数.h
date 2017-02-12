Automatic Reference Counting (ARC), 自动引用计数，是开发Cocoa程序时的一个编译级别的特性，用于自动内存管理。

在XCode 4.2中，使用模板新建一个工程，该工程将使用ARC特性。

如果你的iOS SDK是iOS5 seed release 2，需要做如下修改，才能避免编译时的错误：
● 在System/Library/Frameworks/CoreFoundation.framework/Headers/CFBase.h中, 将:
CFTypeRef CFMakeCollectable(CFTypeRef cf) CF_AUTOMATED_REFCOUNT_UNAVAILABLE;
修改成:
CFTypeRef CFMakeCollectable(CFTypeRef cf);
●在System/Library/Frameworks/Foundation.framework/Headers/NSObject.h中, 将:
return (__bridge_retain CFTypeRef)X;
修改成：
return (__bridge_retained CFTypeRef)X;

使用ARC将让你远离烦人且容易遗漏的retain，release和autorelease等操作。

ARC的工作原理是，在你编译程序时，将内存操作的代码（retain，release或autorelease）自动添加到需要的位置。即底层上使用和Manual Reference Counting（手工引用计数）一样的内存管理机制，但由于XCode自动帮你在编译时添加内存操作的代码，从而简化了编程的工作。

启用ARC，编译选项中需加上-fobjc-arc，不过这个由XCode在创建工程模板时帮你完成。
//不用ARC -fno-objc-arc
4.2以前版本的XCode都不支持ARC。
对操作系统也有要求：Mac OS X v10.6 或 v10.7 (64-bit applications)， iOS4或iOS5。注意：其中Mac OS X v10.6和iOS4不支持weak references(弱引用，后面会说明什么是weak references)。

Xcode 4.2提供了一个名为“Convert to Objective-C Automatic Reference Counting”的工具，在Edit->Convert menu下，可以帮你自动将使用Manual Reference Counting的老代码转换成使用ARC的新代码（例如去掉对retain和release的调用）。

一个使用ARC的代码例子：

@interface Person : NSObject
@property (nonatomic, strong) NSString *firstName;
@property (nonatomic, strong) NSString *lastName;
@property (nonatomic, strong) NSNumber *yearOfBirth;
@property (nonatomic, strong) Person *spouse;
@end

@implementation Person
@synthesize firstName, lastName, yearOfBirth, spouse; @end

注意：不再需要重载dealloc函数,因为没有release操作。（strong的语义后面会介绍。）

例子2：
(void)contrived {
    Person *aPerson = [[Person alloc] init];
    [aPerson setFirstName:@"William"];
    [aPerson setLastName:@"Dudney"];
    [aPerson:setYearOfBirth:[[NSNumber alloc] initWithInteger:2011]];
    NSLog(@"aPerson: %@", aPerson);
}

注意：没有了release操作。

例子3：
(void)takeLastNameFrom:(Person *)person {
    NSString *oldLastname = [self lastName];
    [self setLastName:[person lastName]];
    NSLog(@"Lastname changed from %@ to %@", oldLastname, [self lastName]);
}

注意：ARC会保证 oldLastname引用的对象在NSLog执行结束之前，不会被释放掉。

使用ARC的一些规则：
不能直接调用dealloc方法，不能重载或直接调用retain, release, retainCount, 或 autorelease等方法。
但可以通过@selector(retain), @selector(release)这样的形式调用。
用户自定义的dealloc方法，不能调用[super dealloc] ，编译器会自动帮你添加这个代码。
对Core Foundation-style 的对象，仍可以使用CFRetain, CFRelease等方法。
不能使用NSAllocateObject或NSDeallocateObject去创建对象，请使用alloc方法。
在c语言中的结构体中，不能再使用对象指针。请放弃C结构体，使用Objective-C的类。
id和void*之间没有隐式的类型转换，请使用显式类型转换。
不能使用NSAutoreleasePool，ARC提供了@autoreleasepool语句块。
例如：
@autoreleasepool {
    // Code, such as a loop that creates a large number of temporary objects.
}
不能使用NSZone。
方法和变量的命名不能以“new”开头。

关于对象的生命周期：
weak引用：设置成weak的属性，不会影响对象的生命周期，如果引用的对象已经被释放，引用会指向nil。
strong引用：设置成strong的属性，会影响对象的生命周期。
例如：
@property(strong) MyClass *myObject; 和 @property(retain) MyClass *myObject; 是等效的。

又例如：
@property(weak) MyClass *myObject; 和 @property(assign) MyClass *myObject; 在多数情况下等效，但当instance被释放时，设置为weak的引用会指向nil。

可用的限定词：
__strong， 默认的
__weak
__unsafe_unretained， 和weak的区别是当对象被释放时，引用不指向nil。
__autoreleasing，当方法的参数是id*，且希望方法返回时对象被autoreleased，可以添加__autoreleasing限定词。

使用__weak时要特别小心，例如
NSString __weak *string = [[NSString alloc] initWithFormat:@"First Name: %@", [self firstName]];
NSLog(@"string: %@", string); //此时 string为空，因为weak类型不影响对象的生命周期，对象刚创建就释放了。

其他特性：
使用strong, weak, autoreleasing限定的变量会被隐式初始化为nil。
例如：
- (void)myMethod { NSString *name;
    NSLog(@"name: %@", name); //会输出null
}