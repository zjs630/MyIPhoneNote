1.手写代码
	CGRect frame = CGRectMake( 0, 292.0, kPageControlWidth, kPageControlHeight);
	UIPageControl *pageControl = [[UIPageControl alloc] initWithFrame:frame];//创建分页控件
	[pageControl addTarget:self action:@selector(pageAction:) forControlEvents:UIControlEventTouchUpInside];//设置点击触发的方法
	pageControl.backgroundColor = [UIColor clearColor];//控件条的背景色
	pageControl.numberOfPages = PageControlCount;//页的总数
	[mView addSubview: pageControl];


	- (void)pageAction:(id)sender
	{
		NSLog(@"pageAction: current page = %d", [sender currentPage]);
		
	}