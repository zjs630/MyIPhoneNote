
//禁用剪切板
//禁止textField和textView的复制粘贴菜单： 
-(BOOL)canPerformAction:(SEL)action withSender:(id)sender {
	
	if ( [UIMenuController sharedMenuController] )
	{
		[UIMenuController sharedMenuController].menuVisible = NO;
	}
	return NO;
}