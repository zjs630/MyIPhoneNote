1，实现在应用程序退出之前保存界面的数据。
a,将以下代码写在- (void)loadView或者- (void)viewDidLoad函数中。

UIApplication *app = [UIApplication sharedApplication];
[[NSNotificationCenter defaultCenter] addObserver:self
										 selector:@selector(applicationWillTerminate:)
											 name:UIApplicationWillTerminateNotification 
										   object:app];

b,将以下代码放入上面代码的同一个文件中。
- (void)applicationWillTerminate:(NSNotification *)notification {
	//do some 保存的操作
    NSMutableArray *array = [[NSMutableArray alloc] init];
    [array addObject:field1.text];
    [array addObject:field2.text];
    [array writeToFile:[self dataFilePath] atomically:YES];
    [array release];
}
