1，协议是多个类共享的一个方法列表。协议中列出的方法没有相应的实现，有其他人来实现（比如你）。
协议声明了可以被任何类实现的方法，他仅是定义一个接口，其它的对象负责去实现。协议通常用来指定委托对象的接口。
2，通过在@protocol部分列出一组方法名来定义一个正式协议。
	通过在@interface声明中的类名之后列出用尖括号扩起来的协议名称，对象就可以采用该协议，来实现协议中必须实现的方法。

3,在早期的Objective－C版本中，如果遵守一个协议，就必须实现该协议的所有方法。
	在2.0版本中增加了两个新的协议修饰符：@optional和@required。默认情况下，协议的方法是required类型的。
4，非正式协议，它实际上就是一个分类，列出了一组方法但并没有实现它们。你可以只实现你想要的方法。
非正式协议通常是为根类（NSObject）定义的。有时非正式协议称为抽象协议。
建议用带有@optional方法的正式协议取代非正式协议。
5，如果一个类遵守了某个协议，则它的子类也遵守这个协议。
	协议不引用任何类，它是无类的。任何类都可以遵守协议。
6,协议有点像C＋＋的纯虚函数或者java里的interface。
协议会定义一系列的方法，每个对象都可以引用该协议，引用的同时必须实现协议里要求实现的方法。
协议不同于类和类别，类和类别声明的接口必须在特定的类里面得以实现，而协议声明的接口可以被任何类实现，也可以被多个类实现。
协议的声明跟类接口的声明很像，只是协议没有父类，而且他们不会定义任何实例变量，协议可以指定必须或可选的方法。

7,定义一个协议
@protocol ProtocolName
// list of methods and properties
@end

具体：
@protocol XYZPieChartViewDataSource
- (NSUInteger)numberOfSegments;
- (CGFloat)sizeOfSegmentAtIndex:(NSUInteger)segmentIndex;
@optional
- (NSString *)titleForSegmentAtIndex:(NSUInteger)segmentIndex;
@end

给view设置属性
@interface XYZPieChartView : UIView
@property (weak) id <XYZPieChartViewDataSource> dataSource;
...
@end


在运行时，view检查对象是否实现了某个方法。
NSString *thisSegmentTitle;
if ([self.dataSource respondsToSelector:@selector(titleForSegmentAtIndex:)])
{
    thisSegmentTitle = [self.dataSource titleForSegmentAtIndex:index];
}


//Protocols Inherit from Other Protocols

@protocol MyProtocol <NSObject>
@end






