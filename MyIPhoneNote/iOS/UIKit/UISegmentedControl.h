关于UISegmentedControl 的实例

NSArray *textOptionsArray = [NSArray arrayWithObjects:@"Bart",@"Lisa", @"Maggie", nil];
segmentedCtrl = [[UISegmentedControl alloc] initWithItems:textOptionsArray];
segmentedCtrl.frame = CGRectMake(20.0, 100.0, 280, 50);
[segmentedCtrl addTarget:self action:@selector(segmentChanged:)
		forControlEvents:UIControlEventValueChanged];
[theView addSubview:segmentedCtrl];
//点击UISegmentedControl 中的按钮调用的函数
-(void)segmentChanged:(id)sender{
	if(segmentedCtrl == sender){
		printf("The segment was changed to %d\n",
			   [segmentedCtrl selectedSegmentIndex]);//通过判断点击的是UISegmentedControl中的哪个按钮。
	}
}