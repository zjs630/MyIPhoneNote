1,
	
//textView
UITextView *textView = [[UITextView alloc] initWithFrame:CGRectMake(120, 200.0f, 120.0f, 40.0f)];
textView.text = @"hello world";
textView.editable = NO;//设置文本视图默认为可编辑的，改为只读方式的文本视图。
textView.delegate = self;
textView.textAlignment = UITextAlignmentLeft;//UITextAlignmentLeft UITextAlignmentRight UITextAlignmentCenter
[self.view addSubview:textView];
[textView release];

2,改变textView中选中的文字的颜色。（7.0以后的方法）
- (IBAction)changeBodySelectionColorToMatchBackgroundOfButton:(UIButton *)sender
{
    [self.bodyTextView.textStorage addAttribute:NSForegroundColorAttributeName value:sender.backgroundColor range:self.body.selectedRange];
}
取消颜色选择
- (IBAction)unBodySelection:(UIButton *)sender {
    
    [self.bodyTextView.textStorage removeAttribute:NSForegroundColorAttributeName range:self.body.selectedRange];
    
}

3，字数判断
#pragma mark - UItextViewDelegate

- (void)textViewDidChange:(UITextView *)textView{
    NSInteger length = 300 - textView.text.length;
    
    if (length >= 31 && length <= 300) {
        self.numberLabel.textColor = HEXCOLOR(0x7a7a7aff);
    } else if (length >= 11 && length <= 30) {
        self.numberLabel.textColor = HEXCOLOR(0x9b0202ff);
    } else {
        self.numberLabel.textColor = HEXCOLOR(0xf40303ff);
    }
    self.numberLabel.text = [NSString stringWithFormat:@"%ld", length];
    
    //fix ios 7 bug
    CGRect caret = [textView caretRectForPosition:textView.selectedTextRange.end];
    [textView scrollRectToVisible:caret animated:YES];
}
4.设置键盘滚动时消失。


5,依据键盘，动态改变textView的高度。
（1）
- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    // 监听键盘的出现和隐藏的通知
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillShowNotification object:nil];
}
#pragma mark 键盘出现调用方法
- (void)keyboardWillShow:(NSNotification *)notification
{
    NSDictionary *keyboardInfo = [notification userInfo];
    CGRect  keyboardRect = [[keyboardInfo objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue];
    CGFloat _keyboardHeight = keyboardRect.size.height;
    [UIView animateWithDuration:0.25 animations:^{
        self.suggestionTextView.frame = CGRectMake(10, 15, [UIScreen mainScreen].bounds.size.width-20,self.view.frame.size.height - _keyboardHeight - 30);
    }];
}
