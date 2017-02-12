Sequence 的使用非常简单,该类也从 CCIntervalAction 派生,本身就可以被 CocosNode 对象执行。
该类的作用就是线序排列若干个动作,然后按先后次序逐个执行。
1，播放一系列基本动作。
- (void) OnSequence:(id) sender
{
	CGSize s = [[CCDirector sharedDirector] winSize];
	CGPoint p = ccp(s.width/2, 50);
	// 创建5个动作
	id ac0 = [sprite runAction:[CCPlace actionWithPosition:p]];
	id ac1 = [CCMoveTo actionWithDuration:2 position:ccp(s.width - 50, s.height - 50)];
	id ac2 = [CCJumpTo actionWithDuration:2 position:ccp(150, 50) height:30 jumps:5];
	id ac3 = [CCBlink actionWithDuration:2 blinks:3];
	id ac4 = [CCTintBy actionWithDuration:0.5 red:0 green:255 blue:255];//变色
	//创建回调函数
	CCCallFunc* func = [CCCallFunc actionWithTarget:self selector:@selector(onCallFunc)];
	//将 5 个动作组合为一个序列,注意丌要忘了用 nil 结尾。
	[sprite runAction:[CCSequence actions:ac0, ac1, ac2, ac3, ac4, func, nil]];
	
}
-(void)onCallFunc{
	CCLOG(@"end of action!");
}
2,函数回调

CCCallFunc* func = [CCCallFunc actionWithTarget:self selector:@selector(onCallFunc)];
CCCallFuncN* funcN = [CCCallFuncN actionWithTarget:self selector:@selector(onCallFuncN:)]; 
CCCallFuncND* funcND = [CCCallFuncND actionWithTarget:self selector:@selector(onCallFuncND:data:) data:(void*)self];

CCSequence* seq = [CCSequence actions:tint1, func, tint2, funcN, tint3, funcND, nil]; 
[label runAction:seq];

-(void) onCallFuncN:(id)sender {
	CCLOG(@"end of tint2! sender: %@", sender);
}
-(void) onCallFuncND:(id)sender data:(void*)data {
	// 如下转换指针的方式要求data必须是一个CCSprite 
	CCSprite* sprite = (CCSprite*)data; 
	CCLOG(@"end of sequence! sender: %@ - data: %@", sender, sprite);
}
//sender这个参数继承自CCNode;这 是运行动作的节点。
//data参数可以是任何值,结构或者指针。只是你必须正确 地转换data指针的类型。



