1，assign,copy,retain的区别
	assign:简单赋值，不更改Reference Counting
	copy:建立一个索引计数计为1的对象
	retain：使对象的引用计数器加1，
    
    Readwrite 表示变量可读写。
    Readonly 表示变量只读，你需要手动添加setter函数。

	Copy其实是建立了一个相同的对象，而retain不是：
	比如一个NSString对象，地址为0×1111，内容为@”STR”
	Copy到另外一个NSString之后，地址为0×2222，内容相同，新的对象retain为1，旧有对象没有变化
	retain到另外一个NSString之后，地址相同（建立一个指针，指针拷贝），内容当然相同，这个对象的retain值+1
	也就是说，retain是指针拷贝，copy是内容拷贝。
	
    * 使用assign: 对基础数据类型 （NSInteger，CGFloat）和C数据类型（int, float, double, char, 等等）
    * 使用copy： 对NSString
    * 使用retain： 对其他NSObject和其子类
	
	retain的实际语法为：
	- (void)setName:(NSString *)newName {
		if (name != newName) {
		   [name release];
		   name = [newName retain];
		}
	}
	
2，nonatomic关键字：
atomic是Objc使用的一种线程保护技术，基本上来讲，是防止在写未完成的时候被另外一个线程读取，造成数据错误。
而这种机制是耗费系统资源的，所以在iPhone这种小型设备上，如果没有使用多线程间的通讯编程，那么nonatomic是一个非常好的选择。
//nonatomic means its setter and getter are not thread-safe.

3，There are four ownership qualifiers:

__autoreleasing
__strong
__unsafe_unretained
__weak

Then there are six ownership modifiers for declared property:

assign implies __unsafe_unretained ownership.
copy implies __strong ownership, as well as the usual behavior of copy semantics on the setter.
retain implies __strong ownership.
strong implies __strong ownership.
unsafe_unretained implies __unsafe_unretained ownership.
weak implies __weak ownership.
With the exception of weak, these modifiers are available in non-ARC modes.

4,http://rdcworld-iphone.blogspot.in/2012/12/variable-property-attributes-or.html
//所有的属性信息
01. atomic          //default
02. nonatomic
03. strong=retain   //default
04. weak= unsafe_unretained  //weak跟assign类似，但是当weak指向的对象被deallocated时，会自动的设置为nil。但assign对象不会置为nil。个人理解。zjs
05. retain
06. assign 			//default
07. unsafe_unretained
08. copy
09. readonly
10. readwrite       //default

5，重命名getter方法
.h文件中
@property (nonatomic) BOOL chosen;
。m文件中
@synthesize chosen = _chosen;
//get方法
- (BOOL)chosen
{
    return _chosen;
}
//set方法
- (void)setChosen:(BOOL)chosen
{
    _chosen = chosen;
}
//是否选择，通常我们更愿意getter方法叫做isChosen，而不是chosen。
@property (nonatomic,getter=isChosen) BOOL chosen;//getter=the new name you want
//get方法
- (BOOL)isChosen
{
    return _chosen;
}
//注：重命名设置setter方法，setter=newname
6,为什么说访问属性比直接访问instance variables好
it's good for doing things like balance checking.initializing pointers.updating ui.
在OC中，所有的properties，都是以0开始，对于指针就是nil。

7,outlet collections 中对对象是无序的。

01. atomic
-Atomic means only one thread access the variable(static type).
-Atomic is thread safe.
-but it is slow in performance
-atomic is default behavior
-Atomic accessors in a non garbage collected environment (i.e. when using retain/release/autorelease) will use a lock to
ensure that another thread doesn't interfere with the correct setting/getting of the value.
-it is not actually a keyword.

Example :

@property (retain) NSString *name;

@synthesize name;


02. nonatomic
-Nonatomic means multiple thread access the variable(dynamic type).
-Nonatomic is thread unsafe.
-but it is fast in performance
-Nonatomic is NOT default behavior,we need to add nonatomic keyword in property attribute.
-it may result in unexpected behavior, when two different process (threads) access the same variable at the same time.

Example:

@property (nonatomic, retain) NSString *name;

@synthesize name;

Explain:

Suppose there is an atomic string property called "name", and if you call [self setName:@"A"] from thread A,
call [self setName:@"B"] from thread B, and call [self name] from thread C, then all operation on different thread will be performed serially which means if one thread is executing setter or getter, then other threads will wait. This makes property "name" read/write safe but if another thread D calls [name release] simultaneously then this operation might produce a crash because there is no setter/getter call involved here. Which means an object is read/write safe (ATOMIC) but not thread safe as another threads can simultaneously send any type of messages to the object. Developer should ensure thread safety for such objects.


