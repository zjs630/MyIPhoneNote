1,视图生命周期。 loadView,viewDidLoad,viewWillAppear,viewDidAppear,viewWillDisappear,viewDidDisappear等区别

loadView; 
viewDidLoad;

viewWillAppear: 
viewDidAppear: 

viewWillDisappear:
viewDidDisappear:



- (void)loadView;//无nib,加载界面时调用

// This is where subclasses should create their custom view hierarchy if they aren't using a nib. Should never be called directly.
//这是当他们没有正在使用nib视图页面，子类将会创建自己的自定义视图层。绝不能直接调用。

- (void)viewDidLoad;//有nib,nib加载完后，界面进一步更改时调用//只在第一次加载其视图的时候调用。
Called after the view has been loaded. For view controllers created in code, this is after -loadView. For view controllers unarchived from a nib, this is after the view is set.
在视图加载后被调用，如果是在代码中创建的视图加载器，他将会在loadView方法后被调用，如果是从nib视图页面输出，他将会在视图设置好后后被调用。
//在这里视图的bounds还没有定下来，所以不要在这里设置视图的位置。



- (void)viewWillAppear:(BOOL)animated;
Called when the view is about to made visible. Default does nothing
视图即将可见时调用。默认情况下不执行任何操作
//界面将要appear的指令已经发出，但是apear还没完成，典型是switch view时，switch动作开始后到结束前调用
//当view出现在屏幕上之前，会调用此方法。此方法可以调用多次，所以不要在这里添加一次性初始化的东西。
//在这里view的几何信息已经设置了，因此你可以在这里做一些关于几何的初始化。但有一个地方更适合做基于几何的初始化(如：viewWillLayoutSubviews)。

- (void)viewDidAppear:(BOOL)animated;
// Called when the view has been fully transitioned onto the screen. Default does nothing
//视图已完全过渡到屏幕上时调用
//界面将要appear的指令发出，apear已经完成时调用，典型是switch view时，switch动作结束后调用


- (void)viewWillDisappear:(BOOL)animated;//和上面差不多
Called when the view is dismissed, covered or otherwise hidden. Default does nothing
视图被驳回时调用，覆盖或以其他方式隐藏。默认情况下不执行任何操作//当视图从屏幕消失时，会调用此方法。
//可以停止动画，停止视频播放，停止占用资源的东西。保存当前状态，以便在viewWillAppear中恢复。


- (void)viewDidDisappear:(BOOL)animated;
Called after the view was dismissed, covered or otherwise hidden. Default does nothing
视图被驳回后调用，覆盖或以其他方式隐藏。默认情况下不执行任何操作



- (void)viewWillUnload __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);//Deprecated
- (void)viewDidUnload //Deprecated
// Called after the view controller's view is released and set to nil. For example, a memory warning which causes the view to be purged. Not invoked as a result of -dealloc.
//view 已经 remove 的时候调用（如：内存警告，当前试图并未显示），清理内存

2,先调用init方法,如果没有用nib创建试图，--------->loadView---->viewDidLoad---->viewWillAppear---->viewDidAppear---->
弹出viewController---->viewWillDisappear---->viewDidDisappear

3,- (void)didReceiveMemoryWarning; 
// Called when the  application receives a memory warning. Default implementation releases the view if it doesn't have a superview.
// Releases the view if it doesn't have a superview.
// Release any cached data, images, etc that aren't in use.









