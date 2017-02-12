

1,禁用复制，剪切，粘贴等按钮。
-(BOOL)canPerformAction:(SEL)action withSender:(id)sender {
	
	if ( [UIMenuController sharedMenuController] )
	{
		[UIMenuController sharedMenuController].menuVisible = NO;
		
	}
	return NO;
}




2.第一响应者通常是用户当前正在交互的对象
保持响应者链的活动状态

-(void)respindTofictionalEvent:(UIEvent *)event{
    if(somecondition)
        [self handlvEvent:event];
    else
        [self.nextResponder respondToFictionalEvent:event];
}