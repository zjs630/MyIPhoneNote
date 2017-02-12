1,Create with alloc/init 
UINavigationController *myNavController = [[UINavigationController alloc] init];
[myNavController pushViewController:oneViewController animated:YES];
[window addSubview:myNavController.view];

// rootViewController can't be an instance of UITabBarController
// remember to include RootViewController in your class!
RootViewController * rootViewController = [[RootViewController alloc] initWithNibName:@"RootViewController" bundle:nil];

UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:rootViewController];

[self.window addSubview:navigationController.view];

2，设置标题：//Adding a title to a navigation controller
 self.title = @"My View Controller";
//titleTextAttributes 它是一个设置title的字体的导航栏属性。
//self.navigationController.navigationBar.titleTextAttributes：用于设置title部分的字体（颜色、大小、格式）。
//self.navigationController.navigationBar.titleTextAttributes = @{UITextAttributeTextColor : [UIColor redColor],NSFontAttributeName:[UIFont systemFontOfSize:20.0]};

3，//Showing the navigation toolbar
self.navigationController.toolbarHidden = NO;  
// hide the navigation bar  
// use setToolbarHidden:animated: if you need animation  
4，//Changing the Navigation Bar background color
self.navigationController.navigationBar.tintColor = [UIColor   
													 colorWithRed:102.0/255   
													 green:52.0/255   
													 blue:133.0/255   
													 alpha:1];
5，//Changing the Navigation Bar style
Default style is UIBarStyleDefault, but you can use UIBarStyleBlack and
eventually set the translucent propriety to YES.

self.navigationController.navigationBar.barStyle = UIBarStyleBlack; 
self.navigationController.navigationBar.translucent = YES;  
6，//Using a Navigation Bar background image

To use a background image for you navigation bar, 
you need to subclass UINavigationBar and declare your own drawRect method. 
You can add this code on its own file or at the top of your application delegate 
(after the import declarations):
@implementation UINavigationBar (UINavigationBarCategory)

- (void)drawRect:(CGRect)rect
{
	UIImage *image = [UIImage imageNamed:@"bg.png"];
	
	[image drawInRect:rect];
}

@end

7，//Adding items to the Navigation Toolbar
UIBarButtonItem *flexibleSpace = [[UIBarButtonItem alloc] 
								  initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
								  target:nil 
								  action:nil];

UIBarButtonItem *item1 = [[UIBarButtonItem alloc] 
						  initWithBarButtonSystemItem:UIBarButtonSystemItemAdd 
						  target:self 
						  action:nil];

UIBarButtonItem *item2 = [[UIBarButtonItem alloc] 
						  initWithBarButtonSystemItem:UIBarButtonSystemItemEdit
						  target:self 
						  action:nil];


UIBarButtonItem *item3 = [[UIBarButtonItem alloc] 
						  initWithBarButtonSystemItem:UIBarButtonSystemItemOrganize
						  target:self 
						  action:nil];

NSArray *items = [NSArray arrayWithObjects:item1, flexibleSpace, item2, flexibleSpace, item3, nil];

self.toolbarItems = items;

[item1 release];
[item2 release];
[item3 release];

1，为导航栏添加右侧按钮，并设置动作。
	// Add an action button
	self.navigationItem.rightBarButtonItem = [[[UIBarButtonItem alloc]
											 initWithTitle:@"Do It" 
											 style:UIBarButtonItemStylePlain 
											 target:self 
											 action:@selector(presentSheet)] autorelease];
//返回
self.navigationItem.leftBarButtonItem = [[[UIBarButtonItem alloc]
                                          initWithTitle:@"返回"
                                          style:UIBarButtonItemStylePlain
                                          target:self
                                          action:@selector(back)] autorelease];

2,设置navigationItem的标题
	self.navigationItem.titleView = [[[UILabel alloc] initWithFrame:CGRectMake(0.0f, 4.0f, 320.0f, 36.0f)] autorelease];
	// Prepare the Navigation Item
	[(UILabel *)self.navigationItem.titleView setText:@"Font Families"];
	[(UILabel *)self.navigationItem.titleView setBackgroundColor:[UIColor clearColor]];//清除背景色
	[(UILabel *)self.navigationItem.titleView setTextColor:[UIColor whiteColor]];//设置字体的颜色
	[(UILabel *)self.navigationItem.titleView setTextAlignment:UITextAlignmentCenter];//文本居中
	[(UILabel *)self.navigationItem.titleView setFont:[UIFont boldSystemFontOfSize:[UIFont systemFontSize]]];
3，常用方法和属性：
self.navigationItem.leftBarButtonItem //左边栏项目
self.navigationItem.rightBarButtonItem //右边栏项目
self.navigationItem.backBarButtonItem //后退栏项目//创建的按钮带有左箭头，只有再视图控制器不是跟控制器时，回退按钮才会显示。
self.navigationItem.hidesBackButton //隐藏后退按钮（YES or NO）

self.navigationController.view.frame = CGRectMake(0, 0, 768, 44);//设置视图的大小
self.navigationController.navigationBarHidden=YES;//隐藏导航栏
self.navigationController.view.hidden=YES;//隐藏导航栏，作用同上
3，下是一些“关键方法”
pushViewController:viewController animated:BOOL//（加载视图控制器）
– 添加指定的视图控制器并予以显示，后接：是否动画显示

