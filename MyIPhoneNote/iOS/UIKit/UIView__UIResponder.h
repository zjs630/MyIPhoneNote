1.定义的每个新的视图对象都应该包含initWithFrame:初始化方法。该方法负责在创建
对象时对类进行初始化，使之处于已知的状态。在通过代码创建您的视图实例时，需要
使用这个方法。

- (id)initWithFrame:(CGRect)aRect {
   self = [super initWithFrame:aRect];
   if (self) {
         // setup the initial properties of the view
         ...
      }
   return self;
}
When creating you view with alloc/initWithFrame: in loadView
//一个好的默认选择是：[[UIScreen mainScreen] applicationFrame];
Currently this is the entire screen minus the status bar at the top.
2.检测子视图
//You can loop through subviews of an existing view. This works
//查询某视图全部子视图 [parentView subviews];
especially well if you use the "tag" property on your views.
for (UIImageView *anImage in [self.view subviews])
{
if (anImage.tag == 1)
       { // do something
       }
}
3,触摸事件
/*UIView类是UIResponder的一个子类，因此能够接收用户和视图内容交互时产生的触摸
事件。触摸事件从发生触摸的视图开始，沿着响应者链进行传递，直到最后被处理。视
图本身就是响应者，是响应者链的参与者，因此可以收到所有关联子视图派发给它们的
触摸事件。
	UIView视图的默认用户交互userInteractionEnabled为YES，而UIImageView的这个属性默认为NO。
若设置为NO，用户的触摸事件将会被忽略。*/
处理触摸事件的视图通常需要实现下面的所有方法.
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
4,添加和删除视图
- (void)addSubview:(UIView *)aView; //[parentView addSubview:child];
- (void)removeFromSuperview;	//[childView removeFromSuperView];
	
给子视图标记 settag: 当父视图调用viewWithTag: 可从结构中检索该视图
	
	
	
4，管理视图的顺序
- (void)insertSubview:(UIView *)aView atIndex:(int)index; 
- (void)insertSubview:(UIView *)aView belowSubview:(UIView *)otherView; 
- (void)insertSubview:(UIView *)aView aboveSubview:(UIView *)otherView;
5，可以通过设置hidden property来隐藏视图。
@property BOOL hidden; 
myView.hidden = YES;	// view will not be on screen and will not handle events
6，将超出视图的部分隐藏，不显示。
	@property(nonatomic) BOOL clipsToBounds;              
	myView.clipsToBounds=YES;
6，今天详细看了下视图的具体使用。部分代码如下：
	//创建主视图代码。一般写在视图控制器的loadView中。
	UIView *contentView =  [[UIView alloc] initWithFrame: [[UIScreen mainScreen] applicationFrame]];
	contentView.backgroundColor = [UIColor whiteColor];
	self.view = contentView;
	[contentView release];
	//得到视图的束。
	CGRect apprect = [contentView bounds];
	//添加子视图
	UIView *subview = [[UIView alloc] initWithFrame:CGRectInset(apprect,32.0f,32.0f)];
	//设置背景色
	subview.backgroundColor = [UIColor redColor];
	//[subview setBackgroundColor:[UIColor redColor]];
	//设置透明度
	//[subview setAlpha:value];  (0.0 < value < 1.0)
	[contentView addSubview:subview];
	[subview release];
	
	//自动适应父视图大小：
	aView.autoresizingSubviews = YES;
	aView.autoresizingMask = (UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight);
	
	

	//对父视图中的子视图进行排序
	[parentView bringSubviewToFront:myView2];//将绿色视图移动到最顶端。
	[parentView sendSubviewToBack:myView4];//将黄色视图移动到最低端。
	[parentView exchangeSubviewAtIndex:2 withSubviewAtIndex:0];	//对子视图重新排序

	
	//插入视图
	/*CGRect viewRect5 = CGRectMake(80, 60, 120, 120);
	 UIView *myView5 = [[UIView alloc] initWithFrame:viewRect5];
	 [myView5 setBackgroundColor:[UIColor blackColor]];    
	 [myView insertSubview:myView5 atIndex:3];
	 */
	//移除一个子视图
	//[myView3 removeFromSuperview];//将蓝色视图删除
