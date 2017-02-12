一、音频文件的加载
1,在项目中添加AudioToolbox.Frameworks
2,代码：
NSString *path = [[NSBundle mainBundle] pathForResource:@"crunch" ofType:@"wav"];//获取音频文件路径 
SystemSoundID soundID;//声明变量

CFURLRef sound1URL = (CFURLRef)[NSURL fileURLWithPath:path1];//将路径转换为CFURLRef
AudioServicesCreateSystemSoundID(sound1URL, &sound1);//加载音频文件并与指定soundID联系起来 
/*或者
 AudioServicesCreateSystemSoundID((CFURLRef) [NSURL fileURLWithPath:path],&soundID);//将路径转换为CFURLRef 
 */

AudioServicesPlaySystemSound(soundID);//在需要播放的地方加入



20. 官方 API 触发 iPhone 振动的代码
如果您想在应用里添加提示功能，比如让 iPhone 机身震动，可以使用下面这行代码： AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);

19.iPhone 播放 midi 文件的方法
iPhone 默认不带播放MIDI的框架，所以播放MIDI还得寻求第3方的库帮忙。这里使用的库就是大名鼎鼎的 FMOD ,许多火爆游戏使用的都是这个库。开发者可以免费下载使用。
首先下载安装 FMOD API FOR IPHONE：http://www.fmod.org/index.php/release/version/fmodapi42607iphone-installer.dmg。安装后可以在目录中看到不少示范代码，可惜没有MIDI。
自己写一个：）
感谢强大的api，写起来异常轻松。
* 新建一个基于view项目
* 修改项目属性，添加 Other Linker Flags 为 -lfmodexL_$PLATFORM_NAME
* 添加 Header Search Paths ：/Developer/FMOD\ Programmers\ API\ iPhone/api/inc  （默认是这个位置，修改成自己FMOD安装的目录）
* 添加 Library Search Paths ：/Developer/FMOD\ Programmers\ API\ iPhone/api/lib （同上）
* 把 appDelegate 修改成 .mm 的后缀
* MIDI 播放需要一个 DLS 文件， 在osx 下没找到，这里使用了xp 自带的 gm.dls 文件（3M 有点大～）,拷贝到项目中。
* 修改ViewController 代码如下 ，随便在xib文件中链接两个按钮action上即可
* 运行（真机有效）

主要代码

//
//  PlayMidiDemoViewController.m
//  PlayMidiDemo
//
//  Created by xhan on 9/9/09.
//  Copyright In-Blue 2009. All rights reserved.
//

#import "PlayMidiDemoViewController.h"

@implementation PlayMidiDemoViewController
@synthesize status;
@synthesize time;

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        fprintf(stderr, "FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}
- (void)viewDidLoad {
    [super viewDidLoad];
    system = NULL;
    sound1  = NULL;
    sound2  = NULL;
    channel = NULL;    
}
- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}
- (void)viewDidUnload {
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}
- (void)dealloc {
    [status release], status = nil;
    [time release], time = nil;
    [super dealloc];
}
- (void)viewWillAppear:(BOOL)animated
{
    FMOD_RESULT   result        = FMOD_OK;
    char          buffer[200]   = {0};
    unsigned int  version       = 0;
    
    /*
     Create a System object and initialize
     */    
    result = FMOD::System_Create(&system); 
    ERRCHECK(result);    
    result = system->getVersion(&version);
    ERRCHECK(result);
    
    if (version < FMOD_VERSION)
    {
        fprintf(stderr, "You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        exit(-1);
    }
    
    result = system->init(32, FMOD_INIT_NORMAL | FMOD_INIT_ENABLE_PROFILE, NULL);
    ERRCHECK(result);
    
    // set up DLS file
    FMOD_CREATESOUNDEXINFO   soundExInfo;
    memset(&soundExInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    soundExInfo.cbsize   = sizeof(FMOD_CREATESOUNDEXINFO);
    char dlsName[200] = {0};
    [[NSString stringWithFormat:@"%@/gm.dls", [[NSBundle mainBundle] resourcePath]] getCString:dlsName maxLength:200 encoding:NSASCIIStringEncoding];    
    soundExInfo.dlsname  = dlsName;    
    
	// midi one
    [[NSString stringWithFormat:@"%@/Bass_sample.mid", [[NSBundle mainBundle] resourcePath]] getCString:buffer maxLength:200 encoding:NSASCIIStringEncoding];    
	
    result = system->createSound(buffer, FMOD_SOFTWARE | FMOD_CREATESTREAM, &soundExInfo, &sound1);
	
	//    ERRCHECK(result);
    
    result = sound1->setMode(FMOD_LOOP_OFF);
	//    ERRCHECK(result);
    
    // midi two
    [[NSString stringWithFormat:@"%@/Drum_sample.mid", [[NSBundle mainBundle] resourcePath]] getCString:buffer maxLength:200 encoding:NSASCIIStringEncoding];    
    
    result = system->createSound(buffer, FMOD_SOFTWARE | FMOD_CREATESTREAM, &soundExInfo, &sound2);
    result = sound2->setMode(FMOD_LOOP_OFF);    
	
    
	//    timer = [NSTimer scheduledTimerWithTimeInterval:0.05 target:self selector:@selector(timerUpdate:) userInfo:nil repeats:YES];
}

- (IBAction)playSound1:(id)sender
{
    FMOD_RESULT result = FMOD_OK;
    
    result = system->playSound(FMOD_CHANNEL_FREE, sound1, false, &channel);
    ERRCHECK(result);
}


- (IBAction)playSound2:(id)sender
{
    FMOD_RESULT result = FMOD_OK;
    
    result = system->playSound(FMOD_CHANNEL_FREE, sound2, false, &channel);
    ERRCHECK(result);    
}

- (void)timerUpdate:(NSTimer *)timer 
{
    
}