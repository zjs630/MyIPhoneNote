UITabBarController is a Array of view controllers.
1,创建一个tab bar controller
	tabBarController = [[UITabBarController alloc] init];
2,创建每个navigation controller
	navController = [[UINavigationController alloc] init];
	[navController pushViewController:firstViewController
							animated:NO];
3,添加它们到tab bar controller
tabBarController.viewControllers = [NSArray arrayWithObjects:
												navController,
												anotherNavController,
												someViewController,
												nil];
												
												
4,创建tab Bar Items,设置标题和图片
self.tabBarItem = [[UITabBarItem alloc]
						initWithTitle:@"PlayLists"
						image:[UIImage imageNamed:@"music.png"]
						tag:0];
5,创建一个System item.
self.tabBarItem = [[UITabBarItem alloc] initWithTabBarSystemItem:UITabBarSystemItemBookmarks tag:0];

6.关于tabbar的隐藏

[self.tabBarController makeTabBarHidden:YES];
如果是navigationController +tabBarController的结构的话，在push到下一级的childController的时候用
childController.hidesBottomBarWhenPushed = YES;
就行了