7，设置视图背景图片//不建议使用，经测试占内存较大。
	self.view.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"image1.png"]];
	//[[myView layer] setBackgroundColor:[[UIColor colorWithPatternImage:[UIImage imageNamed:@"title-bg.png"]] CGColor]];
8,设置视图中层的边框颜色和宽度。
	[[myView layer] setBorderColor:[[UIColor colorWithRed:0.9 green:0.9 blue:0.9 alpha:1] CGColor]];
	[[myView layer] setBorderWidth:1.0];
设置View的圆角：
	// 首先导入QuartzCore.framework  #import <QuartzCore/QuartzCore.h>
	view.layer.cornerRadius = 8;
	view.layer.masksToBounds = YES;
	
	
8，旋转或翻转视图
	[alertView setTransform:CGAffineTransformMakeRotation(3.14159)];//翻转180度
9,缩放视图
	CGAffineTransform transform = CGAffineTransformMakeScale(0.9, 0.9);
	[myTableView setTransform: transform];
	
9,whether a view is on screen.
//check a UIView's window property. If nil, then it's off screen.
for example,this code snippet might appear in a UIViewController somewhere...
	if (self.view.window) {
		...
	}
10.
//	动画效果
//    UIView动画块
//    
//beginAnimatins:context  标记动画块的开始
//    
//    setAnimationCurve 定义动画加速减速的方式
//    
//    setAnimationDuration  以秒为单位指定动画的长度
//    
//    commitAnimations 标记动画的结束
    
	-(void)doChange:(id)sender
	{
		[UIView beginAnimations:nil context:NULL];
		[UIView setAnimationDuration:1]; 
		[UIView setAnimationTransition:([view1 superview]?UIViewAnimationTransitionFlipFromLeft:UIViewAnimationTransitionFlipFromRight)forView:self.view cache:YES];

		if([view1 superview]!= nil)
		{
			[view1 removeFromSuperview];
			[self.view addSubview:view2];
			
		}else {
			
			[view2 removeFromSuperview];
			[self.view addSubview:view1];
		}
		[UIView commitAnimations];
        //简洁写法
        [UIView animateWithDuration:0.3 animations:^{
            self.bgScrollView.contentOffset = CGPointMake(0, 0);
        }];
	}
11、如何把当前的视图作为照片保存到相册中去：
#import <QuartzCore/QuartzCore.h>
	UIGraphicsBeginImageContext(currentView.bounds.size);     //currentView 当前的view
	[currentView.layer renderInContext:UIGraphicsGetCurrentContext()];
	UIImage *viewImage = UIGraphicsGetImageFromCurrentImageContext();
	UIGraphicsEndImageContext();
	UIImageWriteToSavedPhotosAlbum(viewImage, nil, nil, nil);
12,视图从storybord中加载，不会调用view的initWithFrame方法，需要自己添加awakeFromNib；
//此方法效果等同于ini方法。//执行完此方法后，才加载nib文件的视图。
- (void)awakeFromNib
{
    [super awakeFromNib];
    [self setup];//初始化，
}

13.
hitTest的作用:当在一个view上添加一个屏蔽罩，但又不影响对下面view的操作，也就是可以透过屏蔽罩对下面的view进行操作，这个函数就很好用了。


hitTest的用法：将下面的函数添加到UIView的子类中，也就是屏蔽罩类中即可。

-(id)hitTest:(CGPoint)point withEvent:(UIEvent *)event
{
    UIView *hitView = [super hitTest:point withEvent:event];
    if (hitView == self)
    {
        return nil;
    }
    else{
        return hitView;
    }
}

