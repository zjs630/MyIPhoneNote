8.实现一个图片视图，通过触摸渐显渐隐的效果。
a.创建一个基于视图的应用程序。
b.创建一个UIView的子类，名为ToggleView。主要代码如下：

- (id)initWithFrame:(CGRect)frame {//初始化代码：加载图像
	
	if ((self = [super initWithFrame:frame])) {
		
		isVisible = YES;
		
		UIImageView *imgView = [[UIImageView alloc] initWithFrame:[[UIScreen
																	mainScreen] applicationFrame]];
		
		imgView.image = [UIImage imageNamed:@"alphablend.png"];
		
		imgView.tag = 5;//设置图像标记号
		
		//imgView.userInteractionEnabled = NO;
		
		[self addSubview:imgView];
		
		[imgView release];
		
	} 
	
	return self;
	
}

-(void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event

{
	
	//UITouch *touch = [touches anyObject];
	
	//if([touch phase] != UITouchPhaseBegan) return;
	
	isVisible = !isVisible;
	
	//perform the fade out or fade in
	
	CGContextRef context = UIGraphicsGetCurrentContext();
	
	[UIView beginAnimations:nil context:context];
	
	[UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
	
	[UIView setAnimationDuration:1.0];
	
	[[self viewWithTag:5] setAlpha:(float)isVisible];
	
	[[self superview] bringSubviewToFront:self];
	
	[UIView commitAnimations];
	
}

c.再视图控制器类中，ToggleView的对象，将ToggleView对象添加到窗口。

ToggleView *contentView = [[ToggleView alloc] initWithFrame:[[UIScreen
															  mainScreen] applicationFrame]];

self.view = contentView;

[contentView release];
