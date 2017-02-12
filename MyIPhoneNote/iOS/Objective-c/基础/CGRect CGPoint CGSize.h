//三个结构体: 
CGPoint: 点坐标,分别对应屏幕或视图上的xy坐标
CGSize:一个矩形的大小,xy分别对应width和height
CGRect:结合了上面两个,表示矩形在屏幕的大小和位置

//一些相关函数
BOOL isEqual = CGRectEqualToRect(rect1,rect2); //比较两个CGRect

BOOL containPoint = CGRectContainPoint(rect,point); //确定点是否包含在一个CGRect在内

BOOL doesIntersect = CGRectIndersectsCGRect(rect1,rect2);//确定两个CGRect是否交错


//边缘和中心检测
CGRectGetMinX  返回矩形左边缘的坐标

CGRectGetMinY 返回矩形底部边缘的坐标

CGRectGetMidX 返回矩形中心的x坐标

CGRectGetMaxX 矩形右边边缘的坐标

CGRectGetMaxY 矩形顶部边缘的坐标


8.关于CGRect
在代码中定义矩形 CGRectMake (origin.x,origin.y,size.width,size.height)
CGRect imgRect = CGRectInset(self.bounds, self.bounds.size.width *0.2, self.bounds.size.height *0.2);

把CGRect结构转变为格式化字符串 NSStringFromCGRect(someCGRext)
由字符串恢复出矩形 CGRectFromNSString(aString)
创建较大或较小的矩形(中心点相同),正的内嵌值表示较小的矩形,负表较大的;
判断两矩形是否重叠交叉 CGRectIntersectsRect(rect1,rect2)
高宽为零,位于(0,0)的矩形常量 CGRectZero

创建点或大小 CGPointMake(x,y) 或 CGSizeMake(width,height)

Quartz从左下方建立坐标系,而UIView的原点位于左上方;


横向:480*320,纵向320*480,顶部的标准状态栏占20像素,导航栏44像素;
查询状态栏边框 [[UIApplacation sharedApplication] statusBarFrame];
隐藏状态栏 [[UIApplication sharedApplication] setStatusBarHidden:YES animated:YES];或修改Info.plist;
仅在横向下运行程序 [[UIApplicatiion sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeRight];

UIScreen对象代表物理屏幕([UIScreen mainScreen])

CGRect
CGRect frame = CGRectMake (origin.x, origin.y, size.width, size.height)；矩形
NSStringFromCGRect(someCG) 把CGRect结构转变为格式化字符串；
CGRectFromString(aString) 由字符串恢复出矩形；
CGRectInset(aRect) 创建较小或较大的矩形（中心点相同），＋较小  －较大
CGRectIntersectsRect(rect1, rect2) 判断两矩形是否交叉，是否重叠
CGRectZero 高度和宽度为零的／位于（0，0）的矩形常量

CGPoint & CGSize
CGPoint aPoint = CGPointMake(x, y);
CGSize aSize = CGSizeMake(width, height);

NSLog(@"%@",NSStringFromCGRect(titleField.frame));
