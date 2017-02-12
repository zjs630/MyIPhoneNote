
//  Created by Zhangjingshun on 11-11-1.
//  Copyright 2011 __MyCompanyName__. All rights reserved.

// create and initialize a Label
CCLabelTTF *label = [CCLabelTTF labelWithString:@"Hello World" fontName:@"Marker Felt" fontSize:64];
// ask director the the window size
CGSize size = [[CCDirector sharedDirector] winSize];

// position the label on the center of the screen
label.position =  ccp( size.width /2 , size.height/2 );

// add the label as a child to this Layer
[self addChild: label];

label.tag = 13;//这样你就可以通过tag来找到它。

-(void) ccTouchesBegan:(NSSet*)touches withEvent:(UIEvent*)event; {
    CCLabelTTF* label = (CCLabelTTF*)[self getChildByTag:13]; 
    label.scale = CCRANDOM_0_1();//通过点击屏幕，让文字随机变大变小。
}


