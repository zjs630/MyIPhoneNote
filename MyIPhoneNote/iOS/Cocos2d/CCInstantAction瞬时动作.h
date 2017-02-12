1，将精灵随机移动到某一位置。
//
// CCPlace
- (void) OnPlaceMenue:(id) sender
{
	CGSize s = [[CCDirector sharedDirector] winSize];
	CGPoint p = ccp(CCRANDOM_0_1() * s.width, CCRANDOM_0_1() * s.height);
	
	[sprite runAction:[CCPlace actionWithPosition:p]];
	
}
2，隐藏精灵//CCHide
[sprite runAction:[CCHide action]];
3,显示精灵//CCShow
[sprite runAction:[CCShow action]];	
4,精灵可见切换 
[sprite runAction:[CCToggleVisibility action]];	