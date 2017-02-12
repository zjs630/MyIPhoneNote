1,非标准协议NSKeyValueCoding，是一个用于间接访问对象属性的机制。
使用该机制不需要调用存取方法和变量实例就可访问对象属性。
2，使用键值编码可以简化代码。
//ChildObject *child = [childrenArray objectAtIndex:row];
//return [child valueForKey:[column identifier]];
3,键和键路径
键是一个标示对象某个属性的字符串。通常，一个键与接收对象的一个访问器方法或是实例变量对应。
键必须使用ASCII编码，以小写字母开头，并且不能包含空格。
例如，键可以是payee, openingBalance, transactions和amount。

键路径是一串由点隔开的键，用于指定一组对象属性序列。序列中第一个键的属性与接收者相关，其他后续键则是相对于前一个属性的值。
比如，键路径address.street将会从接收方对象获得address属性的值，之后依据address对象确定street的属性。
4,获取属性值
方法valueForKey:返回接收对象特定键的值。
方法valueForKeyPath:返回接收对象特定键路径的值。
方法dictionaryWithValuesForKeys:得到接收对象的一组键的值。被返回的NSDictionary包含了数组中所有键的值。
5,设定属性值
方法setValue:forKey:用于将接收对象的特定键设定为所提供的值。
方法setValue:forKeyPath:该方法既可以处理键路径，也可以处理单独的键。
setValuesForKeysWithDictionary:使用指定字典中的具体值设定接收对象的属性，并使用字典键来识别这些属性。默认的方法是为每一对键-值调用setValue:forKey:，并按需要将nil替换为NSNull 对象。
/*使用KVC来访问实例中的属性：
MyClass *myInstance = [[MyClass alloc] init];
NSString *string = [myInstance valueForKey:@"stringProperty"];
[myInstance setValue:[NSNumber numberWithInt:2] forKey:@"integerProperty"];
*/
6,键-值编码为标量和数据结构提供了以自动包装和解包NSNumber和NSValue中的值为基础的支持。

