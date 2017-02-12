/* 使用 BMP 字体显示游戏时间
CCBitmapFontAtlas *lbScore = [CCBitmapFontAtlas bitmapFontAtlasWithString:@"Time: 0" fntFile:@"font09.fnt"];
lbScore.anchorPoint = ccp(1.0, 1.0);//右上角
lbScore.scale = 0.6;//缩放
lbScore.position = ccp(320, 480);//右上角
[self addChild:lbScore z:1 tag:3];
 
 Bitmap字体对游戏来说是个非常好的选择,因为它的速度很快。不过它有
 一个很大的缺点:任何bitmap的字体大小都是固定的。
 
 因为你需要添加bitmapfont.fnt和配套的
 bitmapfont.png两个文件,两个文件都要放在项目的Resources文件夹中。这两 
 个文件一般需要你自己创建。

如何创建这些文件?
 我们使用的工具叫Hiero,开发者是Kevin James Glass。
 它是一个免费的Java Web程序,你可以在这里找到它:
 http://slick.cokeandcode.com/demos/hiero.jnlp

如果你希望使用另外的程序,可以试一下BMFont。不过 
 BMFont是个Windows程序,它需要在Windows平台上运行。
 这也是为什么在Mac开 发者社区里没有得到广泛应用的原因。
 你可以在这里下载BMFont: http://www.angelcode.com/products/bmfont/

 学习更多关于Hiero的用法,你可以查看我网站上的教程:
 http://www.learn-cocos2d.com/knowledge-base/tutorialbitmap-fonts-hiero/