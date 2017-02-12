1,从一个UIViewController子类中，加载另一个UIViewController子类的nib文件。
	a,首先通过#import导入类名OtherViewController，并添加导入类的对象,OtherViewController *otherViewController;设置对象特性。
	b, 通过点击按钮来，加载导入类的nib文件。
	-(IBAction)buttonPressed:(id)sender
	{
		OtherViewController *otherController = [[OtherViewController alloc] 
												initWithNibName:@"OtherViewController" bundle:nil];
		self.otherViewController = otherController;
		[otherController release];
		//[self.view removeFromSuperview];
		[self.view insertSubview:otherViewController.view atIndex:1];
		//[self.view insertSubview:otherViewController.view belowSubview:self.view];
		//[self.view insertSubview:otherViewController.view aboveSubview:self.view];
		
	}
	c,要向返回原来的界面。OtherViewController.m中可调用代码以下代码实现。
	[self.view removeFromSuperview];
2,通过视图控制器加载自定义视图。
- (void)loadView {
	UIView *contentView = [[UIView alloc] initWithFrame:[[UIScreen mainScreen] applicationFrame]];
	contentView.backgroundColor = [UIColor greenColor];
	self.view = contentView;
	[contentView release];
}

3

4,the idea here is one screen ,one View Controller.
5，Instantiating a UIViewController by name from a storyboard

NSString *vcid = @"something";
UIViewController *controller = [storyboard instantiateViewControllerWithIdentifier:vcid];
//Usually you get the storyboard above from self.storyboard in an existing UIViewController.
//The identifier vcid must match a string you set in Xcode to identify a UIViewController.

6，Autorotation
When the device is rotated, the top level view controller will have its bounds reoriented iff ... The view controller returns YES from shouldAutorotate.
The view controller returns the new orientation in supportedInterfaceOrientations.
The application allows rotation to that orientation (defined in Info.plist file).

7. View之间切换：
SettingsController *settings = [[SettingsController alloc]initWithNibName:@"SettingsView" bundle:nil];
settings.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;  //水平翻转
[self presentModalViewController:settings animated:YES];
[settings release];


