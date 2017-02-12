/*
 1，设置时间间隔，重复调用一个函数。
 -(void) schedule: (SEL) selector interval:(ccTime)interval
 //设定时间回调凼数,修改游戏用时显示
 [self schedule:@selector(timeUpdate:) interval:1];
 