popViewControllerAnimated:BOOL（弹 出当前视图控制器）
– 弹出并向左显示前一个视图

popToViewController:viewController animated:BOOL（弹出到指定视图控制器）
– 回到指定视图控制器， 也就是不只弹出一个

popToRootViewControllerAnimated:BOOL（弹 出到根视图控制器）
– 比如说你有一个“Home”键，也许就会实施这个方法了。

setNavigationBarHidden:BOOL animated:BOOL（设置导航栏是否显示）
– 如果你想隐藏导航栏，这就是地方了。参照Picasa的WebApp样式
// hide the navigation bar  
// use setNavigationBarHidden:animated: if you need animation  
self.navigationController.navigationBarHidden = YES;  

4，实现 pushViewController:animated:的不同页面转换特效
a, 首先要明确的是,不使用pushViewController的默认动画,所以在调用这个函数时,要将animated设置为NO.
b, 使用普通的来CATransition实现转换效果,代码如下:

	CATransition *animation = [CATransition animation];
	[animation setDuration:0.3];
	[animation setType: kCATransitionMoveIn];
	[animation setSubtype: kCATransitionFromTop];
	[animation setTimingFunction:[CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionDefault]];
	
	[self.navigationController pushViewController:m_poseAddIssueViewController animated:NO];

	[self.navigationController.view.layer addAnimation:animation forKey:nil];
	

3.5 导航栏风格:
UIBarStyleDefault //默认风格,灰色背景,白色文字
UIBarStyleBlackOpaque //纯黑色,白色文字
UIBarStyleBlackTranslucent //透明黑色,白色字体

//给导航栏添加分段控件
UISegmentedControl *sgementedControl = [[UISegmentedControl alloc] initWithItems:nil];
segmentedControl.segmentedControlStyle = UISegmentedControlStyleBar;

[segmentedControl insertSegmentWithTitle:@"all" atIndex:0 animated:NO];
[segmentedControl insertSegmentWithTitle:@"missed" atIndex:1 animated:NO];

self.navigationItem.titleView = segmentedControl;



//更新导航栏右键按钮状态
- (void)updateRightBarButtonItemState {
	// Conditionally enable the right bar button item -- it should only be enabled if the book is in a valid state for saving.
    self.navigationItem.rightBarButtonItem.enabled = [book validateForUpdate:NULL];
}
	
	
//////////////////

3.将分段控件添加到导航项的标题视图中
   NSArray *buttonNames = [NSArray arrayWithObjects:@"One", @"Two",
@"Three", @"Four", @"Five", nil];
   UISegmentedControl* segmentedControl = [[UISegmentedControl alloc]
initWithItems:buttonNames];
   //segmentedControl.momentary = YES;
   [(UITextView *)self.view setText:@""];

   segmentedControl.autoresizingMask = UIViewAutoresizingFlexibleWidth;
   segmentedControl.segmentedControlStyle = UISegmentedControlStyleBar;
   segmentedControl.frame = CGRectMake(0, 0, 400, 30);
   [segmentedControl addTarget:self action:@selector(segmentAction:)
forControlEvents:UIControlEventValueChanged];

   self.navigationItem.titleView = segmentedControl;
   [segmentedControl release];
-(void) segmentAction: (id) sender
{
       //根据选择分段的索引判断按的是哪个按钮，并显示
	switch([sender selectedSegmentIndex] + 1)
	{
		case 1: [(UITextView *) self.view setText:@"\n\nOne"];
			break;
		case 2: [(UITextView *) self.view setText:@"\n\nTwo"];
			break;
		case 3: [(UITextView *) self.view setText:@"\n\nThree"];
			break;
		case 4: [(UITextView *) self.view setText:@"\n\nFour"];
			break;
		case 5: [(UITextView *) self.view setText:@"\n\nFive"];
			break;
		default: break;
	}
}

4.直接加载Nib文件，（通过导航栏的右侧按钮点击）。
a, 在导航栏右侧加ButtonItem，触发加载nib操作，在视图控制器子类中代码：
- (void)loadView
{
	self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc]
											initWithTitle:@"Do It"
											style:UIBarButtonItemStylePlain
											target:self
											action:@selector(doit)];
}
b, 加载nib文件代码。
- (void) doit
{
	NSArray *niblets = [[NSBundle mainBundle] loadNibNamed:@"sample"
owner:self options:NULL];
	for (id theObject in niblets)
	{
		if ([theObject isKindOfClass:[UIViewController class]])
			[self.navigationController
pushViewController:theObject animated:YES];
	}
}

5,让导航栏返回按钮消失。
[self.navigationItem setHidesBackButton:YES];
//self.navigationItem.leftBarButtonItem = nil;//这个好像不管用。
6，//Changing Navigation Bar back button text
self.navigationController.navigationBar.backItem.title = @"Custom";

7，Navigation stack是一个后进先出的custom view controller集合，由navigation controller负责管理。第一个被加入的会称为root view controller并且永远不会被移出stack。

