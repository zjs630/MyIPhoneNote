2. AVAudioPlayer 类

	AVAudioPlayer 是 AVFoundation.framework 中定义的一个类，
	所以使用要先在工程中引入 AVFoundation.framework。
	我们可以把 AVAudioPlayer 看作是一个高级的播放器，它支持广泛的音频格式，主要是以下这些格式：

	■ AAC
	■ AMR(AdaptiveMulti-Rate, aformatforspeech)
	■ ALAC(AppleLossless)
	■ iLBC(internetLowBitrateCodec, anotherformatforspeech)
	■ IMA4(IMA/ADPCM)
	■ linearPCM(uncompressed)
	■ µ-lawanda-law
	■ MP3(MPEG-1audiolayer3 
	  
	AVAudioPlayer 可以播放任意长度的音频文件、支持循环播放、可以同步播放多个音频文件、
	控制播放进度以及从音频文件的任意一点开始播放等，更高级的功能可以参考 AVAudioPlayer 的文档。
	要使用 AVAudioPlayer 的对象播放文件，你只需为其指定一个音频文件并设定一个实现了 
	AVAudioPlayerDelegate 协议的 delegate 对象。这里举一个简单的例子，
	和上一个例子一样，实现一直循环播放的背景音乐： 
	  - (void) playBackgroundSoundEffect {
		  NSString *soundFilePath = [[NSBundle mainBundle] pathForResource: @"background" ofType: @"wav"];
		  NSURL *fileURL = [[NSURL alloc] initFileURLWithPath: soundFilePath];
		  AVAudioPlayer *newPlayer =
		  [[AVAudioPlayer alloc] initWithContentsOfURL: fileURL error: nil];
		  [fileURL release];
		  self.player = newPlayer;
		  [newPlayer release];
		  [self.player prepareToPlay];
		  
		  [self.player setDelegate: self];
		  self.player.numberOfLoops = -1;    // Loop playback until invoke stop method
		  [self.player play];
	  }

		  AVAudioPlayer 同样支持 Callback，这是 AVAudioPlayerDelegate 的一个可选 delegate 方法：
		  - (void) audioPlayerDidFinishPlaying: (AVAudioPlayer *) player successfully: (BOOL) flag {
			  if (player == self.player && flag == YES) {
				  NSLog(@"Playback finish.");
			  }
		  }
		  
		  另外，你可以随时控制 AVAudioPlayer 对象的播放、暂停以及停止，通过判断对象的状态，分别调用 play、pause 和 stop 方法即可：
		  - (IBAction) playOrPause: (id) sender {
			  // if playing, pause
			  if (self.player.playing) {
				  [self.player pause];
				  // if stopped or paused, start playing
			  } else {
				  [self.player play];
			  }
			  
	  虽然 AVAudioPlayer 可以播放很多格式，但是我们在实际开发过程中还是最好使用一些没有压缩的格式，
	  比如 WAVE 文件，这样可以减少系统处理单元的资源占用，以便更好的完成程序的其他功能。
	  另外，在使用 AVAudioPlayer 连续播放 mp3 这类经过压缩的音频文件时，
	  在连接处可能出现一定的间隔时间。

2,播放声音
	  NSData *sound1 = [NSData dataWithContentsOfFile:[[[NSBundle mainBundle] bundlePath] stringByAppendingPathComponent:@"01.mp3"]];
	  NSError *error = nil;
	  AVAudioPlayer *player1 = [[AVAudioPlayer alloc] initWithData:sound1 error:&error];
	  [player1 prepareToPlay];
	  [player1 play];
			  
3，播放多个声音。
	  - (void)viewDidLoad 
	  {
		  [super viewDidLoad];
		  
		  NSData *sound1 = [NSData dataWithContentsOfFile:[[[NSBundle mainBundle] bundlePath] stringByAppendingPathComponent:@"01.mp3"]];
		  NSData *sound2 = [NSData dataWithContentsOfFile:[[[NSBundle mainBundle] bundlePath] stringByAppendingPathComponent:@"07.mp3"]];
		  
		  NSOperationQueue *queue = [[NSOperationQueue alloc] init];
		  NSError *error = nil;
		  
		  AVAudioPlayer *player1 = [[AVAudioPlayer alloc] initWithData:sound1 error:&error];
		  AVAudioPlayer *player2 = [[AVAudioPlayer alloc] initWithData:sound2 error:&error];
		  
		  NSInvocationOperation *op1 = [[[NSInvocationOperation alloc] initWithTarget:self selector:@selector(playSounds:) object:player1] autorelease];
		  
		  NSInvocationOperation *op2 = [[[NSInvocationOperation alloc] initWithTarget:self selector:@selector(playSounds:) object:player2] autorelease];
		  
		  [queue addOperation:op1];
		  [queue addOperation:op2];
		  
	  }
	  
	  - (void)playSounds:(id)data
	  {
		  AVAudioPlayer *player = (AVAudioPlayer *)data;
		  
		  [player prepareToPlay];
		  [player play];
	  }
			  








