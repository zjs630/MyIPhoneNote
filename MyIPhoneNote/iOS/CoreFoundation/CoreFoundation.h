1,CoreFoundation is a framework written in C.
2,内存管理
函数通过Create创建return a retained object. For example,ABAddressBookCreate();
应该：CFRelease;

3,Unlike Objective-c ,must NULL chedk CF type objects

CFStringRef string = CreateSomeCFString...;
if(string != NULL){
    
}
