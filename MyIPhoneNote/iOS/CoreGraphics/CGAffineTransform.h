1,放大缩小视图
-(void)viewWillAppear:(BOOL)animated{
	UIButton *oneButton = [[UIButton alloc] initWithFrame:CGRectMake(20, 40, 120, 30)];
	[oneButton addTarget:self action:@selector(test) forControlEvents:UIControlEventTouchUpInside];
	[self.view addSubview:oneButton];
	[oneButton setTitle:@"Test" forState:UIControlStateNormal];
    
	isTrue = YES;
	self.view.backgroundColor = [UIColor redColor];
}
-(void)test{
	if (isTrue) {
		isTrue = NO;
		[UIView beginAnimations:nil context:nil];
		CGAffineTransform transform = CGAffineTransformMakeScale(0.9, 0.9);
		[self.view setTransform: transform];
		[UIView commitAnimations];	
	}
	else {
		isTrue = YES;
		[UIView beginAnimations:nil context:nil];
		CGAffineTransform transform = CGAffineTransformMakeScale(1, 1);
		[self.view setTransform: transform];
		[UIView commitAnimations];	
	}
    
}
