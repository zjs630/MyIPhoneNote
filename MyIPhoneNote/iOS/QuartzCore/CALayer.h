1,CALayer就是层，这个层你随便控制他的大小，旋转，角度，坐标变化或者内容之类的信息，这些变化还可以通过动画表现出来。
UIView所有你能看到的显示的内容，后面都有一个Layer。下面来自定义添加一个CALayer。
	CALayer *layer = [[CALayer alloc] init];//定义一个layer
	layer.frame = CGRectMake(10, 30, 240, 240);//设置该layer的坐标和大小
	UIColor *c = [UIColor redColor];
	[layer setBackgroundColor:(c.CGColor)];//设置该layer的背景，因为layer setBackgroundColor用到的是CGColor所以要进行一次转换
	[self.view.layer insertSublayer:layer atIndex:0];//在self view中添加该layer

2,//要访问图层，需要读取基类UIView的layer属性：
	CALayer *layer = myView.layer;
所有派生自UIView的对象，都会继承这一属性，正是这些图层控制了视图的内容时如何呈现再屏幕上的。