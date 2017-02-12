1,开启状态保存和恢复功能。
在AppDelegate.m文件中添加下面两个方法
- (BOOL) application:(UIApplication *)application shouldSaveApplicationState:(NSCoder *)coder
{
    return YES;
}

- (BOOL) application:(UIApplication *)application shouldRestoreApplicationState:(NSCoder *)coder
{
    
#if 0
    return YES;
#else
    //在不同的版本中恢复
    NSString *bundleVersion = [coder decodeObjectForKey:UIApplicationStateRestorationBundleVersionKey];
    NSLog(@"%@",bundleVersion);
    NSString *myVersion = [coder decodeObjectForKey:@"VersionKey"];// 自己存储的版本号
    NSLog(@"%@",myVersion);
    
    return [bundleVersion isEqualToString:myVersion];

#endif
}
2，只有在StoryBoard中填写了某个controller的Restoration ID，这个controller才有可能进行保存和回复。（如果它的navigation或Tab Bar Controller没有Restoration ID，则这个controller的状态不会被保存和恢复）
注意：Restoration ID一定要设置到视图控制器上，而不是它的主视图上。视图也可以有Restoration ID。

3，
#pragma mark - 状态保存和恢复

#if 0

- (UIViewController *) application:(UIApplication *)application viewControllerWithRestorationIdentifierPath:(NSArray *)identifierComponents coder:(NSCoder *)coder
{
    NSLog(@"%@",identifierComponents);
    UIViewController *viewController = nil;
    NSString *identifier = [identifierComponents lastObject];
    if ([identifier isEqualToString:@"EMPHomePageViewControllerSRID"]) {
        UIStoryboard *storyboard = [coder decodeObjectForKey:UIStateRestorationViewControllerStoryboardKey];
        if (storyboard) {
            viewController = [storyboard instantiateViewControllerWithIdentifier:identifier];
            if (viewController) {
                ;
            }
        }
    }
    return viewController;
}

- (void) application:(UIApplication *)application willEncodeRestorableStateWithCoder:(NSCoder *)coder
{
    [coder encodeObject:[UserData sharedUserData] forKey:@"ShareUserData"];
}

- (void) application:(UIApplication *)application didDecodeRestorableStateWithCoder:(NSCoder *)coder
{
    UserData *userData = [UserData sharedUserData];
    userData = [coder decodeObjectForKey:@"ShareUserData"];
}

#endif
