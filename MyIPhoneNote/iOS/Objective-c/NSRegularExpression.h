1 在ios4.0中正则表达式的使用是使用NSRegularExpression类来调用。
// 如果在检索的文本中需要检索包含正则表达式的关键字,如 "[ ]" 那么在 拼装字符串时 需要加两个反斜杠(\\[)进行转义识别,否则会误判的
//在iOS中的正则表达式字符串  不需要左右侧加 /

                                                         
//http+:[^\\s]* 这个表达式是检测一个网址的。
//<a[^<]+href="course_play.html\?url=([^\"]+)">
//<a[^<]+href="([^\"]+)">
NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:@"http+:[^\\s]*" options:0 error:&error];

2，并设置检测对象范围为：0-9
NSRegularExpression *regex2 = [NSRegularExpression regularExpressionWithPattern:@"^[0-9]*$" options:0 error:nil];
3，匹配9-15个由字母/数字组成的字符串的正则表达式：
NSString * regex = @"^[A-Za-z0-9]{9,15}$";

1:NSRegularExpression 案例一. 在HTML字符串中 找寻出完整的 <img> 标签.   包含  /> 和 </img> 结尾两种情况


4，http://www.xuebuyuan.com/1787815.html