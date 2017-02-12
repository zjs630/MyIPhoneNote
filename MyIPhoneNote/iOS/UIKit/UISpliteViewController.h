//1,创建SplitViewController
UIViewController *vc1 = ...;
UIViewController *vc2 = ...;
UISplitViewController *svc = [[UISplitViewController alloc] init];//should be ivar released in dealloc?????
svc.viewControllers = [NSArray arrayWithObjects:vc1,vc2,nil];
[vc1 release];
[vc2 release];
[window addSubview:svc.view];