If the property "name" was nonatomic, then all threads in above example - A,B, C and D will execute simultaneously producing any unpredictable result. In case of atomic, Either one of A, B or C will execute first but D can still execute in parallel.


03. strong (iOS4 = retain )
-it says "keep this in the heap until I don't point to it anymore"
-in other words " I'am the owner, you cannot dealloc this before aim fine with that same as retain"
-You use strong only if you need to retain the object.
-By default all instance variables and local variables are strong pointers.
-We generally use strong for UIViewControllers (UI item's parents)
                                                -strong is used with ARC and it basically helps you , by not having to worry about the retain count of an object. ARC automatically releases it for you 	 when you are done with it.Using the keyword strong means that you own the object.
                                                
                                                Example:
                                                
                                                @property (strong, nonatomic) ViewController *viewController;
                                                
                                                @synthesize viewController;
                                                
04. weak (iOS4 = unsafe_unretained )
-it says "keep this as long as someone else points to it strongly"
-the same thing as assign, no retain or release
-A "weak" reference is a reference that you do not retain.
-We generally use weak for IBOutlets (UIViewController's Childs).This works because the child object only
needs to exist as long as the parent object does.
-a weak reference is a reference that does not protect the referenced object from collection by a garbage collector.
-Weak is essentially assign, a unretained property. Except the when the object is deallocated the weak pointer is automatically set to nil

Example :

@property (weak, nonatomic) IBOutlet UIButton *myButton;

@synthesize myButton;

Explain:

Imagine our object is a dog, and that the dog wants to run away (be deallocated).
Strong pointers are like a leash on the dog. As long as you have the leash attached to the dog, the dog will not run away. If five people attach their leash to one dog, (five strong pointers to one object), then the dog will not run away until all five leashes are detached.
Weak pointers, on the other hand, are like little kids pointing at the dog and saying "Look! A dog!" As long as the dog is still on the leash, the little kids can still see the dog, and they'll still point to it. As soon as all the leashes are detached, though, the dog runs away no matter how many little kids are pointing to it.
As soon as the last strong pointer (leash) no longer points to an object, the object will be deallocated, and all weak pointers will be zeroed out.
When we use weak?
The only time you would want to use weak, is if you wanted to avoid retain cycles
(e.g. the parent retains the child and the child retains the parent so neither is ever released).


05. retain = strong
-it is retained, old value is released and it is assigned
-retain specifies the new value should be sent -retain on assignment and the old value sent -release
-retain is the same as strong.
-apple says if you write retain it will auto converted/work like strong only.
-methods like "alloc" include an implicit "retain"

Example:

@property (nonatomic, retain) NSString *name;

@synthesize name;

06. assign 
-assign is the default and simply performs a variable assignment
-assign is a property attribute that tells the compiler how to synthesize the property's setter implementation
-I would use assign for C primitive properties and weak for weak references to Objective-C objects.

Example:

@property (nonatomic, assign) NSString *address;

@synthesize address;


07. unsafe_unretained

-unsafe_unretained is an ownership qualifier that tells ARC how to insert retain/release calls
-unsafe_unretained is the ARC version of assign.

Example:

@property (nonatomic, unsafe_unretained) NSString *nickName;

@synthesize nickName;


08. copy
-copy is required when the object is mutable.
-copy specifies the new value should be sent -copy on assignment and the old value sent -release.
-copy is  like retain returns an object which you must explicitly release (e.g., in dealloc) in non-garbage collected environments.
-if you use copy then you still need to release that in dealloc.
-Use this if you need the value of the object as it is at this moment, and you don't want that value to reflect any changes made by other 
owners of the object. You will need to release the object when you are finished with it because you are retaining the copy.

Example:

@property (nonatomic, copy) NSArray *myArray;

@synthesize myArray;

09. readonly

-declaring your property as readonly you tell compiler to not generate setter method automatically.
-Indicates that the property is read-only.
-If you specify readonly, only a getter method is required in the @implementation block. If you use the @synthesize directive in 
the @implementation block, only the getter method is synthesized. Moreover, if you attempt to assign a value using the dot syntax, 
you get a compiler error.

Example:

@property (nonatomic, readonly) NSString *name;

@synthesize name;


10. readwrite 
-setter and getter generated.
-Indicates that the property should be treated as read/write.
-This attribute is the default.
-Both a getter and setter method are required in the @implementation block. If you use the @synthesize directive in the implementation 
block, the getter and setter methods are synthesized.

Example:

@property (nonatomic, readwrite) NSString *name;

@synthesize name;

