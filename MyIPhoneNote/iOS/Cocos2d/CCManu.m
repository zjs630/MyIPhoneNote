1,设置菜单列表
[CCMenuItemFont setFontName:@"Marker Felt"];//设置字体
[CCMenuItemFont setFontSize:25];//设置字体大小
//创建5个菜单项，逐一设置列表内容，及点击触发的函数。//生成文字标签
CCMenuItem *newGame = [CCMenuItemFont itemFromString:@"新游戏" target:self selector:@selector(newGame:)];
CCMenuItem *loadGame = [CCMenuItemFont itemFromString:@"旧的回忆" target:self selector:nil];
CCMenuItem *GameSttings = [CCMenuItemFont itemFromString:@"设置" target:self selector:@selector(OnSettings:)];
CCMenuItem *helpGame = [CCMenuItemFont itemFromString:@"帮助" target:self selector:nil];
CCMenuItem *quitGame = [CCMenuItemFont itemFromString:@"退出" target:self selector:@selector(onQuit:)];
//将5个菜单子项加入菜单对象，CCMenu对象可以添加的数据项有CCMenuItem,CCMenuItemToggle,CCMenuItemLabel类的对象。
//CCMenu只支持CCMenuItem作为它的子节点。
CCMenu *mn = [CCMenu menuWithItems:newGame, loadGame, GameSttings, helpGame, quitGame, nil];

[mn alignItemsVertically];//设置排列方式，纵向布局。

[self addChild:mn z:1 tag:2];//添加到场景中，系统才会显示

2，设置某一菜单项的位置。

CCMenuItem *systemMenu = [CCMenuItemFont itemFromString:@"菜单" target:self selector:@selector(sysMenue:)];
CCMenu *mn = [CCMenu menuWithItems:systemMenu, nil];
mn.position = ccp(0,0);
// 手工设置菜单位置在左下角
systemMenu.anchorPoint = ccp(0, 0);
systemMenu.position = ccp(0, 0);//设置位置
//将菜单项添加到层中
[self addChild:mn z:1 tag:2];
3，设置菜单选项开关。
CCMenuItemToggle *item1 = [CCMenuItemToggle itemWithTarget:self selector:@selector(menuCallback:) items:
						   [CCMenuItemFont itemFromString: @"开"],
						   [CCMenuItemFont itemFromString: @"关"],
						   nil];
4，使用已有的精灵生成一个菜单项。
//利用图片文件 生成菜单项,内部实际上使用了CCSprite来实现。
CCSprite *sprite = [CCSprite spriteWithFile:@"Icon-72.png"];
sprite.color = ccRED;
CCSprite *selected = [CCSprite spriteWithFile:@"Icon-72.png"];
selected.color = ccGREEN;
CCMenuItemSprite *item2 = [CCMenuItemSprite itemFromNormalSprite:sprite selectedSprite:selected target:self selector:nil];

4,只显示文字
CCMenuItemFont *title4 = [CCMenuItemFont itemFromString: @"难度"];
[title4 setIsEnabled:NO];

5,设置菜单选项开关包含多个值
// 设置多选项效果。首先加入一个子选项(subItems),再加入一个包吨了多个子菜单的数组。
CCMenuItemToggle *item4 = [CCMenuItemToggle itemWithTarget:self selector:@selector(menuCallback:) items:
						   [CCMenuItemFont itemFromString: @"妈妈的宝贝"], nil];

NSArray *more_items = [NSArray arrayWithObjects:
					   [CCMenuItemFont itemFromString: @"菜鸟"],
					   [CCMenuItemFont itemFromString: @"高手"],
					   [CCMenuItemFont itemFromString: @"骨灰级"],
					   nil];
// TIP: you can manipulate the items like any other NSMutableArray
[item4.subItems addObjectsFromArray: more_items];
item4.selectedIndex = 0;//显示第一项

6,CCMenuItemLabel的使用
CCBitmapFontAtlas *label = [CCBitmapFontAtlas bitmapFontAtlasWithString:@"Go back" fntFile:@"font01.fnt"];
CCMenuItemLabel *back = [CCMenuItemLabel itemWithLabel:label target:self selector:@selector(backCallback:)];
back.scale = 1.8;







