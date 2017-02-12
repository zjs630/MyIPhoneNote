1,动作延时
- (void) OnDelay:(id) sender
{
	id ac1 = [CCMoveBy actionWithDuration:2 position:ccp(200, 200)];
	id ac2 =  [CCDelayTime actionWithDuration:5];//延时5s
	id ac3 = [ac1 reverse];
	[sprite runAction:[CCSequence actions:ac1,ac2, ac3, nil]];		
}
2，函数调用
在动作序列中间戒者结束调用某个函数,执行任何需要执行的任务:动作、状态修 改等。
(1)不带参数
- (void) OnCallFunc:(id) sender
{
	
	id ac1 = [CCMoveBy actionWithDuration:2 position:ccp(200, 200)];
	id ac2 = [ac1 reverse];
	
	id acf = [CCCallFunc actionWithTarget:self selector:@selector(CallBack1)];
	
	[sprite runAction:[CCSequence actions:ac1, acf, ac2, nil]];
	
}

- (void) CallBack1
{
	[sprite runAction:[CCTintBy actionWithDuration:0.5 red:255 green:0 blue:255]];	
}
(2)带对象参数
//调用自定义函数时,传递当前对象。
- (void) OnCallFuncN:(id) sender
{
	id ac1 = [CCMoveBy actionWithDuration:2 position:ccp(200, 200)];
	id ac2 = [ac1 reverse];
	
	id acf = [CCCallFuncN actionWithTarget:self selector:@selector(CallBack2:)];
	
	[sprite runAction:[CCSequence actions:ac1, acf, ac2, nil]];
	
}
//对应的自定义函数:(这里,我们直接使用了该对象)
- (void) CallBack2:(id)sender
{
	[sender runAction:[CCTintBy actionWithDuration:1 red:255 green:0 blue:255]];	
}


(3)带对象、数据参数 调用自定义函数时,传递当前对象和一个常量(也可以是指针)。
- (void) OnCallFuncND:(id) sender
{
	id ac1 = [CCMoveBy actionWithDuration:2 position:ccp(200, 200)];
	id ac2 = [ac1 reverse];
	
	id acf = [CCCallFuncND actionWithTarget:self selector:@selector(CallBack3:data:) data:(void*)2];
	
	[sprite runAction:[CCSequence actions:ac1, acf, ac2, nil]];
	
}
//对应的自定义函数,我们使用了传递的对象和数据:
-(void) CallBack3:(id)sender data:(void*)data
{
	[sender runAction:[CCTintBy actionWithDuration:(NSInteger)data red:255 green:0 blue:255]];	
}

