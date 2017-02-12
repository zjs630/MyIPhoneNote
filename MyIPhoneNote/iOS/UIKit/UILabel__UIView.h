1.文本视图
UIKit框架提供三个显示文本内容的基本类：
UILabel 显示静态文本字符串； UITextField 显示单行可编辑文本； UITextView 显
示多行可编辑文本。
在使用可编辑的文本视图时，您必须提供一个委托对象，负责管理编辑会话。文本视图
会向委托对象发送几个不同的通告，让它知道编辑何时开始，何时结束，并使它有机会
重载某些编辑动作。

//1，设置文本字体的大小
	[myLabel setFont:[UIFont systemFontOfSize:18.0f]];
	[myLabel setFont:[UIFont boldSystemFontOfSize:18]];//设置字体:粗体
//2,设置Label的文本
	[myLabel setText:@"HelloWorld"];
//3,设置Label背景颜色
	[myLabel setBackgroundColor:[UIColor clearColor]];//清除背景颜色
    scoreLabel.highlighted = YES;//设置文本是否高亮
    scoreLabel.highlightedTextColor = [UIColor orangeColor];//高亮时的颜色

//4，设置Label字体颜色
	[myLabel setTextColor:[UIColor redColor]];
	[headTitle setTextColor:[UIColor colorWithRed:0.9 green:0.9 blue:0.9 alpha:1.0]];
//5,设置Label文字对齐方式为居中
	[myLabel setTextAlignment:UITextAlignmentCenter];
//6,UILabel显示换行的方法
UILabel*label;

//设置换行
label.lineBreakMode = UILineBreakModeWordWrap; 
label.numberOfLines = 0;

换行符还是\n
比如NSString * xstring=@"lineone\nlinetwo"

记得要把label的高度设置的足够显示多行内容。

//7,设置是否能与用户进行交互
scoreLabel.userInteractionEnabled = YES;

//8,//设置label中的文字是否可变，默认值是YES
scoreLabel.enabled = NO;

7,让label自适应里面的文字，自动调整宽度和高度的
NSString *s = @"string......";
UIFont *font = [UIFont fontWithName:@"Arial" size:12];
CGSize labelsize = [s sizeWithFont:font constrainedToSize:CGSizeMake(200,2000) lineBreakMode:UILineBreakModeWordWrap];

UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, labelsize.width, labelsize.height)];
[label setNumberOfLines:0];//一定要设置此值为0
label.font = font;
label.text = s;
[self.view addSubview:label];

这样就可以对s赋值让其自动调整其大小了。

8,让文本自动缩小，以适应文本窗口的大小。
//设置字体大小是否适应label宽度
scoreLabel.adjustsFontSizeToFitWidth = YES;

9,iOS 6.0以后通过属性实现富文本效果
NSMutableAttributedString *str = [[NSMutableAttributedString alloc] initWithString:@"Hello. That is a test attributed string."];
[str addAttribute:NSBackgroundColorAttributeName value:[UIColor yellowColor] range:NSMakeRange(3,5)];
[str addAttribute:NSForegroundColorAttributeName value:[UIColor greenColor] range:NSMakeRange(10,7)];
[str addAttribute:NSFontAttributeName value:[UIFont fontWithName:@"HelveticaNeue-Bold" size:20.0] range:NSMakeRange(20, 10)];
_nameLabel.attributedText = str;

//9,显示阴影

//设置阴影的颜色和阴影的偏移位置
//scoreLabel.shadowColor = [UIColor redColor];
//scoreLabel.shadowOffset = CGSizeMake(1.0,1.0);

[headTitle.layer setShadowColor:[UIColor grayColor]];
[headTitle.layer setShadowOffset:CGSizeMake(-0.1, -1.0)];

//设置文字过长时的显示格式
scoreLabel.lineBreakMode = UILineBreakModeMiddleTruncation;//截去中间
//  typedef enum {
//     UILineBreakModeWordWrap = 0,
//      UILineBreakModeCharacterWrap,
//      UILineBreakModeClip,//截去多余部分
//      UILineBreakModeHeadTruncation,//截去头部
//      UILineBreakModeTailTruncation,//截去尾部
//      UILineBreakModeMiddleTruncation,//截去中间
//  } UILineBreakMode;
//如果adjustsFontSizeToFitWidth属性设置为YES，这个属性就来控制文本基线的行为

scoreLabel.baselineAdjustment = UIBaselineAdjustmentNone;
//  typedef enum {
//      UIBaselineAdjustmentAlignBaselines,
//      UIBaselineAdjustmentAlignCenters,
//      UIBaselineAdjustmentNone,
//  } UIBaselineAdjustment;

在使用UILabel存放字符串时，经常需要获取label的长宽数据，本文列出了部分常用的计算方法。

1.获取宽度，获取字符串不折行单行显示时所需要的长度

CGSize titleSize = [aString sizeWithFont:font constrainedToSize:CGSizeMake(MAXFLOAT, 30)];

注：如果想得到宽度的话，size的width应该设为MAXFLOAT。


2.获取高度，获取字符串在指定的size内(宽度超过label的宽度则换行)所需的实际高度.

CGSize titleSize = [aString sizeWithFont:font constrainedToSize:CGSizeMake(label.frame.size.width, MAXFLOAT) lineBreakMode:UILineBreakModeWordWrap];

注：如果想得到高度的话，size的height应该设为MAXFLOAT。
