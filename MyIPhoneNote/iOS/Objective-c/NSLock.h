1,NSLock的使用。
-(void)init{
    myLock = [[NSLock alloc] init];
}

-(void)someMethod{
    [myLock lock];
    //We only want one thread executing this code at once
    [myLock unlock];
}
2，Conditions are the other type of Lock.
NSCondition is useful for producer/consumer model.
你有一个线程生产数据，另外一个线程尝试去消耗它。

//On the producer thread
-(void)produceData{
    [condition lock];
    //Produce new data
    newDataExists = YES;//设置一个flag，说明数据可用。
    
    [condition signal];//告诉consumer有数据可用。
    [condition unlock];
}

//On the consumer thread
-(void)consumeData{
    [condition lock];
    while(!newDataExists){//While there's no data available,it's going to call conditin wait

        [condition wait];
        //它是3个基础行为的集合。它会先unlock，并执行wait，然后当其它线程发新号给它，它会从等待中出来并再次取得那个锁lock。
    }
    //Consume the new data
    newDataExists = NO;
    [condition unlock];
}
















