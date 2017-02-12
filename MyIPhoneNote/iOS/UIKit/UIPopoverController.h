1,默认的初始化方法
UIViewController *vc = ...;
UIPopoverController *popover = [[UIPopoverController alloc] initWithContentViewController:vc];//注：参数不能为空，必须的初始化时指定一个UIViewController。
//send this message to get the popover to appear
[popover presentPopoverFromRect:(CGRect)aRect 
						 inView:(UIView *)aView
	   permittedArrowDirections:(UIPopoverArrowDirection)direction 
					   animated:(BOOL)animated];
//The direction can be UIPopoverArrowDirectionUp/Down/Left/Right/Any.
2，How to set the size of the popover
[popover setPopoverContentSize:(CGSize)aSize animated:(BOOL)animated];
//3, 得到popover view's UIViewController 的大小
-(CGSize)contentSizeForViewInPopover;
4,How to dismiss the popover from the screen
User clicks anywherre outside the popover.
Or you can dismiss it programmatically by sending the popover this method
[popover dismissPopoverAnimated:(BOOL)animated]; 
5,How to tell if the popover is currently on the screen
if([popover.isPopoverVisible])
6,Popover has a delegate to prevent (and get notified of)dismissal
- (BOOL)popoverControllerShouldDismissPopover:(UIPopoverController *)popover;
- (BOOL)popoverControllerDidDismissPopover:(UIPopoverController *)popover;
