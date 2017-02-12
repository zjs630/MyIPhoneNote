1,自定义颜色：
UIColor *newColor = [[UIColor alloc] initWithRed:(float) green:(float) blue:(float) alpha:(float)];  // 0.0~1.0
2,视图设置背景颜色
self.view.backgroundColor = [UIColor scrollViewTexturedBackgroundColor];
//[self.view setBackgroundColor:[UIColor grayColor]];
3,设置随机颜色

[self.view setBackgroundColor:
 [UIColor colorWithRed:arc4random()%255/255.0
				 green:arc4random()%255/255.0
				  blue:arc4random()%255/255.0 alpha:1.0]];

4,将CGColor转换为UIColor
CGColorSpaceRef colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
float opaqueRed[4] = {1,0,0,1};
CGColorRef red = CGColorCreate(colorSpace, opaqueRed);
UIColor *myRed = [UIColor colorWithCGColor:red];
textView.textColor = myRed;

5，清楚颜色
self.backgroundColor = [UIColor clearColor];
或者
self.backgroundColor = nil;


.color 颜色,主要包括:

blackColor //黑色
darkGray   //暗灰
lightGray  //亮灰
white   
gray  //灰色
red
green
blue
cyan  //蓝绿色,青色
yellow
magenta //品红色
orange 
purple  //紫色
brown  //褐色
clearColor
//也可以用CGColorRef引用来自Core Graphics的颜色