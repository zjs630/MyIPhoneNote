1,iPhone软件启动后的第一屏图片是非常重要的往往就是loading载入中的意思。
设置它说来也简单，但是却无比重要,只需要在resource里面将你希望设置的图片更名为Default.png，
这个图片就可以成为iPhone载入的缺省图片

Default-Portrait.png iPad专用竖向启动画面 768x1024或者768x1004
Default-Landscape.png iPad专用横向启动画面 1024x768或者1024x748
Default-PortraitUpsideDown.png iPad专用竖向启动画面(Home按钮在屏幕上面)，可省略 768x1024或者768x1004
Default-LandscapeLeft.png iPad专用横向启动画面(可省略), 1024x768或者1024x748
Default-LandscapeRight.png iPad专用横向启动画面(可省略), 1024x768或者1024x748
Default.png iPhone默认启动图片，如果没有提供上面几个iPad专用启动图片，则在iPad上运行时也使用Default.png（不推荐） 320x480或者320x460
Default@2x.png iPhone4启动图片640x960或者640x920

为了在iPad上使用上述的启动画面，你还需要在xxxx_info.plist中加入key(根据下拉菜单中的可选项选择):
UISupportedInterfaceOrientations
或 Supported interface orientations
同时，为其加入值(根据下拉菜单中的可选项选择):
UIInterfaceOrientationPortrait 或 Portrait (bottom home button)
UIInterfacOrientationPortraitUpsideDown 或 Portrait (top home button)
UIInterfaceOrientationLandscapeLeft 或 Landscape (left home button)
UIInterfaceOrientationLandscapeRight 或 Landscape (right home button)

2,提交app到App store，需要的图片。

iPhone and iPod thouch:57*57，114*114像素的icon，which will be displayed on the home screen.
iPad:必须包含两个图标。50*50，72*72的icon。which will be displayed on the iPad home screen and App Store when viewed on the iPad.

除此之外，都必须包含一个512*512的icon。

3、iOS 4 引入了多任务支持，所以用户按下 “Home” 键以后程序可能并没有退出而是转入了后台运行。
如果您想让应用直接退出，最简单的方法是：
在 info－plist 里面找到 Application does not run in background 一项，勾选即可。