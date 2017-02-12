在cocos2d里播放音频 最好也是最简单的方式是使用SimpleAudioEngine。
音频支持不是cocos2d自带 的功能;它来自CocosDenshion,和物理引擎一样
是cocos2d的第三方插件。出 于这个原因,你必须在使用音频功能的地方包含相
应的CocosDenshion头文件, 如下所示:

#import "SimpleAudioEngine.h"
//For music, MP3 files are the preferred choice. 
[[SimpleAudioEngine sharedEngine] playBackgroundMusic:@"blues.mp3" loop:YES];
//For sound effects, I’ve had only good experiences with the CAF format.
[[SimpleAudioEngine sharedEngine] playEffect:@"alien-sfx.caf"];