1. 对xml进行解析的标准有两种，sax以及dom。dom实现的原理是把整个xml文档一次性
读出，放在一个树型结构里。在需要的时候，查找特定节点，然后对节点进行读或写。
他的主要优势是实现简单，读写平衡；缺点是比较占内存，因为他要把整个xml文档都
读入内存，文件越大，这种缺点就越明显。sax的实现方法和dom不同。他只在xml文档
中查找特定条件的内容，并且只提取需要的内容。这样做占用内存小，灵活，正好满足
我们的需求。
2.对xml解析的方法有：NSXMLParser，libxml2，TBXML，TouchXML，KissXML，
TinyXML，GDataXML。
3,选择哪个呢？
　如果你只是想读小XML文档 ，性能并不重要，文件非常小。 你可能想选择使用XPath的支持和东西是在Objective - C语言编写的东西，使您的工作更容易。 所以我推荐这种情况下要么TouchXML，KissXML，或GDataXML。
　　如果你想同时读取和写入小XML文档 ，再次表现并不重要，功能多的和易用性。 你可能想选择使用XPath支持的时候，在Objective -C语言编写的，具有读/写能力。 因此，我建议你为这个案件KissXML或GDataXML。

　　如果你想阅读非常大的XML文件 ，性能是关键的问题在这里。 您将要考虑这个libxml2的SAX的，TBXML，或的libxml的DOM，这取决于你的具体情况。
　　那么那些我没有提到?
　　NSXML是一个不错的选择，如果你用相对较小的文件时，你不觉得像增加一个第三方库的SDK。
　　TinyXML的可能是一个大型文件确定选择中的API，如果你已经有经验的和为C舒适的港口，因为它很容易转移到iPhone。

一，使用NSXMLParser解析xml文件.//NSXMLParser 实现的是sax方法解析xml文件。

1. 设置委托对象，开始解析
NSXMLParser *parser = [[NSXMLParser alloc] initWithData:data];   //或者也可以使用initWithContentsOfURL直接下载文件，但是有一个原因不这么做：
// It's also possible to have NSXMLParser download the data, by passing it a URL, but this is not desirable
// because it gives less control over the network, particularly in responding to connection errors.
[parser setDelegate:self];
[parser parse];

2. 常用的委托方法
- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName 
namespaceURI:(NSString *)namespaceURI
qualifiedName:(NSString *)qName 
attributes:(NSDictionary *)attributeDict;
- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName 
namespaceURI:(NSString *)namespaceURI 
qualifiedName:(NSString *)qName;
- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string;
- (void)parser:(NSXMLParser *)parser parseErrorOccurred:(NSError *)parseError;

static NSString *feedURLString = @"http://www.yifeiyang.net/test/test.xml";

3.  应用举例
- (void)parseXMLFileAtURL:(NSURL *)URL parseError:(NSError **)error
{
	NSXMLParser *parser = [[NSXMLParser alloc] initWithContentsOfURL:URL];
	[parser setDelegate:self];
	[parser setShouldProcessNamespaces:NO];
	[parser setShouldReportNamespacePrefixes:NO];
	[parser setShouldResolveExternalEntities:NO];
	[parser parse];
	NSError *parseError = [parser parserError];
	if (parseError && error) {
		*error = parseError;
	}
	[parser release];
}

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI 
qualifiedName:(NSString*)qName attributes:(NSDictionary *)attributeDict{
	// 元素开始句柄
	if (qName) {
		elementName = qName;
	}
	if ([elementName isEqualToString:@"user"]) {
		// 输出属性值
		NSLog(@"Name is %@ , Age is %@", [attributeDict objectForKey:@"name"], [attributeDict objectForKey:@"age"]);
	}
}

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI 
qualifiedName:(NSString *)qName
{
	// 元素终了句柄
	if (qName) {
		elementName = qName;
	}
}

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string
{
	// 取得元素的text
}

NSError *parseError = nil;
[self parseXMLFileAtURL:[NSURL URLWithString:feedURLString] parseError:&parseError];