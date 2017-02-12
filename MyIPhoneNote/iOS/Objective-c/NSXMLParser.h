/*1,NSXMLParser is a forward only reader或一个事件驱动的解析器
(只能读取当前node‘s data and connot go back.)
	The iPhone only supports NSXMLParser and not NSXMLDocument,
which loads the whole XML tree in memory.
2,　NSXMLParser是一个SAX解析器SDK中包含的iPhone默认的。


3,
a,解析元素的开始， parser:didStartElement:namespaceURI:qualifiedName:attributes method
which is called when the parser encounters the start of an element.
b,当Parser moves to the element value and it sends parser:foundCharacters event to the
delegate.
c,当Parser移动到元素的结束， hence parser:didEndElement:namespaceURI:qualifiedName 
is sent to the delegate

 4，
 <?xml version= "1.0" encoding="UTF8">
 <article author="John Doe">
 <para>This is a very short article.</para>
 </article>
 The parser would report the following series of events to its delegate:
 •	Started parsing document
 •	Found start tag for element article －－－<article >
 •	Found attribute author of element article, value “John Doe”－－－－－author="John Doe"
 •	Found start tag for element para －－－－－<para>
 •	Found characters －－－－－－This is a very short article. 【 element's value】 
 •	Found end tag for element para－－－－－－</para>
 •	Found end tag for element article－－－－</article>
 •	Ended parsing document
 
       步骤一，确定从xml文件 解析出来的数据如何保存－－定义一个类（结构体）
                     小提示：可能一个xml文件解析出的数据包含多个对象，可以用NSMutableArray来保存。如参考一中提到的books
   步骤二，自定义解析处理方法（主要三个方法）－－Delegate代理
       为了使代码清晰 可以单独提出来作为一个类
方法一：
- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName
namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qualifiedName
attributes:(NSDictionary *)attributeDict {
	    /*
		      * 处理一：start tag for element 根据不同的元素名，创建不同的用于保存对应数据信息的对象（结构体）
		      * 处理二：attribute of the element 保存数据信息到对象（结构体）
		      
	if([elementName isEqualToString:@"Books"]) {
		//Initialize the array.
		appDelegate.books = [[NSMutableArray alloc] init];
	}
	aBook.bookID = [[attributeDict objectForKey:@"id"] integerValue];
}
/*方法二：主要处理element's value 主要一般都是如下处理保存value值到字符串

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string { 

if(!currentElementValue) 
currentElementValue = [[NSMutableString alloc] initWithString:string];
else
[currentElementValue appendString:string];

NSLog(@"Processing Value: %@", currentElementValue);

}

方法三：
- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName 
namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName {

if([elementName isEqualToString:@"Books"])
return;

//There is nothing to do if we encounter the Books element here.
//If we encounter the Book element howevere, we want to add the book object to the array
// and release the object.
if([elementName isEqualToString:@"Book"]) {
[appDelegate.books addObject:aBook];

[aBook release];
aBook = nil;
}
else 
[aBook setValue:currentElementValue forKey:elementName];

[currentElementValue release];
currentElementValue = nil;
}
    步骤三 获取xml文件，并建立NSXMLParser对象，后解析
如参考一中实例，从url获取xml文件，并实例化NSXMLParser对象
NSURL *url = [[NSURL alloc] initWithString:@"https://sites.google.com/site/iphonesdktutorials/xml/Books.xml"];
NSXMLParser *xmlParser = [[NSXMLParser alloc] initWithContentsOfURL:url];
//Initialize the delegate.实例化解析处理方法的代理（步骤二中定义的代理）
XMLParser *parser = [[XMLParser alloc] initXMLParser];

//Set delegate 设置NSXMLParser对象的解析方法代理
[xmlParser setDelegate:parser];

//Start parsing the XML file.调用代理解析NSXMLParser对象
BOOL success = [xmlParser parse];

if(success)
NSLog(@"No Errors");
else
NSLog(@"Error Error Error!!!");




