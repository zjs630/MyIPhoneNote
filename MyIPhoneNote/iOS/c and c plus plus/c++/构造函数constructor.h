1,构造函数是有用户定义的，函数名必须于类名相同。
	构造函数不需用户调用，而是在定义一个对象时由系统自动执行，而且只能执行一次。
2，在Objective-c中，我们也可以使用构造方法，它是在创建对象的时候用来初始化对象中的数据的一种特殊方法。
构造方法可以以任何方法命名，但通常，将他们命名为init。
构造方法返回指向对象的一个指针，我们可以通过调用超类的init方法来获得这个指针。
-(Container *)init:(int)n{
    self = [super init];
    if(self){
        [self setNumber:n];
    }
    return self;
}
//向构造方法传值。
Container *object = [[Container new] init:3];