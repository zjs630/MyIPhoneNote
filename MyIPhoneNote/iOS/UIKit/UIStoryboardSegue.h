//1,通过代码，从storyboard中实例化一个UIViewController，通过创建vc的name（identifier）。
#if 0
NSString *storyboardName =@"新建的storyboard文件名";//无后缀.storyboard
UIStoryboard *mainStoryboard = [UIStoryboard storyboardWithName:storyboardName bundle:nil];
UIViewController *rightViewController = [mainStoryboard instantiateViewControllerWithIdentifier:@"RightViewController"]; //“RightViewController”自己制定的标记(storybord id)
//rightViewController.infoDoitNeeds = self.info;
[self.navigationController pushViewController:rightViewController animated:YES];
#else
UIViewController *controller = [storyboard instantiateViewControllerWithIdentifier:@"vcStorybordID"];
//controller.infoDoitNeeds = self.info;
[self.navigationController pushViewController:controller animated:YES];
#endif
2,segues的种类
push //有navigation的时候使用
replace //Replaces the right-hand side of a UISplitViewController (iPad only)
popover //Puts the view controller on the screen in a popover (iPad only)
modal //Puts the view controller up in a way that blocks the app until it is dismissed
custom // You can create your own subclasses of UIStoryboardSegue
3，通过代码生成一个segue。
Sometimes it makes sense to segue directly when a button is touched, but not always.
For example, what if you want to conditionally segue?
You can programmatically invoke segues using this method in UIViewController:
- (void)performSegueWithIdentifier:(NSString *)segueId sender:(id)sender;
//The segueId is set in the attributes inspector in Xcode (seen on previous slide).
//The sender is the initiator of the segue (a UIButton or yourself (UIViewController) usually).
- (IBAction)rentEquipment
{
        [self performSegueWithIdentifier:@"segueID" sender:self];
}

//传递数据
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"segueID"]) {
        if ([segue.destinationViewController isKindOfClass:[HWSecondViewController class]]) {
            HWSecondViewController *doVC = (HWSecondViewController *)segue.destinationViewController;
            //doVC.neededInfo = ...; 传递数据
        }
    }
}

//组织是否跳转，很少使用
- (BOOL)shouldPerformSegueWithIdentifier:(NSString *)identifier sender:(id)sender {
    ￼    if ([segue.identifier isEqualToString:@"DoAParticularThing"]) {
        return [self canDoAParticularThing] ? YES : NO;
    }
}

4,切换storyboard

UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Buyers_iPhone" bundle:nil];
self.view.window.rootViewController = [storyboard instantiateInitialViewController];

