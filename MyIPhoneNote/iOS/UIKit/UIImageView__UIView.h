1.设置图片动画。
it can animate a sequence of images
@property (retain) NSArray *animationImages;
@property NSTimeInterval animationDuration;
@property NSInteger animationRepeatCount;
@property BOOL isAnimating;
-(void)startAnimating;
-(void)stopAnimating;

//创建UIImageView，用于显示图片
	UIImageView *imgView = [[UIImageView alloc] initWithFrame:CGRectMake(40.0f, 300.0f, 60.0f, 60.0f)];
	[self addSubview:imgView];
	[imgView release];
	
	// load in the animtion cells for the butterfly
	NSMutableArray *bflies = [[NSMutableArray alloc] init];
	for (int i = 1; i <= 17; i++) {
		NSString *cname = [NSString stringWithFormat:@"bf_%d.png", i];
		UIImage *img = [UIImage imageNamed:cname];
		if (img) [bflies addObject:img];
	}
	
	// begin the animation
	[imgView setAnimationImages:bflies];
	imgView.animationDuration = 0.75f;// all frames will execute in 0.75 seconds
	campFireView.animationRepeatCount = 0;// repeat the annimation forever
	[imgView startAnimating];// start animating
	[bflies release];
2，加载图片
a, 创建一个UIImageView对象
	UIImage *apple = [UIImage imageNamed:@"apple.png"];
	UIImageView *myImgView = [[UIImageView alloc] initWithImage:apple];
或者：
	UIImageView *myImgView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"1.png"]];
b,设置视图的位置
	myImgView.frame = CGRectMake(0, 0, 160, 230);
c,//Provide support for auto-rotation and resizing 
	myImgView.autoresizesSubviews = YES;
	myImgView.autoresizingMask = (UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight);

d,添加到窗口或视图
	[self.view addSubview:myImgView];
3.显示一系列图片的动画。

NSArray *myImages = [NSArray arrayWithObjects: [UIImage imageNamed:@"myImage1.png"], [UIImage imageNamed:@"myImage2.png"],
[UIImage imageNamed:@"myImage3.png"], [UIImage imageNamed:@"myImage4.gif"], nil];

UIImageView *myAnimatedView = [[UIImageView alloc] initWithFrame:[self bounds]];
myAnimatedView.animationImages = myImages;
myAnimatedView.animationDuration = 0.25; // seconds
myAnimatedView.animationRepeatCount = 0; // 0 = loops forever
[myAnimatedView startAnimating];
[self addSubview:myAnimatedView];


4,通过实例化UIimageview子类，来显示图像（位置随机，图片随机）。
a,创建UIImageView子类DragView。
b,设置Imageview 的位置和大小。
CGRect dragRect = CGRectMake(0.0f, 0.0f, 64.0f, 64.0f);
dragRect.origin = randomPoint();//调用自定义函数，让位置随机生成。
DragView *dragger = [[DragView alloc] initWithFrame:dragRect];
c,随机显示图片数组中的一张图片
NSString *whichFlower = [[NSArray arrayWithObjects:@"blueFlower.png",
						  @"orangeFlower.png", nil] objectAtIndex:(random() % 2)];
