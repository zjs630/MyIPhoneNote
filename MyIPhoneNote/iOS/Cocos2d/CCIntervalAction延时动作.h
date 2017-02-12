1,延时动作就是指动作的完成需要一定时间。
因此,actionWithDuration 是延时动作执 行时的第一个参数,
延时动作的共同基类是 CCIntervalAction。
XXXXTo：意味着运动到指定的位置。
XXXXBy：意味着运动到指定的x，y增量的位置。（x,y可以是负值）。
2，//移动到某一位置：//CCMoveTo
[sprite runAction:[CCMoveTo actionWithDuration:2 position:ccp(320,100)]];
//移动x，y方向的偏移量
[sprite runAction:[CCMoveBy actionWithDuration:2 position:ccp(-50, -50)]];
3,//跳跃到某个位置，设置终点，跳跃的高度和次数。
[sprite runAction:[CCJumpTo actionWithDuration:2 position:ccp(150, 50) height:30 jumps:5]];
//跳跃-CCJumpBy
[sprite runAction:[CCJumpBy actionWithDuration:1 position:ccp(100, 100) height:30 jumps:5]];
4,//3次贝塞尔曲线,首先设置定 Bezier 参数,然后执行。//CCBezierBy
ccBezierConfig bezier;
bezier.controlPoint_1 = ccp(0, 200);
bezier.controlPoint_2 = ccp(120, 200);
bezier.endPosition = ccp(160,0);

[sprite runAction:[CCBezierBy actionWithDuration:2 bezier:bezier]];
5,//放大缩小精灵，是浮点数。//CCScaleTo
[sprite runAction:[CCScaleTo actionWithDuration:2 scale:4]];
//可多次放大缩小//CCScaleBy
[sprite runAction:[CCScaleBy actionWithDuration:2 scale:2]];
6,//设置闪烁，//CCBlink
[sprite runAction:[CCBlink actionWithDuration:3 blinks:5]];//闪烁5次

7,颜色变化//色调变化到 – CCTintTo
[sprite runAction:[CCTintTo actionWithDuration:2 red:255 green:0 blue:0]];
//色调变换 – CCTintBy
[sprite runAction:[CCTintBy actionWithDuration:0.5 red:0 green:110 blue:0]];
8,设置淡入淡出效果
[sprite runAction:[CCFadeTo actionWithDuration:1 opacity:80]];
[sprite runAction:[CCFadeIn actionWithDuration:1.0f]];
[sprite runAction:[CCFadeOut actionWithDuration:1.0f]];

