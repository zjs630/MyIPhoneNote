时间进度类可用于很多地方,比如加载进度条,或者用
于展示处于失效状态的按钮恢复到激活状态所需要的时间(你可以回想一下 
《魔兽争霸》里面的动作按钮和恢复到可以释放魔法的时间进度显示)。进度 
条使用精灵图形来显示进度:随着时间的过去逐渐显示出精灵的全部,来表示 
游戏的进度。列表5-15代码展示了如何初始化CCProgressTimer节点:
列表5-15.初始化CCProgressTimer节点 
//进度条使用精灵图形来显示进度:随着时间的过去逐渐显示出精灵的全部,来表示游戏的进度
CCProgressTimer* timer = [CCProgressTimer progressWithFile:@"Icon-72.png"]; 
timer.type = kCCProgressTimerTypeHorizontalBarLR; 
timer.percentage = 0; 
timer.position = CGPointMake(120, 120);
[self addChild:timer z:1 tag:77];

// 进度条需要预约的更新方法来更新自身的状态
[self scheduleUpdate];
timer类型来自在CCProgressTimer.h里定义的CCProgressTimerType这个枚举类 
型。你可以选择圆形,纵向和横向的进度显示。不过进度条有一个缺点:它不 
会自己更新自己。你必须经常更新进度条的百分比数值来显示进度。这是我在 
列表5-15的代码中包含了scheduleUpdate这个更新方法的原因。列表5-16展示 
了这个更新方法的具体实现代码。这里的进度是用当前已经经过的时间来表示 的。
列表5-16.进度时间的更新方法的具体实现
-(void) update:(ccTime)delta {
	
	CCNode* node = [self getChildByTag:77];
    NSAssert([node isKindOfClass:[CCProgressTimer class]], @"node is not a CCProgressTimer");
	// 更新进度条的时间显示 
    CCProgressTimer* timer = (CCProgressTimer*)node; 
    timer.percentage += delta * 10;
    if (timer.percentage >= 100) {
        timer.percentage = 0;
    }
}


