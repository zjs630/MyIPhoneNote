1,NSSet,//Unordered collection of objects. and all of the objects have to be unique.不能重复，而NSArray可以重复

-(BOOL)containsObject:(id)anObject;//It returns a boolean whether this set contains this object.
-(id)anyObject;//它会从NSSet中随机返回一个对象。//It also returns nil if there are no objects in there.
-(void)makeObjectsPerformSelector:(SEL)aSelector;
-(id)member:(id)anObject;//查找集合中是否有这个对象，return a matching object。

2，NSMutableSet
-(void)addObject:(id)anObject;//[set addObject:object];
-(void)removeObject:(id)anObject;//[set removeObject:object];

//以下三个方法都是对集合的操作
-(void)unionSet:(NSSet *)otherSet;//合并集合//[set unionSet:anotherSet];
-(void)minusSet:(NSSet *)otherSet;//球集合交集//[set ninusSet:anotherSet];
-(void)intersectSet:(NSSet *)otherSet;

3,剔除NSArray中的重复元素。
NSArray *array = [NSArray arrayWithObjects:@"asss jc",@"gg ajb", @"jja", @"jja", @"jja",@"ddd",nil];
NSSet *uniqueElements = [NSSet setWithArray:array];
NSLog(@"%@",uniqueElements);

4

NSOrderedSet / NSMutableOrderedSet Sort of a cross between NSArray and NSSet.
Objects in an ordered set are distinct. You can’t put the same object in multiple times like array.
