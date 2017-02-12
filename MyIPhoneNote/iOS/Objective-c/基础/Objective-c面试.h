1，isMemberOfClass和isKindOfClass的区别：
都可以检查一个对象是否是一个类型的成员。//都可以检查对象是否是类成员memberOfClass
不同：isKindOfClass，如果是派生自该类的成员，也将返回true。

2，验证对象是否支持某个方法
BOOL yesOrNO = [objcet respondsToSelector:@selector(print)];
3,验证类是否会创建一个支持特定方法的对象。
BOOL isA = [Class1 instancesRespondToSelector:@selector(print)];
4，实例变量作用域。@protected,@private,@public的区别。
@protected,这个指令后面的实例变量可被该类及任何子类中定义的方法直接访问。这是默认的。
@private，这个指令后面的实例变量可被定义在该类的方法直接访问，但是不能被子类中定义的方法直接访问。
@public,这个指令后面的实例变量可被该类中定义的方法直接访问，也可被其它类的或模块中定义的方法直接访问。
5,didReceiveMemoryWarning函数

//The OS is telling you that memory is low, and you need to free up as much as you can as soon as you can. 
//The idea is that you should free any cached data, unload views that aren't visible, etc. 
6，@dynamic与@synthesize的区别

@property有两个对应的词，一个是@synthesize，一个是@dynamic。如果@synthesize和@dynamic都没写，那么默认的就是@syntheszie var = _var;

@synthesize的语义是如果你没有手动实现setter方法和getter方法，那么编译器会自动为你加上这两个方法。

@dynamic告诉编译器,属性的setter与getter方法由用户自己实现，不自动生成。
（当然对于readonly的属性只需提供getter即可）。假如一个属性被声明为@dynamic var，然后你没有提供@setter方法和@getter方法，编译的时候没问题，但是当程序运行到instance.var =someVar，由于缺setter方法会导致程序崩溃；或者当运行到 someVar = var时，由于缺getter方法同样会导致崩溃。编译时没问题，运行时才执行相应的方法，这就是所谓的动态绑定。