//
//  1.m
//  基础教程的笔记
//
//  Created by spey on 10-9-12.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//


这个是我创建的xml文件，用于测试用的：
<?xml version="1.0" encoding="UTF-8"?>
<book>
<book1>
<author>zhangsan</author>
<title>Hello this is book1</title>
<content>book1 is very good for testing!</content>
</book1>
<book2>
<author>lisi</author>
<title>Hello this is book2</title>
<content>book2 is very good for testing!</content>
</book2>
<book3>
<author>wangwu</author>
<title>Hello this is book3</title>
<content>book3 is very good for testing!</content>
</book3>
</book>






对xml进行解析需要使用NSXMLParser类，首先声明一个NSXMLParser对象
NSXMLParser *xmlRead;

NSString *path = [[NSBundle mainBundle] pathForResource:@"test" ofType:@"xml"];
NSFileHandle *file = [NSFileHandle fileHandleForReadingAtPath:path];
NSData *data = [file readDataToEndOfFile];//得到xml文件
[file closeFile];
xmlRead = [[NSXMLParser alloc] initWithData:data];//初始化NSXMLParser对象
[data release];
[xmlRead setDelegate:self];//设置NSXMLParser对象的解析方法代理
BOOL success = [xmlRead parse];//调用代理解析NSXMLParser对象，看解析是否成功

//解析器，从两个结点之间读取内容
- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string {
	NSLog(string);
}
//获得结点结尾的值
- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName
namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName {
	NSLog(elementName);
}
//获得结点头的值
- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName
namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName
attributes:(NSDictionary *)attributeDict {
	NSLog(elementName);
}





Objective-C解析html(xml)全过程

iphone 2010-06-18 16:29:08 阅读286 评论0   字号：大中小 订阅
解析html和解析xml一样,可以用解析xml的方法来解析html,
NSString *path = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"parsefile.html"];
//获取文件路径
NSString *string=[[NSString  alloc]initWithContentsOfFile:paths encoding:NSUTF8StringEncoding error:nil];//获取文件内容
NSError *error;
DDXMLDocument *xmlDoc = [[DDXMLDocument alloc] initWithXMLString:string options:0 error:&error];//转换
if(xmlDoc)
{
    NSXMLElement *rootElement= [xmlDoc rootElement];//获取根节点
	
    NSXMLElement *bodyElement=[rootElement elementForName:@"body"];//从根节点中获取body节点
	
    NSArray *bodyList=[bodyElement elementsForName:@"div"];//body节点中获取div节点
	
	for (int textIndex=0 ; textIndex < [bodyList count] ; textIndex ++)
	{
		NSXMLElement *sub_title_list=(NSXMLElement *)[bodyList objectAtIndex:textIndex];
		
		NSString *headString=[[sub_title_list elementForName:@"h2"] stringValue];//获取头节点内容即<h2>标签内容
		//如果节点有多个就容数组存储
		NSArray *ptStringList=[sub_title_list elementsForName:@"p"];//获取p节点即p标签
		
		for(int i = 0 ; i < [textStringList count] ; i ++)
		{
			//第一种方式将NSXMLElement类型转换成NSString类型
			//        NSString *pString = @"";
			//        pString = [textString stringByAppendingString:[[ptStringList objectAtIndex:i] stringValue]];
			//第二种方式将NSXMLElement类型转换成NSString类型
			NSString * pString = @"";
			pString = [textString stringByAppendingString:[NSString stringWithFormat:@"%@",[ptStringList objectAtIndex:i]]];
			
		}
	}                
}










解析NSString形式xml的代码


解决方法：先转换成NSData，然后用NSXMlParser进行解析。代码：
- (void)handleXMLData {    
    NSString *myString = @"<addresses owner='swilson'><person><lastName>Doe</lastName><firstName>John</firstName></person></addresses>";
    NSData *myRequestData = [ NSData dataWithBytes: [myString UTF8String]  length:[myString length]];  
    NSXMLParser *myParser = [[NSXMLParser alloc] initWithData:myRequestData];
    [myParser setDelegate:self];
    [myParser setShouldProcessNamespaces:YES];
    [myParser setShouldReportNamespacePrefixes:YES];
    [myParser setShouldResolveExternalEntities:NO];
    BOOL success = [myParser parse];
    [myParser release];
	
	
