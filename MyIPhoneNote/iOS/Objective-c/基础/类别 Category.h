1, //a category allows you to add methods to an existing class without subclassing it or needing to know any of the details of how it's implemented.
//Unlike subclasses, categories can't add instance variables. You can, however, use categories to override existing methods in classes, but you should do so very carefully.

//Remember, when you make changes to a class using a category, it affects all instances of that class throughout the application.

可以通过类别为现有的类A添加新的方法（无须子类化即可扩展现有的类），与类不同的是类别的声明中没有实例变量部分，但分类可以访问原始类的实例变量。
	当需要使用类别中的方法时，可通过类A的对象直接调用。
	在分类中添加的方法，将被扩展类的所有子类继承，并且在运行时与原来编译进类中的方法没有区别。
添加的方法可以是实例方法，也可以是类方法。
//Categories have their own .h and .m files.(usually ClassName+PurposeOfExtension.[hm])
//Categories cannot have instance variables! 但是可以有properties.
2，类别的局限性
	①无法向类中添加新的实例变量，类别没有位置容纳实例变量。
	②名称冲突，即类别中的方法与现有的方法重名。当发生名称冲突时，类别具有更高的优先级。
3，类别的作用
	①将类的实现分散到多个不同文件或多个不同框架中。
	②创建对私有方法的向前引用。//将不想在interface部分显示的方法(如细节的实现方法)，放到类别中，消除编译器产生的警告。//已经过时了
	③向对象添加非正式协议。
4,利用类别可以声明非正式协议。
创建一个NSObject的一个类别，称为创建一个非正式协议，它可以列出对象能够响应的方法。非正式协议通常定义为NSObject的类别。
非正式协议用于实现委托，委托是一种允许你轻松定制对象行为的技术。
5，和一般接口不同的是，不必实现分类中的所有方法。
6，在类别中实现的方法总是会取代类自身中具有相同名称的方法的实现。若多个类别都实现了相同的方法，则无法保证将使用哪个实现。所以要近可能的避免方法名称冲突。

7,有一个约定俗称的名称：

8,我可以在categories中重写一个已经存在的方法吗？
//The answer is don't do that.That is really hard to understand for people reading your code,what you mean by that.So only add methods,dont't try to replace or otherwise,you know,use a same method.
9，创建类别，如果我用一个空文件，填写类别的东西，oc是怎么知道他是一个category呢？
系统根据 类名(words)来判断是否是个类别。when you go new file in category,that's just a convenience.
你当然可以自己创建一个空文件，自己些代码，creta new file in category 更简便些。






一，匿名类别//class Extension
与其它类别不同的是：
首先，匿名类别的声明，在圆括号里没有类名称。
其次，每个类最多只能有一个匿名类别。
最后，匿名类别中声明的方法必须实现，否则有警告错误。
extension可以添加属性。

//引入extension的目的主要是Publicly-Readable, Privately-Writeable Properties，即实现外部只读，内部可写。
//extension中声明的方法是私有的，只有主implement能调用，外部的类无法调用。
 //extension 和 category 都不能定义新的实例变量。但extension可以定义新的property，然后在main implementation里@synthesize 新的property。而category定义新的property却不能@synthesize，这时可以使用Associative References技术实现对新定义的property的getter和setter。

在C和OC里，方法不能在还没有声明之前被调用。现在这句话不完全正确了。
由于Xcode4.3的出现，编译器已经足够智能，可以在源文件里面找到正确的方法定义了。这意味着什么？更少的代码量。
你现在可以把类扩展中的私有方法声明全部移除掉了。


类扩展现在只有属性，不在有方法名字了。从Xcode4.3开始私有方法需要前置声明已经成为历时。有是一个大大节约时间的特性。
