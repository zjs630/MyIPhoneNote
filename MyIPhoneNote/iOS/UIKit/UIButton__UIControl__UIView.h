1,添加一个按钮
UIButton *button = [[UIButton alloc] initWithFrame:CGRectMake(20, 20, 120, 37)]; 
button.titleLabel.text = @"Do it!"; 
[window addSubview:button]; 
[button release];
2,添加一个圆角按钮,并添加事件。
	UIButton *btn= [UIButton buttonWithType:UIButtonTypeRoundedRect];
	btn.frame = CGRectMake(20, 20, 80, 30);//[btn setFrame:CGRectMake(20, 20, 80, 30)];//设置按钮的位置，大小
	[btn setTitle:@"放大" forState:UIControlStateNormal];//设置按钮的标题
	//[btn setBackgroundColor:[UIColor redColor]];设置按钮的背景色
	//[btn setCenter:CGPointMake(90.0f, 90.0f)];//重新设置按钮的位置
	//[btn setEnabled:NO];//设为不能使用，即不能触发点击事件
	[btn addTarget:self action:@selector(buttonClicked:) forControlEvents:UIControlEventTouchUpInside];//为按钮添加事件。
3,添加自定义按钮。
       
		UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];//定义按钮显示类型。
        button.frame = CGRectMake(0.0, 0.0, buttonUpImage.size.width, buttonUpImage.size.height);//定义坐标位置及显示的大小。
		[button setTitle:@"未按" forState:UIControlStateNormal];//设置按钮的标题。
		[button setTitle:@"已按" forState:UIControlStateHighlighted];//设置按钮按下的标题。
		[button setBackgroundImage:[UIImage imageNamed:@"button_up.png"] forState:UIControlStateNormal];//设置正常模式下按钮的背景图片。
        [button setBackgroundImage:[UIImage imageNamed:@"button_down.png"] forState:UIControlStateHighlighted];//设置按下按钮时的背景图片。

		[button setImage:[UIImage imageNamed:@"soundON.png"] forState:UIControlStateNormal];//若图片大小小于按钮大小，则居中显示。
		[button setImage:[UIImage imageNamed:@"soundOFF.png"] forState:UIControlStateSelected];

		button.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;//对齐
		button.contentHorizontalAlignment = UIControlContentHorizontalAlignmentCenter;

//		button.font = [UIFont boldSystemFontOfSize:12.0f]; 过时了
        button.titleLabel.font = [UIFont systemFontOfSize: 14.0];

        [button addTarget:self action:@selector(buttonTapped:) forControlEvents:UIControlEventTouchUpInside];
/*
 * 默认情况下，当按钮高亮的情况下，图像的颜色会被画深一点，如果这下面的这个属性设置为no，
 * 那么可以去掉这个功能
 */
button.adjustsImageWhenHighlighted = NO;
/*跟上面的情况一样，默认情况下，当按钮禁用的时候，图像会被画得深一点，设置NO可以取消设置*/
button.adjustsImageWhenDisabled = NO;
/* 下面的这个属性设置为yes的状态下，按钮按下会发光*/
button.showsTouchWhenHighlighted = YES;


4,得到Button的title
UIButton *but = [[UIbutton alloc] init];
[but setTitle:@"title" forState:UIControlStateNormal];
[but addTarget:self action:@selector(click:) forControlEvents:UIControlEventTouchUpInside];
-(void)click:(id)sender
{
	NSString *s = [sender titleForState:UIControlStateNormal];//获得按钮对象在初始化的状态。
} 
5，判断按下的是哪个按钮。
先给每个按钮设置tag,
然后定义一个操作方法,比如,
-(void)buttonPressed:(id)sender
在操作方法里加上:   int i = [sender tag];
得到的 i 就是你按下的按钮的标记值,通过这个值就可以知道按下哪个按钮了.
6,//按钮的类型

UIBarButtonSystemItemAdd
UIBarButtonSystemItemAction, 
UIBarButtonSystemItemBookmarks, 
UIBarButtonSystemItemCamera, 
UIBarButtonSystemItemCancel, 
UIBarButtonSystemItemCompose, 
UIBarButtonSystemItemDone, 
UIBarButtonSystemItemEdit, 
UIBarButtonSystemItemFastForward, 
UIBarButtonSystemItemFixedSpace, 
UIBarButtonSystemItemFlexibleSpace, 
UIBarButtonSystemItemOrganize, 
UIBarButtonSystemItemPause, 
UIBarButtonSystemItemPlay, 
UIBarButtonSystemItemRedo, 
UIBarButtonSystemItemRefresh, 
UIBarButtonSystemItemReply, 
UIBarButtonSystemItemRewind,
UIBarButtonSystemItemSave, 
UIBarButtonSystemItemSearch, 
UIBarButtonSystemItemStop, 
UIBarButtonSystemItemTrash, 
UIBarButtonSystemItemUndo

7,UIButton 防止多按钮同时按下

将按钮得每个ExclusiveTouch属性设置为YES即可。

[b1 setExclusiveTouch:YES];

[b2 setExclusiveTouch:YES];
