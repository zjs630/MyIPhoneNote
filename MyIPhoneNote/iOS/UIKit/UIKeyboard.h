

10.6 键盘

//风格
textView.keyboardType = UIKeyboardTypePhonePad; //电话键盘,输入号码
Default   //默认,可使用所有字符
ASC||Capable //支持ASC||值的默认键盘
URL       //URL键盘
......




//外观
textView.keyboardAppearance = UIKeyboardAppearanceDefault; //默认,浅灰色
AppearanceAlert   //深灰色

//回车键
textView.returnKeyType = UIReturnKeyGo;
.....


//自动更正
textView.autocorrectionType = UITextAutocorrectionTypeDefault;

//安全文本输入
textView.secureTextEntry = YES;



14、Ipad隐藏键盘的同时触发方法。
[[NSNotificationCenter defaultCenter] addObserver:self
										 selector:@selector(keyboardWillHide:)
											 name:UIKeyboardWillHideNotification
										   object:nil];
- (IBAction)keyboardWillHide:(NSNotification*)note{
	
}

12、更改iphone的键盘颜色：

1.只有这2种数字键盘才有效果。UIKeyboardTypeNumberPad，UIKeyboardTypePhonePad
2. keyboardAppearance ＝ UIKeyboardAppearanceAlert 
- (void)textViewDidBeginEditing:(UITextView *)textView{
	NSArray *ws = [[UIApplication sharedApplication] windows];
	for(UIView *w in ws){
		NSArray *vs = [w subviews];
		for(UIView *v in vs)
		{
			if([[NSString stringWithUTF8String:object_getClassName(v)] isEqualToString:@"UIKeyboard"])
			{
				v.backgroundColor = [UIColor redColor];
			}
		}
	}
	
	
