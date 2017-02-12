1,如何设置UIAccelerometer对象和接收加速度计事件的例子，请参阅文档 iPhone Application Programming Guide中的Accessing Accelerometer Events。

{
	// set up the plumb view
	UIImage* image = [UIImage imageNamed:@"PlumbBob.png"];
	plumbBobView = [[UIImageView alloc] initWithImage:image];

	// move the anchor point to the bottom middle of the metronomeArm bounds, 
	// so rotations occur around that point
	plumbBobView.layer.anchorPoint = CGPointMake(0.5, 0.0);

	// set the frame AFTER setting the ancor point so the view will be in the
	// correct start position.
	plumbBobView.frame = CGRectMake(self.view.frame.size.width/2 - 20, 0, 40, 450);

	[self.view addSubview:plumbBobView];
	[plumbBobView release];

	// Configure and start the accelerometer
	[[UIAccelerometer sharedAccelerometer] setUpdateInterval:(2)];
	[[UIAccelerometer sharedAccelerometer] setDelegate:self];
}

// UIAccelerometerDelegate method, called when the device accelerates.
- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration {
[self rotatePlumbStringToDegree:-acceleration.x* 45];
	NSLog(@"%f",acceleration.x);
}


- (void)rotatePlumbStringToDegree:(CGFloat)positionInDegrees {
    //[plumbBobView.layer removeAllAnimations];
	
    CATransform3D rotationTransform = CATransform3DIdentity;
    rotationTransform = CATransform3DRotate(rotationTransform, DegreesToRadians(positionInDegrees), 0.0, 0.0, 1.0);
    plumbBobView.layer.transform = rotationTransform;
}

@end

CGFloat DegreesToRadians(CGFloat degrees) {return degrees * M_PI / 180;};
CGFloat RadiansToDegrees(CGFloat radians) {return radians * 180/M_PI;};



//================================================================================================



1.访问加速计
UIAccelerometer *accelerometer = [UIAccelerometer sharedAccelerometer];

从加速计获取信息和从Core Location的相似,创建一个符合UIAccelerometerDelegate协议的类,并指定该类的一个实例为加速计的委托


2.更新间隔时间频率
accelerometer.delegate = self;
accelerometer.updateInterval = 1.0f/60.0f;



3.为了接收加速计信息,要实现
accelerometer: didAccelerate: 

要在标签中显示加速度值
NSString *newText = [[NSString alloc] initWithFormat:@"x:%g  y:%g  z:%g",acceleration.x,acceleration.y,acceleration.z];
lable.text = newText;



4. 检测摇动:
-(void)accelerometer:(UIAccelerometer) accelerometer
didAccelerate:(UIAcceleration *)acceleration {
	
	if (fabsf(acceleration.x)>2.0 || fabsf(acceleration.y)>2.0 || fabsf(acceleration.z)>2.0) {
		
		......
	}
}
//2.0表示剧烈摇动,1.5轻微摇动

5,Stopping the event delivery
-(void)disableAccelerameterEvents{
    UIAccelerometer *theAccel = [UIAccelerometer sharedAccelerometer];
    theAccel.delegate = nil;
}




//例子破碎中的代码

- (void) viewDidLoad {
    UIAccelerometer *accel = [UIAccelerometer sharedAccelerometer];
    accel.delegate = self;
    accel.updateInterval = kUpdateInterval;
	
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"glass" ofType:@"wav"];
    AudioServicesCreateSystemSoundID((CFURLRef)[NSURL fileURLWithPath:path], &soundID);
    
    self.fixed = [UIImage imageNamed:@"home.png"];
    self.broken = [UIImage imageNamed:@"homebroken.png"];
    
    imageView.image = fixed;
}


#pragma mark -

- (void)accelerometer:(UIAccelerometer *)accelerometer 
didAccelerate:(UIAcceleration *)acceleration {
    
	if (! brokenScreenShowing) {
        if (acceleration.x > kAccelerationThreshold || acceleration.y > kAccelerationThreshold || acceleration.z > kAccelerationThreshold) {
            
			imageView.image = broken;
            AudioServicesPlaySystemSound (soundID);
            brokenScreenShowing = YES;
        }
    }
}
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    imageView.image = fixed;
    brokenScreenShowing = NO;
}









