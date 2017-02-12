1,Objective-c 定义的类型
	
	id       对象的引用（指向其数据结构的指针）
	Class  类对象的引用 （指向其数据结构的指针）
	SEL    选标（编译器分配用来区分方法名的编码）//方法名字吧，个人理解
	IMP    指向方法实现的指针，该实现返回id


	BOOL   布尔值，YES或NO. //默认为NO;//其值也可以是TRUE和FALSE,YES<=>TRUE

	nil    空的对象指针，（id）0 //nil means an object pointer is 0. A pointer that doesn't point to anything is nil.
	Nil    空的类指针，（Class）0

	NULL  表示空指针。可以给nil传递消息，这与NULL不一样。 Null means a C pointer is --points to nothing
/*
SEL是“selector”的一个类型，表示一个方法的名字。@selector是一个选择器，里面的参数是一个方法，返回的是SEL类型，也就是方法的名字。
  Objective-C 在编译的时候, 会根据方法的名字(包括参数序列),生成一个用 来区分这个方法的唯一的一个 ID,这个 ID 就是 SEL 类型的。
IMP定义为 id (*IMP) (id, SEL, …)。这样说来， IMP是一个指向函数的指针，这个被指向的函数包括id(“self”指针)，调用的SEL（方法名），再加上一些其他参数。
 
 说白了IMP就是实现方法，给一个方法起个名字，实现动态调用，不用再使用[对象 message]的方式。
*/
2，对象的创建
	TheClass *newObject = [[TheClass alloc] init];
	TheClass *newObject = [TheClass new];//这两种方法是等价的
	//接受消息的类用alloc方法动态地为新实例分配内存，同时返回这个新对象,
	//（alloc makes space in heap for the class's instance variables,also sets them all to zero,
	//so instance variables which are object pointers start out nil）。
	init消息的接收者正是有alloc动态分配的新对象。
	对象必须被初始化以后才能使用，而且只能初始化一次。
	
	NSObject 类中定义的init方法只做了一件事情。实际上它只是简单的返回了self，self是Objective－c中的特殊变量。
	指向调用当前方法的对象。
3，初始化方法,每一个class has a “designated” initializer method.所有的初始化方法都应该返回id类型（not statically typed）。

当处理继承自NSObject的类时，子类的init方法，在初始化本类时，要给super发送init消息。这样确保了初始化过程与继承顺序一致。
//当子类话一个对象，你必须从你的默认初始化方法中，调用你的superclass's designated initializer.(确保它不会初始化失败,如果返回nil，标识初始化失败)
注：（1）如果不是从NSObject继承的类，初始化返回的可能不是调用它的对象。所以要使用以下代码：
-init
{
	if(self = [super init])//判断返回了一个对象还是nil，在任何情况下都可以这么做。
	{
		/*本类特定的初始化由此开始*/
	}
	return self;
}
（2）子类的指定初始化方法应该总是调用其父类的指定初始化方法。

4，回收对象//析构函数
－（void) dealloc
{
	[name release];
	[super dealloc];//当覆盖默认的dealloc功能时，必须确保调用了父类的dealloc方法。
//    析构时先子类，后父类。[super dealloc]一定要放到最后一行。
}