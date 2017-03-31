//
//  untitled.h
//  基础教程的笔记
//
//  Created by spey on 10-7-31.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//



14.modal的一个转换动画

CATransition *animation = [CATransition animation];
animation.duration = 0.4f;
animation.timingFunction = UIViewAnimationCurveEaseInOut;
animation.fillMode = kCAFillModeForwards;
animation.type = kCATransitionMoveIn;
animation.subtype = kCATransitionFromTop;
[about.view setFrame:CGRectMake(251.0f, 200.0f, 484, 600)];
[self.view addSubview:about.view];
[about.view.layer addAnimation:animation forKey:@"presentModalViewController"];





3.6 创建转场动画

#import <QuartzCore/QuartzCore.h>

//1.创建新动画:
CATransition *myTransition = [CATransition animation];


/*
 2.指定方法:
 myTransition.timingFunction = UIViewAnimationCurveEaseInOut;
 
 计时函数包括:
 UIViewAnimationCurveEaseInOut  在动画的开头和结尾比较慢
 UIViewAnimationCurveEaseIn     开始慢,后面快
 ........................Out    开始快,后面慢
 ....................Linear     速度不变
 
 
 
 */

/*
 3.动画类型
 myTransition.type = kCATransitionPush;
 或
 myTransition.subtype = kCATransitionFromLeft;
 
 方法有: 
 kCATransitionFade  从一个视图淡入淡出到另一个视图
 .............MoveIn 将新视图移入,覆盖旧视图
 .............Push   推出
 ..............Reveal 移走旧视图,露出新视图
 
 kCATransitionFromRight  新视图从右侧滑入
 .................Left
 .................Top
 .................Bottom
 
 
 
 */
持续时间: .duration = 0.3;

//4.生成动画:
1.两个控制器之间转: [[self.view.superview.layer] addAnimation:myTransition forKey:nil];

2.一个控制器内两视图之间转:
[self.view.layer addAnimation:myTransition forKey:nil];
[self.view addSubview:newView];
[oldView removeFromSuperview];

3.导航的话:
[navigationController.view.layer addAnimation:myTransition forKey:nil];




在玩一些 iPhone/iPod Touch 游戏时, 按游戏开始或由一个画面转到另一个画面, 会有一个很cool 的转移画面, 一直在想是怎么做的呢? 后来才知道, 是用了 LKAnimation.

刚找到参考, 马上试试用.

附件是代码包和app, 测试时, 只要用手指点一下屏幕, 就会出现一种效果, 一共有19种效果之多呢!

看看LKAnimation 的设定:

LKAnimation *animation = [LKTransition animation];

[animation setType: effects[mCurr]];

[animation setSubtype: subtype[rand()%4]];

[animation setTimingFunction: [LKTimingFunction functionWithName: @"easeInEaseOut"]];

[animation setFillMode: @"extended"];

[animation setTransitionFlags: 3];

[animation setSpeed: 0.20];

[[self _layer] addAnimation: animation forKey: 0];



其中 [animation setType: effects[mCurr]] 的参数是一个字符串, 字符串可以是下列的其中一个:

- pageCurl: 旧版面像一页书那样被揭开, 显示下面的新版面.
- pageUnCurl: 新版面像一页书被翻过来覆盖旧版面.
- suckEffect: 旧版面在屏幕下方中间位置被吸走, 显示出下面的新版面.
- spewEffect: 新版面在屏幕下方中间位置被释放出来覆盖旧版面.
- genieEffect: 旧版面在屏幕左下方或右下方被吸走, 显示出下面的新版面 (阿拉丁灯神?).
- unGenieEffect: 新版面在屏幕左下方或右下方被释放出来覆盖旧版面.
- twist: 版面以水平方向像龙卷风式转出来.
- tubey: 版面垂直附有弹性的转出来.
- swirl: 旧版面360度旋转并淡出, 显示出新版面.
- rippleEffect: 新版面以水波方式显示出来.
- cameraIris: 旧版面被镜头快门关走, 镜头快门然后开出新版面.
- cameraIrisHollow: 同上, 但旧版面在镜头快门没关时就消失了.
- cameraIrisHollowOpen: 镜头快门一开始已关上, 快门打开显示新版面.
- cameraIrisHollowClose: 镜头快门关上而并不打开.
- charminUltra: 旧版面淡出并显示新版面.
- zoomyIn: 新版面由小放大走到前面, 旧版面放大由前面消失.
- zoomyOut: 新版面屏幕外面缩放出现, 旧版面缩小消失.
- oglApplicationSuspend: 像按"home" 按钮的效果.
- oglFlip: 新版面转出来.

setSpeed 的参数, 可以由 0.0 (不动) 到大约 5.0 (马上出现), 数值越小越慢.

LKTimingFunction 的参数也是一个字符串, 可以是以下三个之一:

