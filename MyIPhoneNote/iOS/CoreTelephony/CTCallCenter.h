1、捕获iphone通话事件：
CTCallCenter *center = [[CTCallCenter alloc] init];
center.callEventHandler = ^(CTCall *call) 
{
    NSLog(@"call:%@", call.callState);
}
