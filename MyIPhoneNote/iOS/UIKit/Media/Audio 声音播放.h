iPhone OS 主要提供以下了几种播放音频的方法：
    * System Sound Services
    * AVAudioPlayer 类
    * Audio Queue Services
    * OpenAL

System Sound Services 是最底层也是最简单的声音播放服务，
调用 AudioServicesPlaySystemSound 这个方法就可以播放一些简单的音频文件，
使用此方法只适合播放一些很小的提示或者警告音，因为它有很多限制：

    ■ 声音长度要小于 30 秒
    ■ In linear PCM 或者 IMA4 (IMA/ADPCM) 格式的
    ■ 打包成 .caf, .aif, 或者 .wav 的文件
    ■ 不能控制播放的进度
    ■ 调用方法后立即播放声音
    ■ 没有循环播放和立体声控制
另外，它还可以调用系统的震动功能，方法也很简单。具体的代码可以参考官方的示例 SysSound，
但是官方的示例只有一些简单的用法，从文档中我们发现可以通过 
AudioServicesAddSystemSoundCompletion 方法为音频播放添加 CallBack 函数，
有了 CallBack 函数我们可以解决不少问题，比如可以克服 System Sound Services 本身不支持循环播放的问题。
以下代码可以实现一个在程序中循环播放的背景音乐：
/*
	 static void completionCallback (SystemSoundID  mySSID) {
	 // Play again after sound play completion
	 AudioServicesPlaySystemSound(mySSID);
	 }
	 
	 - (void) playSound {
	 // Get the main bundle for the app
	 CFBundleRef mainBundle;
	 SystemSoundID soundFileObject;
	 mainBundle = CFBundleGetMainBundle ();
	 
	 // Get the URL to the sound file to play
	 CFURLRef soundFileURLRef  = CFBundleCopyResourceURL (
	 mainBundle,
	 CFSTR ("background"),
	 CFSTR ("wav"),
	 NULL
	 );
	 // Create a system sound object representing the sound file
	 AudioServicesCreateSystemSoundID (
	 soundFileURLRef,
	 &soundFileObject
	 );
	 // Add sound completion callback
	 AudioServicesAddSystemSoundCompletion (soundFileObject, NULL, NULL,
	 completionCallback,
	 (void*) self);
	 // Play the audio
	 AudioServicesPlaySystemSound(soundFileObject);
 
 }
 
 */



1，按钮播放声音         播放短声音
a,添加AudioToolbox.framework.需要导入框架#import <AudioToolbox/AudioToolbox.h>
b,导入声音文件后，添加如下代码：
	NSString *path = [[NSBundle mainBundle] pathForResource:@"win" ofType:@"wav"];//创建音乐文件路径。
    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID((CFURLRef)[NSURL fileURLWithPath:path], &soundID);//变量SoundID与URL对应 
	AudioServicesPlaySystemSound(soundID);//播放声音


	或者用下面的代码
	//sound initialization
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	CFURLRef soundFileURLRef = CFBundleCopyResourceURL(mainBundle, (CFStringRef)@"win", CFSTR("wav"), NULL);
	 SystemSoundID soundID;
	AudioServicesCreateSystemSoundID(soundFileURLRef, &soundID);
	AudioServicesPlaySystemSound(soundID);//播放声音
	
2、AudioToolbox可以支持的音频格式有：wav，mp3，caf，wma
3、背景音乐播放    支持mp3格式 循环播放长音乐
添加AVFoundation.framework.
这种播放音乐的方式导入框架#import <AVFoundation/AVFoundation.h>；

	NSString *musicFilePath = [[NSBundle mainBundle] pathForResource:@"changan" ofType:@"mp3"]; //创建音乐文件路径
	NSURL *musicURL = [[NSURL alloc] initFileURLWithPath:musicFilePath];  

	AVAudioPlayer *thePlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:musicURL error:nil];


	//创建播放器
	self.myBackMusic = thePlayer;    //赋值给自己定义的类变量
  
	[musicURL release];
	[thePlayer release];
  
	[myBackMusic prepareToPlay];
	[myBackMusic setVolume:1];   //设置音量大小
	myBackMusic.numberOfLoops = -1;//设置音乐播放次数  -1为一直循环
	if (mainMusicStatus)
	{
		[myBackMusic play];   //播放
	}
4,从网上加载声音。
	NSString* urlString = [@"http://translate.google.com/translate_tts?q=" stringByAppendingString:word.text];
	NSURL* url = [[NSURL alloc] initWithString:[urlString stringByReplacingOccurrencesOfString:@" " withString:@"+"]];
	NSData* mp3Data = [[NSData alloc] initWithContentsOfURL:url];
	AVAudioPlayer* player = [[AVAudioPlayer alloc] initWithData:mp3Data error:nil];
	[player play];