////////////////////////////////

//小珠子滚动的例子的代码:

//控制器类中:

- (void)viewDidLoad {
    UIAccelerometer *accelerometer = [UIAccelerometer sharedAccelerometer];
    accelerometer.delegate = self;
    accelerometer.updateInterval =  kUpdateInterval;
    [super viewDidLoad];
}
#pragma mark -
- (void)accelerometer:(UIAccelerometer *)accelerometer 
didAccelerate:(UIAcceleration *)acceleration {
    
    [(BallView *)self.view setAcceleration:acceleration];//将加速对象传递到视图中
    [(BallView *)self.view draw]; //调用方法draw
}







//小珠视图类中:

- (id)initWithCoder:(NSCoder *)coder {
    
    if (self = [super initWithCoder:coder]) {
        self.image = [UIImage imageNamed:@"ball.png"];
        self.currentPoint = CGPointMake((self.bounds.size.width / 2.0f) +
                                        (image.size.width / 2.0f), 
                                        (self.bounds.size.height / 2.0f) + (image.size.height / 2.0f));
        
        ballXVelocity = 0.0f;
        ballYVelocity = 0.0f;
    }
    return self;
}
//从nib文件载入视图时,始终不能调用类的init和initWithFrame:方法,nib包含了归档的对象,
//所以任何从nib文件载入的实例都会使用initWithCoder:进行初始化.




- (id)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        // Initialization code
    }
    return self;
}


- (void)drawRect:(CGRect)rect {
    // Drawing code
    [image drawAtPoint:currentPoint];
}


- (void)dealloc {
    [image release];
    [acceleration release];
	
    [super dealloc];
}

#pragma mark -
- (CGPoint)currentPoint {
    
    return currentPoint;
}
- (void)setCurrentPoint:(CGPoint)newPoint {
    previousPoint = currentPoint;
    currentPoint = newPoint;
    
    if (currentPoint.x < 0) {
        currentPoint.x = 0;
        //ballXVelocity = 0;
        ballXVelocity = - (ballXVelocity / 2.0);
    }
    if (currentPoint.y < 0){
        currentPoint.y = 0;
        //ballYVelocity = 0;
        ballYVelocity = - (ballYVelocity / 2.0);
    } 
    if (currentPoint.x > self.bounds.size.width - image.size.width) {
        currentPoint.x = self.bounds.size.width  - image.size.width; 
		//ballXVelocity = 0;
        ballXVelocity = - (ballXVelocity / 2.0);
    }
    if (currentPoint.y > self.bounds.size.height - image.size.height) {
        currentPoint.y = self.bounds.size.height - image.size.height;
        //ballYVelocity = 0;
        ballYVelocity = - (ballYVelocity / 2.0);
    }
    
    CGRect currentImageRect = CGRectMake(currentPoint.x, currentPoint.y, 
                                         currentPoint.x + image.size.width, 
                                         currentPoint.y + image.size.height);
    CGRect previousImageRect = CGRectMake(previousPoint.x, previousPoint.y,
                                          previousPoint.x + image.size.width,  
                                          currentPoint.y + image.size.width);
    [self setNeedsDisplayInRect:CGRectUnion(currentImageRect,
                                            previousImageRect)];
    
}

- (void)draw {
    static NSDate *lastDrawTime;
    
    if (lastDrawTime != nil) {
        NSTimeInterval secondsSinceLastDraw =
        -([lastDrawTime timeIntervalSinceNow]);
        
        ballYVelocity = ballYVelocity + -(acceleration.y *
                                          secondsSinceLastDraw);
        ballXVelocity = ballXVelocity + acceleration.x *
        secondsSinceLastDraw;
        
        CGFloat xAcceleration = secondsSinceLastDraw * ballXVelocity * 500;
        CGFloat yAcceleration = secondsSinceLastDraw * ballYVelocity * 500;
        
        self.currentPoint = CGPointMake(self.currentPoint.x + xAcceleration,
                                        self.currentPoint.y +yAcceleration);
    }
    // Update last time with current time
    [lastDrawTime release];
    lastDrawTime = [[NSDate alloc] init];
    
}



