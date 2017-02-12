使用NSTimer与iphone的简单动画，实现飘雪效果，这理原理比较简单，就是定时生成一定的雪花图片，
然后使用动画的方式向下漂落（我在其它论坛，看到使用path的方式实现的一个云漂来漂去的效果，
实际也可以用那种方式实现，这实际就是前面说的动画效果的两种应用）。
所以，我们可以在viewDidLoad事件中，增加一个图片及定时器并启动,这里的pic请在头文件中定义。
-(void)viewDidLoad{
	[super viewDidLoad];
	self.flakeImage = [UIImage imageNamed:@"snow.png"];//初始化图片
	//启动定时器，实现飘雪效果
	[NSTimer scheduledTimerWithTimeInterval:(0.2) target:self selector:@selector(onTimer) userInfo:nil repeats:YES];
}
然后再实现定时器定时调用的ontime方法：
-(void)onTimer{
	UIImageView *view = [[UIImageView alloc] initWithImage:pic];//声明一个UIImageView对象，用来添加图片
	view.alpha = 0.5;//设置该view的alpha为0.5，半透明的
	int startX = round(random()%320);//随机得到该图片的x坐标
	int endX = round(random()%320);//这个是该图片移动的最后坐标x轴的
	int scale = round(random()%15)+10;//这个是定义雪花图片的大小
	int speed = 1/round(random()%100)+1;//这个是速度
	view.frame = CGRectMake(startX, -50, scale, scale);//雪花开始的大小和位置
	[self.view addSubview:view];//添加该view
	
	[UIView beginAnimations:nil context:view];//开始动画
	[UIView setAnimationDuration:10*speed];//设定速度
	view.frame = CGRectMake(endX, 500, scale, scale);//设定该雪花最后的消失坐标
	// set a stop callback so we can cleanup the flake when it reaches the
	// end of its animation
	[UIView setAnimationDidStopSelector:@selector(onAnimationComplete:finished:context:)];
	[UIView setAnimationDelegate:self];
	[UIView commitAnimations];
}

- (void)onAnimationComplete:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context {
	
	UIImageView *flakeView = context;
	[flakeView removeFromSuperview];
	// open the debug log and you will see that all flakes have a retain count
	// of 1 at this point so we know the release below will keep our memory
	// usage in check
	NSLog([NSString stringWithFormat:@"[flakeView retainCount] = %d", [flakeView retainCount]]);
	[flakeView release];
	
	
}
