1，Moving UITextField When Keyboard Pops Up!
a,创建一个基于UIViewController的子类，实现UITextFieldDelegate协议。
@interface ClassName : UIViewController<UITextFieldDelegate> 
b,添加以下实现代码。
- (void)textFieldDidBeginEditing:(UITextField *)textField {	
	[UIView beginAnimations:nil context:NULL];
	[UIView setAnimationDelegate:self];
	[UIView setAnimationDuration:0.5];
	[UIView setAnimationBeginsFromCurrentState:YES];
	textfield.frame = CGRectMake(textfield.frame.origin.x, (textfield.frame.origin.y - 100.0), textfield.frame.size.width, textfield.frame.size.height);
	[UIView commitAnimations];
}
- (void)textFieldDidEndEditing:(UITextField *)textField {	
	[UIView beginAnimations:nil context:NULL];
	[UIView setAnimationDelegate:self];
	[UIView setAnimationDuration:0.5];
	[UIView setAnimationBeginsFromCurrentState:YES];
	textfield.frame = CGRectMake(textfield.frame.origin.x, (textfield.frame.origin.y + 100.0), textfield.frame.size.width, textfield.frame.size.height);
	[UIView commitAnimations];
}
c,调用委托，在loadview中写代码。
textfield.delegate = self;
或者在nib文件中设置TextField中Outlet的delegate为file''s Owner.

2,当用户点击键盘的Done时，键盘消失，要在类中添加<UITextFieldDelegate>协议。
然后调用如下方法：
- (BOOL)textFieldShouldReturn:(UITextField *)theTextField {
	if (theTextField == textField) {
		[textField resignFirstResponder];
        // Invoke the method that changes the greeting.
        [self updateString];//将输入的字符显示到Label中。
	}
	return YES;
}
-(void)updateString{
	label.text = textField.text;
}
注：要设置textField的delegate。可以在nib中设置，或通过以下代码：
	textField.delegate = self;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    // Dismiss the keyboard when the view outside the text field is touched.
    [textField resignFirstResponder];
    // Revert the text field to the previous value.
    label.text = textField.text;
  
}
3, 设置点击屏幕，使键盘消失
a,.h文件中
-(IBAction) backgroundTap:(id)sender;
b,.m文件中
-(IBAction) backgroundTap:(id)sender
{
[myTextField resignFirstResponder];
}
c，打开IB，选中UIView视图，Command4，修改class为UIcontrol，Command2，Touch Down连接IBAction(backgroundTap:)。
4,希望在应用里以密码方式显示 UITextField 文本，只需一行代码
	textField.secureTextEntry = YES;

5,创建并配置UITextField实例作为子试图

UITextField *myTextField = [[UITextField alloc] initWithFrame:CGRectMake(10,10, 150, 30)];
myTextField.textColor = [UIColor blackColor];//设置文本的颜色
myTextField.backgroundColor = [UIColor whiteColor];//设置背景颜色
myTextField.font = [UIFont systemFontOfSize:17.0];//设置文本字体的大小
myTextField.placeholder = @"enter text";
myTextField.borderStyle = UITextBorderStyleBezel;
myTextField.keyboardType = UIKeyboardTypeDefault;
myTextField.autocorrectionType = UITextAutocorrectionTypeNo;//取消自动更正
myTextField.returnKeyType = UIReturnKeyDone;
myTextField.clearButtonMode = UITextFieldViewModeAlways;
myTextField.delegate = self;
[theView addSubview:myTextField];



6，设置搜索URL地址栏样式,添加刷新按钮。
UITextField *addressTextField = [[UITextField alloc] initWithFrame:CGRectMake(250, 10, frame.size.width-180-340, 28)];
[addressTextField setDelegate:self];
[addressTextField setKeyboardType:UIKeyboardTypeURL];
[addressTextField setContentVerticalAlignment:UIControlContentVerticalAlignmentCenter];//设置文本垂直居中对齐，//默认是顶端对齐。
[addressTextField setBorderStyle:UITextBorderStyleRoundedRect];
[addressTextField setClearButtonMode:UITextFieldViewModeWhileEditing];// Show cancel button only when you're editing text in textField
[addressTextField setAutocapitalizationType:UITextAutocapitalizationTypeNone];//取消大小写。
[addressTextField setReturnKeyType:UIReturnKeyGo];//设置键盘类型

