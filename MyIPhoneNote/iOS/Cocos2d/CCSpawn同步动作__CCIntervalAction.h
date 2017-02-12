Spawn 的使用非常简单,该类也从 IntervalAction 派生,本身就可以被
CocosNode 对象执行。该类的作用就是同时并列执行若干个动作,但要求动作都必须是可以同时执行的。
比如:移动式翻转、变色、变大小等。
需要特别注意的是,同步执行最后的完成时间由基本动作中用时最大者决定。
1，
- (void) OnSpawn:(id) sender
{
	CGSize s = [[CCDirector sharedDirector] winSize];
	CGPoint p = ccp(s.width/2, 50);
	
	sprite.rotation = 0;
	[sprite setPosition:p];
	// 创建 4 个需要并行的动作,确保动作用时可组合。2 – 2 - (1+1)
	id ac1 = [CCMoveTo actionWithDuration:2 position:ccp(s.width - 50, s.height - 50)];
	id ac2 = [CCRotateTo actionWithDuration:2 angle:180];
	id ac3 = [CCScaleTo actionWithDuration:1 scale:4];
	id ac4 = [CCScaleBy actionWithDuration:1 scale:0.5];
	
	id seq = [CCSequence actions:ac3, ac4, nil];
	// 同步 动作和组合动作 以形成一个连续的新动作。
	[sprite runAction:[CCSpawn actions:ac1, ac2, seq, nil]];
	
}