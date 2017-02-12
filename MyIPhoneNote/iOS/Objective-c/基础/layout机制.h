1
//ioslayout机制相关方法
－(CGSize)sizeThatFits:(CGSize)size

- (void)sizeToFit

-------------------刷新子对象布局------------------

- (void)layoutSubviews

- (void)layoutIfNeeded

- (void)setNeedsLayout

-------------------重绘--------------------------------

- (void)setNeedsDisplay

- (void)drawRect

2.方法解释：


1）sizeToFit会自动调用sizeThatFits方法；

2）sizeToFit不应该在子类中被重写，应该重写sizeThatFits；

3）sizeThatFits传入的参数是receiver当前的size，返回一个适合的size；

4）sizeToFit可以被手动直接调用；

5）sizeToFit和sizeThatFits方法都没有递归，对subviews也不负责，只负责自己。
－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

1）-layoutSubviews方法：这个方法，默认没有做任何事情，需要子类进行重写。


2）-setNeedsLayout方法： 标记为需要重新布局，异步调用layoutIfNeeded刷新布局，不立即刷新，但layoutSubviews一定会被调用
。setNeedsLayout在receiver标上一个需要被重新布局的标记，在系统runloop的下一个周期自动调用layoutSubviews。

3）-layoutIfNeeded方法：layoutIfNeeded方法如其名，UIKit会判断该receiver是否需要layout.，根据Apple官方文应该是subviews链。如果有需要刷新的标记，立即调用layoutSubviews进行布局（档,layoutIfNeeded方法应该是这样的： layoutIfNeeded遍历的不是superview链，如果没有标记，不会调用layoutSubviews）。如果要立即刷新，要先调用[view setNeedsLayout]，把标记设为需要布局，然后马上调用[view layoutIfNeeded]，实现布局。在视图第一次显示之前，标记总是“需要刷新”的，可以直接调用[view layoutIfNeeded]。

－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

1）-drawRect:(CGRect)rect方法：重写此方法，执行重绘任务。


2）-setNeedsDisplay方法：标记为需要重绘，异步调用drawRect
。setNeedDisplay在receiver标上一个需要被重新绘图的标记，在下一个draw周期自动重绘，iphone device的刷新频率是60hz，也就是1/60秒后重绘。

3）-setNeedsDisplayInRect:(CGRect)invalidRect方法：标记为需要局部重绘。

四 .layoutSubviews总结


1.layoutSubviews在以下情况下会被调用：

1)、init初始化不会触发layoutSubviews

但是是用initWithFrame 进行初始化时，当rect的值不为CGRectZero时,也会触发

2)、addSubview会触发layoutSubviews

3)、设置view的Frame会触发layoutSubviews，当然前提是frame的值设置前后发生了变化

4)、滚动一个UIScrollView会触发layoutSubviews

5)、旋转Screen会触发父UIView上的layoutSubviews事件

6)、改变一个UIView大小的时候也会触发父UIView上的layoutSubviews事件

7) 、直接调用setLayoutSubviews。

2.在苹果的官方文档中强调:

You should override this method only if the autoresizingbehaviors of the subviews do not offer(提供) the behavior you want.

3.layoutSubviews, 当我们在某个类的内部调整子视图位置时，需要调用。

反过来的意思就是说：如果你想要在外部设置subviews的位置，就不要重写。

五.drawRect总结

1.drawRect在以下情况下会被调用：

1)、如果在UIView初始化时没有设置rect大小，将直接导致drawRect不被自动调用。drawRect调用是在Controller->loadView, Controller->viewDidLoad 两方法之后掉用的.所以不用担心在控制器中,这些View的drawRect就开始画了.这样可以在控制器中设置一些值给View(如果这些View在 draw的时候需要用到某些变量值).

2)、该方法在调用sizeToFit后被调用，所以可以先调用sizeToFit计算出size。然后系统自动调用drawRect:方法。

3)、通过设置contentMode属性值为UIViewContentModeRedraw。那么将在每次设置或更改frame的时候自动调用drawRect:。

4)、直接调用setNeedsDisplay，或者setNeedsDisplayInRect:触发drawRect:，但是有个前提条件是rect不能为0。

以上1,2推荐；而3,4不提倡

2.drawRect方法使用注意点：

1)、若使用UIView绘图，只能在drawRect：方法中获取相应的contextRef并绘图。如果在其他方法中获取将获取到一个invalidate(无效)的ref并且不能用于画图。drawRect：方法不能手动显示调用，必须通过调用setNeedsDisplay 或者 setNeedsDisplayInRect，让系统自动调该方法。

2)、若使用calayer绘图，只能在drawInContext: 中（类似于drawRect）绘制，或者在delegate中的相应方法绘制。同样也是调用setNeedDisplay等间接调用以上方法

3)、若要实时画图，不能使用gestureRecognizer，只能使用touchbegan等方法来掉用setNeedsDisplay实时刷新屏幕.


六. layoutSubviews ／setNeedsLayOut，drawRect／setNeedsDisplay

1.layoutSubviews方法，此方法，从字面上就很好解释“布局子视图”。根据苹果官方帮助文档对layoutSubviews方法的解释：此方法用来重新定义子元素的位置和大小； 当子类重写此方法，用来实现UI元素的更精确布局；如果要让布局重新刷新，那么就调用setNeedsLayout，即setNeedsLayout方法会默认用layoutSubViews方法。

2.layoutSubviews对subviews重新布局；drawRect方法主要用来画图，drawRect是对receiver的重绘，能获得context；layoutSubviews方法调用先于drawRect。