UIButton *refreshBtn = [UIButton buttonWithType:UIButtonTypeCustom];
[refreshBtn setFrame:CGRectMake(0, 0, 35, 35)];
[refreshBtn setImage:[UIImage imageNamed:@"refresh.png"] forState:UIControlStateNormal];
[addressTextField setRightViewMode:UITextFieldViewModeUnlessEditing];

addressTextField.rightView = refreshBtn;
[refreshBtn addTarget:self action:@selector(refreshTaped:) forControlEvents:UIControlEventTouchUpInside];

[self addSubview:addressTextField];


7,you can use the clearButtonMode property of an UITextField. 
// Show cancel button never
textField.clearButtonMode = UITextFieldViewModeNever;  

// Show cancel button only when you're editing text in textField
textField.clearButtonMode = UITextFieldViewModeWhileEditing;  

// Show the cancel button only when you aren't editing the text
textField.clearButtonMode = UITextFieldViewModeUnlessEditing;

// Show always the cancel button
textField.clearButtonMode = UITextFieldViewModeAlways;


8,/*
   //关闭textField的键盘
   -(BOOL) textFieldShouldReturn:(UITextField *)textField
   {
   [textField resignFirstResponder];
   return YES;
   }
   
   
   //当textView开始编辑时,导航栏添加Done键,当按下Done时,按钮消失,myView回第一响应者
   -(void) textViewDidBeginEditing:(UITextView *)textView 
   {
   self.navigationItem.rightBarButtonItem = [[[UIBarButtonItem alloc] initWithTitle:@"Done" style:UIBarButtonItemStyleDone target:self action:@selector(doneEditing:)] autorelease];
   }
   -(void)doneEditing:(id)sender
   {
   [myView resignFirstResponder];
   self.navigationItem.rightBarButtonItem = NULL;
   }
   */


9,//UITextField输入长度限制

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    int length = textField.text.length - range.length + string.length;
    
    NSUInteger passwordLength = [self.passwordTextField.text length];
    NSUInteger nameLength = [self.nameTextField.text length];
    
    if (textField == _nameTextField) {
        nameLength = length;
    }
    
    if (textField == _passwordTextField) {
        passwordLength = length;
    }
    
    if (passwordLength > 18 || nameLength >= 11) {
        return NO;
    }
    
    if (passwordLength >= 6 && passwordLength <= 18 && nameLength > 0 && nameLength < 11) {
        self.navigationItem.rightBarButtonItem.enabled = YES;
        
    } else {
        self.navigationItem.rightBarButtonItem.enabled = NO;
    }
    
    return YES;
    
}

//方法2
//创建
１.
phonetext = [[UITextField alloc] initWithFrame:CGRectMake(0, 0, self.bounds.size.width-width, 25)];

２.//关联上selector.　注意：　事件要forControlEvents:UIControlEventEditingChanged
[phonetext addTarget:self action:@selector(changePhoneNumValue) forControlEvents:UIControlEventEditingChanged];//手机号码

３.//实现selector
-(void)changePhoneNumValue
{
    int MaxLen = 15;
    NSString* szText = [phonetext text];
    if (phonetext.markedTextRange == nil && [phonetext length]> MaxLen)
    {
        phonetext.text = [szText substringToIndex:MaxLen];
    }
}

#pragma mark - UITextfield
//UITextField输入长度限制
- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    NSString* changedText = textField.text;
    changedText = [changedText stringByReplacingCharactersInRange:range withString:string];
    NSString* trimmingText = [changedText stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    int length = [trimmingText cstrLength];
    //int length = textField.text.length - range.length + string.length;
    
    NSUInteger passwordLength = [self.passwordTextField.text cstrLength];
    NSUInteger newPasswordLength = [self.newsPasswordTextField.text cstrLength];
    NSUInteger confirmPasswordLength = [self.confirmPasswordTextField.text cstrLength];
    
    if (textField == se4lf.passwordTextField) {
        if (length > 18) {
            return NO;
        }
    }
    
    if (textField == self.newsPasswordTextField) {
        if (length > 18) {
            return NO;
        }
    }
    
    if (textField == self.confirmPasswordTextField) {
        if (length > 18) {
            return NO;
        }
    }
    
    return YES;
    
}

