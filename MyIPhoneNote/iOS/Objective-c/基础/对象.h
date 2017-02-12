一，复制对象
1，对于数组的直接赋值。//两个数组都是NSMutableArray对象。
dataArray2 = dataArray;／／仅复制的是对象的指针，两个数组指向一个内存单元。
[dataArray2 removeObjectAtIndex:0];
2，用类的coyp方法。//浅层复制
dataArray2 = ［dataArray mutableCopy];／／在内存中创建了一个新的dataArray副本，并复制了它的所有元素。
[dataArray2 removeObjectAtIndex:0];／／不会对dataArray产生影响。
3，Shallow Copies
（1）//Making a shallow copy
NSArray *shallowCopyArray = [someArray copyWithZone:nil];
NSDictionary *shallowCopyDict = [[NSDictionary alloc] initWithDictionary:someDictionary copyItems:NO];
（2）//Making a deep copy
NSArray *deepCopyArray=[[NSArray alloc] initWithArray:someArray copyItems:YES];
（3）//A true deep copy
NSArray* trueDeepCopyArray = [NSKeyedUnarchiver unarchiveObjectWithData:
                              [NSKeyedArchiver archivedDataWithRootObject:oldArray]];

二，访问当前对象
要获得当前对象的指针，可以使用self关键字。