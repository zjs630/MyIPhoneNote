


4.2 处理多触摸事件

//UITouch的一些属性
timestamp   //提供相对于前一事件的时间戳
phase      //正在发生的触摸事件的阶段类型
UITouchPhaseBegan //当触摸表面时发送
UITouchPhaseMoved //当手指在屏幕上移动时
UITouchPhaseEnded  //当手指在屏幕上移走时发送
UITouchPhaseStationary //当手指一直在屏幕上从未移动
UIPhaseCancelled      //当系统取消手势时
tapCount           //点触的次数

locationInView:   //返回一个点结构体,当前事件的位置的坐标
previousLocationInView:  //返回事件发起点的坐标


//UIEvent对象支持下列方法:

-(NSSet *)allTouches;  //返回程序内全部触摸事件的集合

-(NSSet *)touchesForWindow:(UIWindow *)window;  //返回指定的window内的所有触摸

-(NSSet *)touchesForView;


//一些事件处理方法

-(void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;

-(void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;

-(void) touchesEnd:(NSSet *) touches withEvent:(UIEvent *)event;

-(void) touchesCancelled:(NSSet *) touches withEvent:(UIEvent *) event;





1,UITouch中的重要内容
@property(nonatomic,readonly) NSTimeInterval	timestamp;
@property(nonatomic,readonly) UITouchPhase	phase;
@property(nonatomic,readonly) NSUInteger	tapCount;
@property(nonatomic,readonly,retain) UIWindow	*window;
@property(nonatomic,readonly,retain) UIView	*view;
- (CGPoint)locationInView:(UIView *)view;
- (CGPoint)previousLocationInView:(UIView *)view;

2,通过Touch的相应函数来获得：
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];    
    CGPoint touchPoint = [touch locationInView:self];
	//touchPoint.x ，touchPoint.y 就是触点的坐标。
	NSLog(@"X-cord: %f, Y-cord: %f", location1.x, location1.y);    
}

3,判断捏合操作。

@synthesize initialDistance;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    
    NSLog(@"VC Touch Began");
    
    if ([touches count] == 2) {
        NSArray *twoTouches = [touches allObjects];
        
        UITouch *first = [twoTouches objectAtIndex: 0];
        UITouch *second = [twoTouches objectAtIndex: 1];
        
        initialDistance = distanceBetweenPoints([first locationInView:self.view], 
                                                [second locationInView:self.view]);
        NSLog(@"Bg : cp = %f", initialDistance);
        //NSLog(@"OLD: first=%@, second = %@", first, second);
        //NSLog(@"Sta: init=%@", initialDistance);
    }
    
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    
    NSLog(@"VC Touch Moved");
	
    if ([touches count] == 2) {
        
        NSArray *twoTouches = [touches allObjects];
        
        UITouch *first = [twoTouches objectAtIndex: 0];
        UITouch *second = [twoTouches objectAtIndex: 1];
        
        CGFloat currentDistance = distanceBetweenPoints([first locationInView:self.view], 
                                                        [second locationInView:self.view]);
        
        NSLog(@"Mv : cp = %f, curp = %f", initialDistance, currentDistance);
        //NSLog(@"Mov: init=%@, curr = %@", initialDistance, currentDistance);
        if (initialDistance == 0) {
            initialDistance = currentDistance;
        }
        else if (currentDistance - initialDistance > kMinimmPinchDelta) {
            
            UIAlertView *alert = [[UIAlertView alloc]
                                  initWithTitle: @"More Touch" 
                                  message: @"More Touch OutWard" 
                                  delegate:nil 
                                  cancelButtonTitle: @"OK" 
                                  otherButtonTitles:nil];
            [alert show];
            [alert release];
            
        }
        else if (initialDistance - currentDistance > kMinimmPinchDelta) {
            UIAlertView *alert = [[UIAlertView alloc]
                                  initWithTitle: @"More Touch" 
                                  message: @"More Touch InWard"
                                  delegate:nil 
                                  cancelButtonTitle: @"OK" 
                                  otherButtonTitles:nil];
            [alert show];
            [alert release];
        }
        
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    
    NSLog(@"VC Touch End");
    
    initialDistance = 0;    
}