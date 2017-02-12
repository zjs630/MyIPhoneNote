1，A factory method is a class method that, as a convenience to clients, creates an instance of a class.

工厂方法allocation and initialization合成了一步，返回一个关于这个类的 autoreleased instance。
因为工厂方法创建的对象是autoreleased，所以客户端必须copy or retain the instance，如果你想它 persist in memory。

什么是工厂方法？

GOF是这样描述工厂模式的：
“Define an interface for creating an object, but let subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.”

在基类中定义创建对象的一个接口，让子类决定实例化哪个类。工厂方法让一个类的实例化延迟到子类中进行。

工厂方法要解决的问题是对象的创建时机，它提供了一种扩展的策略，很好地符合了开放封闭原则。工厂方法也叫做虚构造器（Virtual Constructor）。

什么时候使用工厂方法？
当是如下情况是，可以使用工厂方法：一个类不知道它所必须创建的对象的类时，一个类希望有它的子类决定所创建的对象时。