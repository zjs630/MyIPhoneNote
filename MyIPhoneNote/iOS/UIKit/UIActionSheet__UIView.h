1.UIActionSheet显示简单菜单。
a,为UIViewController子类添加<UIActionSheetDelegate>协议。
b,在loadView函数中添加导航按钮，并添加触发事件。
self.navigationItem.rightBarButtonItem = [[[UIBarButtonItem alloc] initWithTitle:@"Do It" style:UIBarButtonItemStylePlain target:self action:@selector(presentSheet)] autorelease];
c,显示菜单代码
- (void) presentSheet
{
	UIActionSheet *menu = [[UIActionSheet alloc] 
						   initWithTitle: @"File Management" 
						   delegate:self
						   cancelButtonTitle:@"Cancel"
						   destructiveButtonTitle:@"Delete File"
						   otherButtonTitles:@"Rename File", @"Email File", nil];
	[menu showInView:self.view];
	[menu release];
}
d,输出点击的是那个菜单
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
	printf("User Pressed Button %d\n", buttonIndex + 1);
	[actionSheet release];
}
2,
//和导航和toolbar一样支持三个风格
设置方法:
mySheet.actionSheetStyle = UIActionSheetStyleDefault;


//显示操作表单有三种方法:
[mySheet showInView:self];
[mySheet showInToolBar:toolbar];
[mySheet showInTabBar:tabbar];

//解除表单
[mySheet dismissWithClickedButtonIndex:1 animated:YES];

3，出现这个错误
Presenting action sheet clipped by its superview.
Some controls might not respond to touches. 
On iPhone try -[UIActionSheet showFromTabBar:] or -[UIActionSheet showFromToolbar:] 
instead of -[UIActionSheet showInView:].

解决：
[actionSheet showInView:[[[UIApplication sharedApplication] windows] objectAtIndex:0] ];