- easeInEaseOut: 前段和后段动画各占一半时间.
- easeIn: 后段动画较快.
- easeOut: 前段动画较快.




//我们怎样用 iphone 提供的功能做动画效果呢? 答案就是: UIClippedImageView!




//下面是设置一个翻转动画的过程:这里设置了两个动画


//我们先新建一个按钮,这个按钮背景可加图片,再把按钮给导航右键,在设置选择器动作事件; 当然,也可以直接在导航键按钮上给动画事件

UIBarButtonItem *flipButtonBarItem=[[UIBarButtonItem alloc] initWithCustomView:newButton];

[self.navigationItem setRightBarButtonItem:flipButtonBarItem animated:YES];
[flipButtonBarItem release];

[flipIndicatorButton addTarget:self action:@selector(flipCurrentView) forControlEvents:(UIControlEventTouchDown   )];



- (void)flipCurrentView {
	
	
	// 翻转期间不能互交
	containerView.userInteractionEnabled = NO;
	flipIndicatorButton.userInteractionEnabled = NO;
	
	// 设置动画
	[UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:0.75];
    [UIView setAnimationDelegate:self];
    [UIView setAnimationDidStopSelector:@selector(transitionDidStop:finished:context:)];
	
	// 交换视图并翻转
    if (frontViewIsVisible==YES) {
        [UIView setAnimationTransition:UIViewAnimationTransitionFlipFromRight forView:containerView cache:YES];
        [atomicElementView removeFromSuperview];
        [containerView addSubview:atomicElementFlippedView];
		
    }
	[UIView commitAnimations];
	
	//第二个动画:
	
	[UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:0.75];
    [UIView setAnimationDelegate:self];
    [UIView setAnimationDidStopSelector:@selector(transitionDidStop:finished:context:)];
	
	if (frontViewIsVisible==YES)
	{
		[UIView setAnimationTransition:UIViewAnimationTransitionFlipFromRight forView:flipIndicatorButton cache:YES];
		[flipIndicatorButton setBackgroundImage:element.flipperImageForAtomicElementNavigationItem forState:UIControlStateNormal];
	}
	else
	{
		[UIView setAnimationTransition:UIViewAnimationTransitionFlipFromLeft forView:flipIndicatorButton cache:YES];
		[flipIndicatorButton setBackgroundImage:[UIImage imageNamed:@"flipper_list_blue.png"] forState:UIControlStateNormal];
		
	}
	[UIView commitAnimations];
	frontViewIsVisible=!frontViewIsVisible;
}


- (void)transitionDidStop:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context {
	// re-enable user interaction when the flip is completed.
	containerView.userInteractionEnabled = YES;
	flipIndicatorButton.userInteractionEnabled = YES;
	
}




//下面介绍一种卷起的翻页效果,这视图下的两个子页间翻个效果是在一个

- (void)loadView {
	UIView *contentView = [[UIView alloc] initWithFrame:[[UIScreen mainScreen] applicationFrame]];
	self.view = contentView;
	[contentView release];
	
	UIView *frontView = [[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, 320.0f, 416.0f)];
	[self.view addSubview:frontView];
	
	isCurl=NO;
	self.navigationItem.rightBarButtonItem = [[[UIBarButtonItem alloc]
											   initWithTitle:@"Curl" 
											   style:UIBarButtonItemStylePlain 
											   target:self 
											   action:@selector(doCurl)] autorelease];
	
	
}



- (void) doCurl
{
	//创建CATransition对象
	CATransition *animation = [CATransition animation];
	//相关参数设置
	[animation setDelegate:self];
	[animation setDuration:1.0f];
	[animation setTimingFunction:UIViewAnimationCurveEaseInOut];
	//向上卷的参数
	if(!isCurl)
	{
		//设置动画类型为pageCurl，并只卷一半,我把0.5那个地方消去后,就是完全翻了
		[animation setType:@"pageCurl"];   
		//animation.endProgress=0.5;
	}
	//向下卷的参数
	else
	{
		//设置动画类型为pageUnCurl，并从一半开始向下卷
		[animation setType:@"pageUnCurl"];
		//animation.startProgress=0.5;
	}
	//卷的过程完成后停止，并且不从层中移除动画
	[animation setFillMode:kCAFillModeForwards];
	[animation setSubtype:kCATransitionFromBottom];
	[animation setRemovedOnCompletion:NO];
	
	isCurl=!isCurl;
	
	[self.view exchangeSubviewAtIndex:0 withSubviewAtIndex:1];
	[[self.view layer] addAnimation:animation forKey:@"pageCurlAnimation"];
	if([switchView isOn])
	{
		switchStatusLabel.text=@"ON";
	}
	else
	{
		switchStatusLabel.text=@"OFF";
	}
}


