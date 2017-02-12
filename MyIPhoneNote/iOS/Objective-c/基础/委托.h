1,委托是一种对象，另一个类的对象会要求委托对象执行它的某些操作。在objective-c中经常用协议来实现 委托对象。
2,委托对象与类别的关系
	委托强调类别的另一种应用：被发送给委托对象的方法可以声明为一个NSObject的类别。
	创建一个NSObject的类别称为“创建一个非正式协议”。
3,委托是一种助手对象，它在特定事件发生时接收其他对象的消息。对象发送请求给它的委托对象，允许其影响自己的行为，
并帮助自己进行决策。
	委托消息会在“感兴趣的”事情发生时发送。对象要成为委托对象就必须实现一个或多个委托方法。

4,use of protocols in IOS:delegates and data sources
委托一般总是定义为 weak @property
@property(nonatomic, weak) id <UISomeObjectDelegate> delegate;

5，
Declare a protocol

@protocol MyDelegate <NSObject>
-(void)oneMethod;
@end

Create a delegate property

@property(assign) id <MyDelegate>myDeleagte;


Implement the protocol

@interface oneClass:UITableViewController<MyDelegate>
@end

Set the delegate



-(void)dealloc{
	viewController.delegate = nil;
	[super dealloc];
}