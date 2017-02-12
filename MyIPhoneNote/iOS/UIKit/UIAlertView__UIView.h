1.弹出对话框的代码：

UIAlertView *alter = [[UIAlertView alloc] initWithTitle:.........];
[alter show];
[alter release];

2,How to ask a user to confirm an action with UIAlertView and UIAlertSheet

-(void) confirmDelete {
 	UIAlertView *alertView = [[UIAlertView alloc]
							  initWithTitle:@"Remove account"	
							  message:@"Are you sure you want to remove this account?"
							  delegate:self
							  cancelButtonTitle:@"Remove"
							  otherButtonTitles:nil];
 	
 	[alertView addButtonWithTitle:@"Don't remove"];
 	[alertView show];
 	[alertView release];
}

- (void)alertView:(UIAlertView *)alertView
clickedButtonAtIndex:(NSInteger)buttonIndex {
 	[appDelegate.managedObjectContext deleteObject:selectedAccount];
 	if (buttonIndex == 0) {
 		NSLog(@"Remove button clicked");
 	} else if (buttonIndex == 1) {
 		NSLog(@"Cancel button clicked");
 	}
}

-(void)confirmDelete {
 	UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"Remove account?" delegate:self cancelButtonTitle:@"Don't remove" destructiveButtonTitle:@"Remove account" otherButtonTitles:nil];
 	actionSheet.actionSheetStyle = UIActionSheetStyleBlackOpaque;	
 	[actionSheet showInView:[UIApplication sharedApplication].keyWindow];	
 	[actionSheet release];
}

-(void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
 	if (buttonIndex == 0) {
 		NSLog(@"Remove button clicked");
 	} else if (buttonIndex == 1) {
 		NSLog(@"Cancel button clicked");
 	}
}
3,
- (void) performDismiss: (NSTimer *)timer
{
    [baseAlert dismissWithClickedButtonIndex:0 animated:NO];//important，让baseAlert直接消失，不会调用其它的delegate方法。
    [baseAlert release];
    baseAlert = nil;
}

- (void) presentSheet
{
    baseAlert = [[UIAlertView alloc] 
				 initWithTitle:@"Alert" message:@"\nMessage to user with asynchronous information" 
				 delegate:self cancelButtonTitle:nil
				 otherButtonTitles: nil];
    [NSTimer scheduledTimerWithTimeInterval:1.0f target:self selector: @selector(performDismiss:)
                                   userInfo:nil repeats:NO];
    [baseAlert show];
}

4,设置UIAlert按钮颜色，（但是不建议这么用）。

UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"" message:@"设置按钮为红色" delegate:nil cancelButtonTitle:@"我是红色" otherButtonTitles:nil];

[[UIView appearance] setTintColor:[UIColor redColor]];

[alertView show];

然后要在点击按钮的时候将tintColor置空，因为默认UIView appearance的tintColor是为nil的：
- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == [alertView cancelButtonIndex]) {
        [[UIView appearance] setTintColor:nil];
    }
}
