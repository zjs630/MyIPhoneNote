iOS sdk中可以使用MPMoviePlayerController来播放电影文件。
但是在iOS设备上播放电影文件有严格的格式要求，只能播放下面两个格式的电影文件。

• H.264 (Baseline Profile Level 3.0)
• MPEG-4 Part 2 video (Simple Profile)
如：H.264/M4V/MP4/MOV/MPEG-4/AVI/3GP等格式

幸运的是你可以先使用iTunes将文件转换成上面两个格式。
MPMoviePlayerController还可以播放互联网上的视频文件。
但是建议你先将视频文件下载到本地，然后播放。如果你不这样做，iOS可能会拒绝播放很大的视频文件。

1，如何播放视频，使用MediaPlayer库來播放影片
导入MediaPlayer.framework
#import <MediaPlayer/MediaPlayer.h>
//点击播放按钮
-(void)playMovie:(NSString *)fileName{
    //视频文件路径
    NSString *path = [[NSBundle mainBundle] pathForResource:fileName ofType:@"mp4"];
    //视频URL
    NSURL *url = [NSURL fileURLWithPath:path];
    //视频播放对象
    MPMoviePlayerController *moviePlayer = [[MPMoviePlayerController alloc] initWithContentURL:url];
    moviePlayer.controlStyle = MPMovieControlStyleFullscreen;//设置视频控制按钮的样式，还有MPMovieControlStyleNone，MPMovieControlStyleEmbedded
    /* Scale the movie player to fit the aspect ratio */
    //movie.scalingMode = MPMovieScalingModeAspectFit;
    [moviePlayer.view setFrame:CGRectMake(0, 80, 320, 200)];
    moviePlayer.initialPlaybackTime = -1;
    // 注册一个播放结束的通知
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(myMovieFinishedCallback:)
                                                 name:MPMoviePlayerPlaybackDidFinishNotification
                                               object:moviePlayer];
    [moviePlayer play];
    [self.view addSubview:moviePlayer.view];
    //设置全屏播放
//    [self.moviePlayer setFullscreen:YES animated:YES];

}

//视频播放结束调用的方法
-(void)myMovieFinishedCallback:(NSNotification*)notify{
    /* Find out what the reason was for the player to stop */
    NSNumber *reason =
    [paramNotification.userInfo valueForKey:MPMoviePlayerPlaybackDidFinishReasonUserInfoKey];
    if (reason != nil){
        NSInteger reasonAsInteger = [reason integerValue];
        switch (reasonAsInteger){
            case MPMovieFinishReasonPlaybackEnded:{
                /* The movie ended normally */
                break; }
            case MPMovieFinishReasonPlaybackError:{
                /* An error happened and the movie ended */ break;
            }
            case MPMovieFinishReasonUserExited:{
                /* The user exited the player */
                break; }
        }
        NSLog(@"Finish Reason = %ld", (long)reasonAsInteger);
        //视频播放对象
        MPMoviePlayerController* theMovie = [notify object];
        //销毁播放通知
        [[NSNotificationCenter defaultCenter] removeObserver:self
                                                        name:MPMoviePlayerPlaybackDidFinishNotification
                                                      object:theMovie];
        [theMovie.view removeFromSuperview];
        // 释放视频对象
        [theMovie release];
    }
}

//点击停止播放按钮
- (void) stopPlayingVideo:(id)paramSender {
    if (self.moviePlayer != nil){
        [[NSNotificationCenter defaultCenter] removeObserver:self name:MPMoviePlayerPlaybackDidFinishNotification object:self.moviePlayer];
        [[NSNotificationCenter defaultCenter]
         removeObserver:self name:MPMoviePlayerThumbnailImageRequestDidFinishNotification object:self.moviePlayer];
        [self.moviePlayer stop];
        if ([self.moviePlayer.view.superview isEqual:self.view]){
            [self.moviePlayer.view removeFromSuperview];
        }
    }
}
//如果你想显示全屏的播放，还可以使用MPVovePlayerViewController类，

2，用MPMoviePlayerController播放视频文件时，获取视频缩略图
（1）首先在播放时添加通知。
[[NSNotificationCenter defaultCenter] addObserver:self
                                         selector:@selector(videoThumbnailIsAvailable:)
                                             name:MPMoviePlayerThumbnailImageRequestDidFinishNotification object:self.moviePlayer];

（2）Use the requestThumbnailImagesAtTimes:timeOption: instance method of MPMovie PlayerController like so:

NSArray *requestedThumbnails = [NSArray arrayWithObject:[NSNumber numberWithFloat:3.0f]];
/* Ask the movie player to capture this frame for us */
[self.moviePlayer requestThumbnailImagesAtTimes:requestedThumbnails timeOption:MPMovieTimeOptionExact];
（3）
//获取视频缩略图
- (void)videoThumbnailIsAvailable:(NSNotification *)paramNotification
{
    MPMoviePlayerController *controller = [paramNotification object];
    
    if ((controller != nil) &&
        [controller isEqual:moviePlayer]) {
        NSLog(@"Thumbnail is available");
        /* Now get the thumbnail out of the user info dictionary */
        UIImage *thumbnail = [paramNotification.userInfo
                              objectForKey:MPMoviePlayerThumbnailImageKey];
        
        if (thumbnail != nil) {
            /* We got the thumbnail image. You can now use it here */
        }
    }
}
3，使用AVPlayer來播放影片

NSString *filePath = [[NSBundle mainBundle] pathForResource:@"backspace" ofType:@"mov"];
NSURL *sourceMovieURL = [NSURL fileURLWithPath:filePath];

AVAsset *movieAsset	= [AVURLAsset URLAssetWithURL:sourceMovieURL options:nil];
AVPlayerItem *playerItem = [AVPlayerItem playerItemWithAsset:movieAsset];
AVPlayer *player = [AVPlayer playerWithPlayerItem:playerItem];
AVPlayerLayer *playerLayer = [AVPlayerLayer playerLayerWithPlayer:player];
playerLayer.frame = self.view.layer.bounds;
playerLayer.videoGravity = AVLayerVideoGravityResizeAspect;

[self.view.layer addSublayer:playerLayer];
[player play];