[dragger setImage:[UIImage imageNamed:whichFlower]];		
//[dragger setUserInteractionEnabled:YES];//设置对象可以与用户交互。
[self.view addSubview:dragger];//将图片显示出来
[dragger release];
5.将5显示的图像可以进行位置的随意拖动。
在DragView类中添加如下代码：
-(void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	// Retrieve the touch point
	CGPoint pt = [[touches anyObject] locationInView:self];
	startLocation = pt;//获得对象的位置
	[[self superview] bringSubviewToFront:self];//将选择的视图置顶
}
-(void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	// Move relative to the original touch point
	CGPoint pt = [[touches anyObject] locationInView:self];//获得移动对
	象的位置
	CGRect frame = [self frame];
	frame.origin.x += pt.x - startLocation.x;
	frame.origin.y += pt.y - startLocation.y;
	[self setFrame:frame];//改变对象的位置，实现移动的效果
}
注：6的产生随机位置的函数代码：（x<256,y<396）
CGPoint randomPoint(){return CGPointMake(random()%256,random()%396)}
7，从网络加载图片，并在UIImageView中显示,之后添加到UIScrollView中。
a,添加 <UIScrollViewDelegate>
b,#define IMAGE_VIEW_TAG 999
c,// return a view that will be scaled. if delegate returns nil, nothing happens
- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView
{
    return [self.view viewWithTag:IMAGE_VIEW_TAG];
}
d,
- (void)loadView
{
	// Download the weather map and load it into the image view
	NSURL *url = [NSURL URLWithString:@"http://hiphotos.baidu.com/kaixinzi999/pic/item/1214f34f0cfc4d40b2de0554.jpg"];
	UIImage *img = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];
	UIImageView *imgView = [[UIImageView alloc] initWithImage:img];
	imgView.tag = IMAGE_VIEW_TAG;
	imgView.userInteractionEnabled = NO;
	
	// Set up the main scroller as our content
	UIScrollView *contentView = [[UIScrollView alloc] initWithFrame: [[UIScreen mainScreen] applicationFrame]];
	[contentView setScrollEnabled:YES];
	[contentView setContentSize:[img size]];
	[contentView setMaximumZoomScale: 2.0f];
	[contentView setMinimumZoomScale: 0.5f];
	[contentView setDelegate:self];
	
	[contentView addSubview:imgView];
	[imgView release];
	
	self.view = contentView;
    [contentView release];
}
8,比较节省内存的加载图片方式（加载后立刻释放图片占用的内存）；
//加载背景图片
NSString *bgImagePath = [[NSBundle mainBundle] pathForResource:@"bg_p" ofType:@"png"];
UIImage *myImage = [[UIImage alloc] initWithContentsOfFile:bgImagePath];
UIImageView *backgroundImageView = [[UIImageView alloc] initWithImage:myImage];
backgroundImageView.frame = CGRectMake(0, 0, 768, 1004);
[self.view addSubview:backgroundImageView];
[myImage release];
[backgroundImageView release];
9,平铺背景图片的方式加载
UIView *myView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 1024, 1024)];
[myView setBackgroundColor:[UIColor colorWithPatternImage:[UIImage imageNamed:@"image-bg.png"]]];
[self.view addSubview:myView];
[myView release];

另一种方式，有机会试试。
UIImage *smallImage = [UIImage imageNamed:@"hc_03.png"];
UIImageView *imageView = [[UIImageView alloc] initWithImage:smallImage];
[imageView setFrame:CGRectMake(0, 20, 320, 44)];
imageView.contentMode = UIViewContentModeScaleToFill;
[self.view addSubview:imageView];
[imageView release];

方式3
UIImage *img2 = [[UIImage imageNamed:@"tianjiaicon.png"] resizableImageWithCapInsets:UIEdgeInsetsMake(5, 5, 5, 5)];
//这种方式，可以拉伸图片
UIImageView *imgview2 = [[UIImageView alloc] initWithImage:img2];
imgview2.frame = CGRectMake(10, 30, 122, 61);
[self.window addSubview:imgview2];
[imgview2 release];


10,使UIimageView的图像旋转：
float rotateAngle = M_PI;
CGAffineTransform transform =CGAffineTransformMakeRotation(rotateAngle);
imageView.transform = transform;

设置旋转的原点：
#import <QuartzCore/QuartzCore.h>
UIImageView *imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"bg.png"]];
imageView.layer.anchorPoint =CGPointMake(0.5, 1.0);

或者 360度 旋转

CABasicAnimation* rotationAnimation;
rotationAnimation = [CABasicAnimation animationWithKeyPath:@"transform.rotation.z"];
rotationAnimation.toValue = [NSNumber numberWithFloat: M_PI * 2.0 ];
rotationAnimation.duration = 1;
rotationAnimation.cumulative = YES;
rotationAnimation.repeatCount = 1;

[self.refreshBtn.layer addAnimation:rotationAnimation forKey:@"rotationAnimation"];
11,设置图片的填充模式

