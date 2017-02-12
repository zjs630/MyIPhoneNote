1,Adding a gesture recognizer to a UIView from a Controller
//添加平移手势支持
-(void)viewDidLoad{//this is a good place to add Gesture Recognizers.
	UIView *panView = ...;
	UIGestureRecognizer *pangr = [[UIPanGestureRecognizer alloc] initWithTarget:panView action:@selector(pan:)];
	[panview addGestureRecognizer:pangr];
}
//实现pan:方法
－（void）pan:(UIPanGestureRecognizer *)recognizer{
	//当手指在屏幕上平滑的移动时。
	if ((sender.state == UIGestureRecognizerStateChanged)||(sender.state == UIGestureRecognizerStateEnded)) {
		CGPoint translation = [recognizer translationInView:self];
		//for example, if I were a graph and my origin was set by an @property called origin
		self.orign = CGPointMake(self.origin.x+translation.x,self.origin.y + translation.y);
		[recognizer setTranslation:CGPointZero inView:self];
	}
}
//UIPanGestureRecognizer provides 3 methods to help us to implement the target of a gesture recognizer.
-(CGPoint)trnaslationInView:(UIView *)aView;//how far this touch has moved
-(CGPoint)velocityInView:(UIView *)aView;//how fast that thing is moving in each direction , x and y.
-(void)setTranslation:(CGPoint)translation inView:(UIView *)aView;
2,	Other Concrete Gestures

UIPinchGestureRecognizer
@property CGFloatscale; //notethatthisisNOTreadonly(canreseteachmovement) 
@property (readonly) CGFloat velocity; // note that this IS readonly; scale factor per second

UIRotationGestureRecognizer
@property CGFloatrotation; //notethatthisisNOTreadonly;inradians 
@property (readonly) CGFloat velocity; // note that this IS readonly; radians per second

UISwipeGestureRecognizer
This one you “set up” (w/the following) to find certain swipe types, then look for Recognized state @propertyUISwipeGestureRecognizerDirectiondirection; //whatdirectionswipesyouwant
@property NSUInteger numberOfTouchesRequired; // two finger swipes? or just one finger? more?

UITapGestureRecognizer
Set up (w/the following) then look for Recognized state @propertyNSUIntegernumberOfTapsRequired; //singletapordoubletaportripletap,etc. 
@property NSUIntegernumberOfTouchesRequired; //e.g.,requiretwofingertap?

//例如：
UITapGestureRecognizer *tapRec = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(keyTaped:)];
[self addGestureRecognizer:tapRec];
3，//delegate方法

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch {
	if (touch.view == dateControlView) {//如果触摸的view是dateControlView 才去响应手势触摸事件。
		return YES;
	}
    return NO;//不响应
}
4，一个视图，是否可以有两个平移手势呢？