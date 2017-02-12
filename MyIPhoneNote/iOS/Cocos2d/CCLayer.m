/*为了让不同的层可以组合产生统一的效果，这些层基本上都是透明或者半透明的（否则我们只能看到最上面的一个层了）。

层的叠加是有顺序的，处于最上面的层内部的不透明的内容将覆盖下面层的内容。
这个次序同样用于编程模型中的事件响应机制。即最顶层最先接收到系统事件（手指单击屏幕事件），
然后是它的下一层。在事件的传递过程中，如果有一个层处理了该事件，则排在后面的层将不再接收到该事件。

为了方便大家进行游戏开发，Cocos2D-iPhone从技术实现角度提供一些公用层：处理菜单用的菜单层（Menu），
处理颜色显示的颜色层(ColorLayer)等。
每一层又可以包含很多各式各样的内容要素：文本（Label）、链接（HTMLLabel）、精灵（Sprite）、地图等等。
其中，精灵是重点。*/

1，layer的主要功能在于：
a，接收 iPhone 上的屏幕触摸(touch)操作输入。
//CCLayer 子类 accept touch!//默认是不接受触摸的。
self.isTouchEnabled = YES;//must be enabled if you want to eceive touch events!
//This is best done in the class’s init method but it can be changed at any time.
b，接收动力感知(Accelerometer)输入。//默认是不接受accelerometer event的。
self.isAccelerometerEnabled = YES;
// 接收感知事件的委托函数。
-(void) accelerometer:(UIAccelerometer *)accelerometer
didAccelerate:(UIAcceleration *)acceleration {
	CCLOG(@"acceleration: x:%f / y:%f / z:%f", acceleration.x, acceleration.y, acceleration.z);
}
You can use the acceleration parameter to determine 
the acceleration in any of the three directions.
//你可以通过加速参数来决定任意三个方向的加速度值。

3，触摸事件
a. 当手指首次触摸到屏幕时调用的方法:
-(void) ccTouchesBegan:(NSSet *)touches withEvent:(UIEvent*)event
b. 手指在屏幕上移动时调用的方法: 
-(void) ccTouchesMoved:(NSSet *)touches withEvent:(UIEvent*)event
c. 当手指从屏幕上提起时调用的方法: 
-(void) ccTouchesEnded:(NSSet *)touches withEvent:(UIEvent*)event
d. 当触摸事件被取消时调用的方法: 
-(void) ccTouchesCancelled:(NSSet *)touches withEvent:(UIEvent*)event
4，
触摸事件由Cocoa Touch API接收,所以触摸的位置必须被转换为OpenGL的坐标。
以下是一个用来转换坐 标的方法:
-(CGPoint) locationFromTouches:(NSSet *)touches
{

UITouch *touch = [touches anyObject]; 
CGPoint touchLocation = [touch locationInView: [touch view]]; 
return [[CCDirector sharedDirector] convertToGL:touchLocation];
}