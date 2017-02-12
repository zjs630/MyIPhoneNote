//1,
NSString *storyboardName =@"新建的storyboard文件名";//无后缀.storyboard
UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:storyboardName bundle: nil];
UIViewController *rightViewController = [mainStoryboard instantiateViewControllerWithIdentifier:@"RightViewController"]; //“RightViewController”自己制定的标记
