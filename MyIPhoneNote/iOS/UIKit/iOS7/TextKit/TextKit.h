1,步骤
http://esoftmobile.com/2013/10/17/text-kit%E8%BF%9B%E9%98%B6/#more
http://www.doubleencore.com/2013/09/text-kit-ios-7/
http://beyondvincent.com/blog/2013/11/12/121-brief-analysis-text-kit/#1


Text Kit四个特性：
1，动态字体（Dynamic type）
动态字体是iOS7中新增加的比较重要的特性之一，程序应该按照用户设定的字体大小和粗细来显示文本内容。
分别在设置\通用\辅助功能和设置\通用\文字大小中可以设置文本在应用程序中显示的粗细和大小。

2，凸版印刷体效果（Letterpress effects）
凸版印刷替效果是给文字加上奇妙阴影和高光，让文字看起有凹凸感，像是被压在屏幕上。当然这种看起来很高端大气上档次的效果实现起来确实相当的简单，只需要给AttributedString加一个NSTextEffectAttributeName属性，并指定该属性值为NSTextEffectLetterpressStyle就可以了。
//NSDictionary *attrs = @{ NSForegroundColorAttributeName : textColor,
//                         NSFontAttributeName : font,
//                         NSTextEffectAttributeName : NSTextEffectLetterpressStyle};

3，路径排除（Exclusion paths）
在排版中，图文混排是非常常见的需求，但有时候我们的图片并一定都是正常的矩形，这个时候我们如果需要将文本环绕在图片周围，就可以用路径排除（exclusion paths）了。
Explosion pats基本原理是将需要被文本留出来的形状的路径告诉文本控件的NSTextContainer对象，NSTextContainer在文字排版时就会避开该路径。
//UIBezierPath *floatingPath = [self pathOfImage];
//self.textView.textContainer.exclusionPaths = @[floatingPath];

4，动态文本格式化和存储（Dynamic text formatting and storage）

当你使用UITextView、UILabel、UITextField控件的时候，系统会自动创建上面这些类，你可以选择直接使用这么默认的实现或者为你的控件自定义这几个中的任何一个。
NSTextStorage本身继承与NSMutableAttributedString，它是以attributed string的形式保存需要渲染的文本，并在文本内容改变的时候通知到对应的layout manager对象。通常你需要创建NSTextStorage的子类来在文本改变时进行文本显示样式的更新。
NSLayoutManager作为文本控件中的排版引擎接收保存的文本并在屏幕上渲染出来。
NSTextContainer描述了文本在屏幕上显示时的几何区域，每个text container与一个具体的UITextView相关联。如果你需要定义一个很复杂形状的区域来显示文本，你可能需要创建NSTextContainer子类。
要实现我们上面描述的动态文本格式化功能，我们需要创建NSTextStorage子类以便在用户输入文本的时候动态的增加文本属性。自定义了text storage后，我们需要替换调UITextView默认的text storage。

