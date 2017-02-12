1,UIScrollView的使用
a，在UIViewController类中，添加声明
	UIScrollView *scrollView1;
b,设置属性（略）
d,

const CGFloat kScrollObjHeight	= 199.0;
const CGFloat kScrollObjWidth	= 280.0;
const NSUInteger kNumImages		= 5;


- (void)viewDidLoad {
	[scrollView1 setBackgroundColor:[UIColor blackColor]];//设置背景颜色
	[scrollView1 setCanCancelContentTouches:NO];
	scrollView1.indicatorStyle = UIScrollViewIndicatorStyleDefault;//设置滑块儿的样式
	scrollView1.clipsToBounds = YES;//将超出滚动视图的部分剪掉		// default is NO, we want to restrict drawing within our scrollview
	scrollView1.scrollEnabled = YES;//default is YES,若设置为NO，视图的内容将不能滚动，使用scrollView的意义将不大。
	
	// pagingEnabled property default is NO, if set the scroller will stop or snap at each photo
	// if you want free-flowing scroll, don't set this property.
	scrollView1.pagingEnabled = YES;//实现翻页的效果

	// load all the images from our bundle and add them to the scroll view
	NSUInteger i;
	for (i = 1; i <= kNumImages; i++)
	{
		NSString *imageName = [NSString stringWithFormat:@"image%d.jpg", i];
		UIImage *image = [UIImage imageNamed:imageName];
		UIImageView *imageView = [[UIImageView alloc] initWithImage:image];
		
		// setup each frame to a default height and width, it will be properly placed when we call "updateScrollList"
		CGRect rect = imageView.frame;
		rect.size.height = kScrollObjHeight;
		rect.size.width = kScrollObjWidth;
		imageView.frame = rect;
		imageView.tag = i;	// tag our images for later use when we place them in serial fashion
		[scrollView1 addSubview:imageView];
		[imageView release];
	}
	
	[self layoutScrollImages];	// now place the photos in serial layout within the scrollview
	
//    [scrollView1 setContentOffset:CGPointMake(scroviewposition, 0)]; //设置可视区域。

}


- (void)layoutScrollImages
{
	UIImageView *view = nil;
	NSArray *subviews = [scrollView1 subviews];
	
	// reposition all image subviews in a horizontal serial fashion
	CGFloat curXLoc = 0;
	for (view in subviews)
	{
		//NSLog(@"%@",view);
		if ([view isKindOfClass:[UIImageView class]] && view.tag > 0)
		{
			CGRect frame = view.frame;
			frame.origin = CGPointMake(curXLoc, 0);
			view.frame = frame;
			
			curXLoc += (kScrollObjWidth);
		}
	}
	
	// set the content size so it can be scrollable
	[scrollView1 setContentSize:CGSizeMake((kNumImages * kScrollObjWidth), [scrollView1 bounds].size.height)];
}
2,在使用 UIScrollView 分页的时候我们如何确定当前是第几页？
首先需要开启分页设置
scrollView.pagingEnabled = YES;
然后我们在委托的类上实现以下方法
- (void) scrollViewDidScroll:(UIScrollView *)sender {
	// 得到每页宽度
	CGFloat pageWidth = sender.frame.size.width;
	// 根据当前的x坐标和页宽度计算出当前页数
	int currentPage = floor((sender.contentOffset.x - pageWidth / 2) / pageWidth) + 1;
}
3,
UIScrollView 内部有一个timer,会来截取event . 当发生touch事件以后, 
如果此UIScrollView的 delaysContentTouches == YES. 那么这个touch
会被UIScrollView拦截,150ms后,判断手指有没有移动,移动则拦截此事件,不让其传
向inner view,并且开始UIScrollView的划动. 如果没有动,
则将此touch传给inner view,不划动.

4,
-(void) scrollViewDidScroll:(UIScrollView *)scrollView{
    NSLog(@"正在滑动中...");
}

//用户直接滑动NSScrollView，可以看到滑动条
-(void) scrollViewDidEndDecelerating:(UIScrollView *)scrollView {
	
}

// 通过其他控件触发NSScrollView滑动，看不到滑动条
- (void) scrollViewDidEndScrollingAnimation:(UIScrollView *)scrollView {
	
}

5.iOS7下scrollview的位置偏移问题，
self.automaticallyAdjustsScrollViewInsets = NO;

6,iOS6下scrollview的contentOffset问题，

@property (assign, nonatomic) CGPoint offSet; //for iOS 6

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    if (iOSVersion()<7.0) {
        self.shopScrollView.contentOffset = CGPointZero;
    }
}
- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    if (iOSVersion()<7.0) {
        self.offSet = self.shopScrollView.contentOffset;
    }
}
- (void)viewWillLayoutSubviews
{
    [super viewWillLayoutSubviews];
    
    if (iOSVersion() < 7.0f) {
        self.shopScrollView.contentOffset = self.offSet;
    }
}
