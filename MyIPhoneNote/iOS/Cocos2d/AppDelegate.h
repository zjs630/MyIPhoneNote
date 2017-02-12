1,AppDelegate 对象通过实现UIApplicationDelegate协议，来实现当前应用程序需要处理的各种系统事件。
 放弃控制权:applicationWillResignActive //[[CCDirector sharedDirector] pause];
 获得控制权:applicationDidBecomeActive //[[CCDirector sharedDirector] resume];
 内存报警:applicationDidReceiveMemoryWarning //[[CCTextureCache sharedTextureCache] removeUnusedTextures];
 程序退出提示:applicationWillTerminate //[[CCDirector sharedDirector] end];
 系统时间变化:applicationSignificantTimeChange //[[CCDirector sharedDirector] setNextDeltaTimeZero:YES];

在完成刜始处理之后,通过凼数 applicationDidFinishLaunching 将
程序的控制权传递给 Cocos2D类库,Cocos2D接下来开始准备启动 游戏主画面的准备:
1.	获得主窗口对象(句柄)由成员 window 保存。 
2.	将 Cocos2D-iPhone 的“导演”对象与之绊定。
3. 设置“导演”对象的基本属性。
4. 由“导演”对象创建“场景”。
5. 将内容展示对象“层”加入当前“场景”。
6. 由导演对象启动幵运行“场景”。

a,创建场景//CCScene *scene = [CCScene node];
b,创建层//HelloWorld *layer = [HelloWorld node];  //注：HelloWorld : CCLayer类
c,将层添加到新建的场景中//[scene addChild: layer];
d，通过导演对象运行新建的场景//[[CCDirector sharedDirector] runWithScene: [HelloWorld scene]];

2，通过 Director 对象设置主程序窗口的显示属性。
--设置主窗口方向。(垂直迓是水平)//[[CCDirector sharedDirector] setDeviceOrientation:CCDeviceOrientationLandscapeLeft];
--设定游戏动画每秒显示桢数。(默认是 60 帧) //[[CCDirector sharedDirector] setAnimationInterval:1.0/60];
--是否显示 FPS。(每秒显示的帧数)//[[CCDirector sharedDirector] setDisplayFPS:NO];
--设定主窗口显示图像的调色盘位宽。//[CCTexture2D setDefaultAlphaPixelFormat:kTexture2DPixelFormat_RGBA8888];
