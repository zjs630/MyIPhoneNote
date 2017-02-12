/*导演 (CCDirector)
一个游戏的整体架构，不同的场景由不同的层组成，每个层又包括自己的精灵在层上运动。
玩家玩游戏的过程就是在操作每个层上的精灵或者菜单选项，导致整个游戏在不同的场景中切换。

it stores global configuration settings for cocos2d and also manages the cocos2d scenes.
 
导演对象负责游戏全过程的场景切换。
导演通常只有一个，因此这个对象是单例（singleton）。
 Cocos2D-iPhone框架已经预定义了该实例，不需创建，我们直接使用就可以。

导演对象接受层对象/场景的要求，按照预先设计好的流程来终止、压栈、激活当前场景，引导下一个场景。

需要特别说明的是：
 任何时间，只有一个Scene对象实例处于运行激活状态。
 该对象可以作为当前游戏内容的对象的整体包容对象，对于Menu（菜单对象，继承Layer对象），
 通常属于当前场景的主层。以上就是一个游戏的主要整体对象架构。
*/

Director 对象一次只能显示一个场景。为了便亍管理场景对象,
Derictor 对象有以下 3 个属性不场景有关:
1.当前正在显示的场景。Scene *runningScene_; 
2.下一个将要显示的场景。Scene *nextScene; 
3.代执行场景队列。NSMutableArray *scenesStack_;(实际应用时,要确保代执行队列不要太长)

常用方法：
1，加载场景
(void) runWithScene:(Scene*) scene;
2，挂起当前当前正在运行的场景并压栈到代执行场景队列。将传入场景设置为当前执行场景:
(void) pushScene:(Scene*) scene;
//[[CCDirector sharedDirector] pushScene:[Settings scene]];
3，执行在执行场景队列中的最后一个场景,当前场景被释放:(void) popScene;
当代执行队列中没有代执行场景时,系统自动退出,调用 end 方法。
//pushScene和popScene方法，
//What they do is to run the new scene without removing the old scene from memory.
//The idea is to make changing scenes faster.//目的是让场景切换的更快。

//[[CCDirector sharedDirector] popScene];


4，直接用一个场景取代当前执行场景,释放当前场景:
(void) replaceScene:(Scene*) scene;//用于场景的切换和返回。
例如：
- (void) newGame:(id) sender {
	CCScene *sc = [CCScene node];
	[sc addChild:[GameLayer node]]; 
	[[CCDirector sharedDirector] replaceScene: sc];
	//实现画面切换效果
	//[[CCDirector sharedDirector] replaceScene: [CCSlideInRTransition transitionWithDuration:1.2f scene:sc]];
}
5.	结束场景运行:(void) end;
6.	暂停场景运行:(void) pause;画面迓存在,时间任务停止。 
7.	恢复场景运行:-(void) resume;
8,设置场景显示模式
    [[Director sharedDirector] setLandscape: YES];//横屏显示
9,获得场景视图的大小
CGSize s = [[CCDirector sharedDirector] winSize];
10,
Directors 有4种类型供你选择，但是它们在细节上有些不同。
最常用的Director is the CCDisplayLinkDirector,他使用了Apple's CADisplayLink class.
这是最好的选择，but available only on ios versions 3.1 or higher.
其次，你可以使用CCFastDirector。

if you plan on using Cocoa Touch views alongside cocos2d,你必须切换到CCThreadedFastDirector,
因为只有这个才fully supports them.不好的一面是对device's battery耗电。

最后的选择是 CCTimerDirector,但这是没有办法的选择,因为它是四种Director里面最慢的。


