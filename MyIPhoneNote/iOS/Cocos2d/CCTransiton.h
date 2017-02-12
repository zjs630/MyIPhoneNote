1,所有过渡效果的类都继承自CCTransitionScene.

//建议a，过渡的时间不超过1秒，或者干脆完全不用。
//b,避免转换场景设置为随机切换过渡效果。
2,
以下是很流行的淡入淡出过渡效果:它在一秒内过渡到 了白色:
// 用我们想要在下一步显示的场景初始化一个过渡场景 CCFadeTransition* tran = [CCFadeTransition transitionWithDuration:1
scene:[HelloWorld scene] withColor:ccWHITE];
// 使用过渡场景对象而不是HelloWorld [[CCDirector sharedDirector] replaceScene:tran];
你可以把CCTransitionScene与replaceScene和pushScene结合使用,但是你不 能将过渡效果和popScene一起使用。
有很多种过渡效果可以使用,大多是和方向有关的,比如从哪个地方开始过渡 到哪个地方过渡结束。以下是目前可以使用的过渡效果和描述:
1.	CCFadeTransition: 淡入淡出到一个指定的颜色,然后回来。
2.	CCFadeTRTransition (还有另外三个变化): 瓦片(tiles)反转过来揭示场景。 
3.	CCJumpZoomTransition: 场景跳动着变小,新场景则跳动着变大。 
4.	CCMoveInLTransition (还有另外三个变化): 场景移出,同时新的场景从左边,右边,上方或者下方移入。 
5.	CCOrientedTransitionScene (还有另外六个变化): 这种过渡效果会将整个场景翻转过来。
6.	CCPageTurnTransition: 翻动书页的过渡效果。 
7.	CCRotoZoomTransition: 当前场景旋转变小,新的场景旋转变大。 
8.	CCShrinkGrowTransition: 当前场景缩小,新的场景在其之上变大。
9. CCSlideInLTransition (还有另外三个变化): 新的场景从左边,右边,上方或者下方滑 入。 
10. CCSplitColsTransition (还有另外一个变化): 将当前场景切成竖条,上下移动揭示新场景。
11. CCTurnOffTilesTransition:将当前场景分成方块,用分成方块的新场景随机的替换当前 
场景分出的方块。







