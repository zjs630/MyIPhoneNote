

static NSString *actionNames[] = {
	@"EaseIn",//有慢至快
	@"EaseOut",//由快至慢
	@"EaseInOut",//由慢至快再由快至慢
	@"EaseSineIn",//由慢至快。
	@"EaseSineOut",//由快至慢
	@"EaseSineInOut",//由慢至快再由快至慢。
	@"EaseExponentialIn",//由慢至极快。
	@"EaseExponentialOut",//由极快至慢。
	@"EaseExponentialInOut",//由慢至极快再由极快至慢。
	@"Speed" //人工设定速度,还可通过 SetSpeed 丌断调整。
};

- (id) init
{
	self = [super init];
	if (self)
	{
		// Add action menue
		[CCMenuItemFont setFontName:@"Arial"];
		// Add Control Items
		[CCMenuItemFont setFontSize:16];
		
		
		CCMenuItem *backMenu = [CCMenuItemFont itemFromString:@"Back" target:self selector:@selector(OnBackMenue:)];
		
		CCMenu *mn = [CCMenu menuWithItems:backMenu, nil];
		
		int actCount = sizeof(actionNames) / sizeof(actionNames[0]) ;
		int i;
		
		for (i = 0; i < actCount; i++) {
			NSString *aName = actionNames[i];
			NSLog(@"%@",aName);
			CCMenuItem *pItm = [CCMenuItemFont itemFromString:aName target:self selector:@selector(OnAction:)];
			[mn addChild:pItm z:1 tag:i];
		}
		
		[mn alignItemsVertically];
		
		//		mn.anchorPoint = ccp(0,1);
		mn.position = ccp(100, mn.position.y);
		
		[self addChild:mn z:1 tag:2];
		
		
		CCSpriteSheet *mgr = [CCSpriteSheet spriteSheetWithFile:@"flight.png" capacity:3];
		[self addChild:mgr z:0 tag:4];
		
		sprite = [CCSprite spriteWithTexture:mgr.texture rect:CGRectMake(32 * 2,0,31,30)];
		[mgr addChild:sprite z:1 tag:5];
		
		sprite.scale = 2.0;
		sprite.position = ccp(s.width/2, 50);
	}
	
	return self;
}

- (void) OnAction:(id) sender
{
	id ac1 = [CCMoveBy actionWithDuration:2 position:ccp(200, 200)];
	id ac2 = [ac1 reverse];
	id ac = [CCSequence actions:ac1,ac2,nil];
	
	int na = [sender tag];
	switch (na) {
		case 0:
			[sprite runAction:[CCEaseIn actionWithAction:ac rate:3]];
			break;
		case 1:
			[sprite runAction:[CCEaseOut actionWithAction:ac rate:3]];
			break;
		case 2:
			[sprite runAction:[CCEaseInOut actionWithAction:ac rate:3]];
			break;
		case 3:
			[sprite runAction:[CCEaseSineIn actionWithAction:ac]];
			break;
		case 4:
			[sprite runAction:[CCEaseSineOut actionWithAction:ac]];
			break;
		case 5:
			[sprite runAction:[CCEaseSineInOut actionWithAction:ac]];
			break;
		case 6:
			[sprite runAction:[CCEaseExponentialIn actionWithAction:ac]];
			break;
		case 7:
			[sprite runAction:[CCEaseExponentialOut actionWithAction:ac]];
			break;
		case 8:
			[sprite runAction:[CCEaseExponentialInOut actionWithAction:ac]];
			break;
		case 9:
			[sprite runAction:[CCSpeed actionWithAction:ac speed:(CCRANDOM_0_1() * 5)]];
			break;
		default:
			break;
	}
	
}
