1，假设某个controller的一个view上有一个button。触摸屏幕，触摸事件会按着响应者链传递。
触摸按钮，触摸事件的响应者链是，button->view->ViewController->UIWindow->UIApplication->AppDelegate

如果传递到AppDelegate，没有响应触摸事件，则此事件会被系统丢弃。

2.查看响应者链
NSLog(@"%@",sender.nextResponder);
NSLog(@"%@",sender.nextResponder.nextResponder);


3.第一响应者，该响应者通常是用户当前正在交互的对象。第一响应者是响应者链的开始，还有其他响应者。
只要超类是UIResponder的类，都可以是响应者。
第一个响应者几乎总是视图或控件，并且首先对事件进行响应。

第一响应者将事件传递给它的视图控制器(如果有的话),然后是它的父视图。
4.
如果第一个响应者不处理某个特殊事件，则他会将该事件传递到响应者链的下一级。

如果该链中的下一个对象响应此特殊事件，则他通常会处理该事件，这将停止该事件沿着响应者链向前传递。

如果事件通过整个响应者链并且没有对象处理该事件，则丢弃该事件。



5.转发事件：保持响应者链的活动状态

//在某些情况下，如果某个响应者只对某个事件进行部分处理，则该响应者将采取操作，并将该事件转发给链中的下一个响应者。但通常不会发生这种情况。正常情况下，当对象响应事件时，即到达了该事件的行尾。


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [super touchesBegan:touches withEvent:event];//传递触摸事件
    NSLog(@"touchesBegan");
}

6，
以一个按钮点击事件为例：
当用户点击按钮时，iphone OS获取到了 “单击”，这一事件的发生，记录了“单击”这一操作的所有信息以UITouch和UIEvent的形式存储在当前应用程序的事件队列中。负责管理应用程序的UIApplication单件将对象将事件从队列的顶部取出，然后派发下去到焦点窗口即拥有当前用户事件焦点的窗口（当前应用程序窗口UIWindow），由uiwindow对象将它再发送给第一响应者进行处理，第一响应者就是当前的button。
UIResponser是所有相应对象的基类。

7。http://www.cnblogs.com/zhw511006/p/3517248.html

一个iOS应用中，在一块屏幕上通常有很多的UI控件，也就是有很多的View，那么当一个事件发生时，如何来确定是哪个View响应了这个事件呢，接下来我们就一起来看看。

寻找hit-test view

什么是hit-test view呢？简单来说就是你触发事件所在的那个View，寻找hit-test view的过程就叫做Hit-Testing。