3.UIView的setNeedsDisplay和setNeedsLayout方法。首先两个方法都是异步执行的。setNeedsDisplay方法的作用是，告知需要重新显示。这样，界面就会重新被绘制，setNeedsDisplay会自动调用drawRect方法来实现view的绘制，这样可以拿到UIGraphicsGetCurrentContext，就可以画画了；而setNeedsLayout会默认调用layoutSubViews来实现view中subView的重新布局，可以处理子视图中的一些数据。


4.所以，当需要刷新布局时，用setNeedsLayOut方法；当需要重新绘画时，调用setNeedsDisplay方法。



七.需要知道的UIview的一些事情

1、在Mac OS中NSWindow的父类是NSResponder，而在iOS中UIWindow 的父类是UIVIew。程序一般只有一个窗口但是会又很多视图。

2、UIView的作用：描画和动画，视图负责对其所属的矩形区域描画、布局和子视图管理、事件处理、可以接收触摸事件、事件信息的载体等等。

3、UIViewController 负责创建其管理的视图及在低内存的时候将他们从内存中移除。还为标准的系统行为进行响应。


八.答疑


1.为什么不直接调用drawRect和layoutSubView，而要通过两个set方法，这样不是更麻烦吗，何必多次一举呢？

假设我们采用的是直接调用drawRect的机制，先考虑这样一个问题 ,现在有两个UIViewControllerA和B,A为当前view的viewController，如果此时在A中调用［B.view drawRect]，这样B的view无论如何都会调用drawRect的方法重新绘制一遍，这样问题就出来了，有必要吗，毕竟现在显示的是A中的view!B重新绘制一遍就调用了drawRect中的方法，完全是在浪费系统资源啊，而通过setNeedsDisplay,ios就会很聪明的判断出不需要调用drawRect的方法，这样就避免了资源的重复调用！（说白了，也就是ios底层的一种封装优化）

同理，setNeedsLayout也采用了同样的机制来避免资源的重复利用！

由此我们可以推断出这中设计的精妙之处，ios由很多精妙的设计来缓解手机资源不足的现状，比如cell的重复利用等等。


九.官方文档翻译：

1.有效使用视图的提示

当你需要绘制一些标准系统视图不能提供的内容时，定制视图是很有用的。但是你要负责保证视图的性能要足够的高。UIKit会尽可能的优化视图相关的行为，也会帮助你提高性能。然而，考虑一些提示可以帮助到UIKit。

重要：在调整绘制代码之前，你应该一直收集与你视图当前性能有关的数据。估量当前性能让你可以确定是否真的有问题，同时如果真的有问题，它也提供一个基线，让你在未来的优化中可以比较。

2.视图不会总是有一个相应的视图控制器

在应用中，视图和视图控制器之间的一对一关系是很少见的。视图控制器的工作是管理一个视图层次，而视图层次经常是包含了多个视图，它们都有自包含特性。对于iPhone应用，每个视图层次通常都填满了整个屏幕，尽管对于iPad应用来说不是。

当你设计用户界面的时候，考虑到视图控制器的所扮演的角色是很重要的。视图控制器提供了很多重要的行为，像协调视图的展示，协调视图的剔除，释放内存以响应低内存警告，还有翻转视图以响应界面的方向变更。逃避这些行为会导致应用发生错误。

获取更多关于视图控制器的信息，查看View Controller Programming Guide for iOS

3.最小化定制的绘画

尽管定制的绘画有时是需要的，但是你也应该尽量避免它。真正需要定制绘画的时候是已有的视图类无法提供足够的表现和能力时。任何时候你的内容都应该可以被组装到其他视图，最好结果时组合那些视图对象到定制的视图层次

4.利用内容模式

内容模式可以最小化重画视图要花费的时间。默认的，视图使用UIViewContentModeScaleToFill内容模式，这个模式会放缩视图的已有内容来填充视图的frame矩形。需要时你可以改变这个模式来调整你的内容，但是应该避免使用UIViewContentModeRedraw内容模式。不管哪个内容模式发生作用，你都可以调用setNeedsDisplay或者setNeedsDisplayInRect:方法来强制视图重画它的内容。

5.可能的话将视图声明为不透明

UIKit使用opaque属性来决定它是否可以优化组合操作。将一个定制视图的这个属性设置为YES会告诉UIKit不需要解释任何在该视图后的内容。这样可以为你的绘制代码提高性能并且是推荐的。当然，如果你将这个属性设置为YES，你的视图一定要用不透明的内容完全填充它的bounds矩形。

6.滚动时调整视图的绘制行为

滚动会导致数个视图在短时间内更新。如果视图的绘制代码没有被适当的调整，滚动的性能会非常的缓慢。相对于总是保证视图内容的平庸，我们更倾向于考虑滚动操作开始时改变视图行为。例如，你可以暂时减少已解释的内容，或者在滚动的时候改变内容模式。当滚动停止时，你可以将视图返回到前一状态，同时需要时更新内容。

7.不要嵌入子视图来定制控制

尽管在技术上增加子视图到标准系统控制对象－继承自UIControl的类－是可行的，你还是永远不应该用这种方法来定制它们。控制对象支持定制，它们有显式并且良好归档的接口。例如，UIButton类包含了设置标题和背景图片的方法。使用已定义好的定制点意味着你的代码总是会正确的工作。不用这些方法，而嵌入一个定制的图像视图或者标签到按钮中去会导致应用出现未预期的结果。

