/*
1，通过触摸移动一个精灵的位置
 - (void)ccTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
 {
 
 UITouch *touch = [touches anyObject];
 // 获得触摸点坐标
 CGPoint location = [touch locationInView: [touch view]];
 CGPoint convertedLocation = [[CCDirector sharedDirector] convertToGL:location];//转换坐标位置
 // 将飞船在 1 秒钟以内移动过去。
 [flight runAction: [CCMoveTo actionWithDuration:1 position:ccp(convertedLocation.x, convertedLocation.y)]];
 /* 可将上一个动作分解为
 a,创建动作
 id actionTo = [CCMoveTo actionWithDuration:1 position:ccp(convertedLocation.x, convertedLocation.y)]
 b,使用动作
 ［flight runAction:actionTo];
 */
 return;
 }
