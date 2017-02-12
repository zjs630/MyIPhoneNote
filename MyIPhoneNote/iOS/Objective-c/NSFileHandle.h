1，拷贝大文件
-(void)startCopy{
    NSString *homePath = NSHomeDirectory();
    NSString *srcPath = [homePath stringByAppendingPathComponent:@"a.mp4"];
    NSString *targetPath = [homePath stringByAppendingPathComponent:@"a_bak.mp4"];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    //创建目标文件
    BOOL success = [fileManager createFileAtPath:targetPath contents:nil attributes:nil];
    if (success) {
        NSLog(@"file create success");
    }
    //读取文件对象
    NSFileHandle *inFile = [NSFileHandle fileHandleForReadingAtPath:srcPath];
    //写文件对象
    NSFileHandle *outFile = [NSFileHandle fileHandleForWritingAtPath:targetPath];
    NSDictionary *fileAttri = [fileManager attributesOfItemAtPath:srcPath error:nil];
    NSNumber *fileSizeNum = [fileAttri objectForKey:NSFileSize];
    
    BOOL isEnd = YES;
    float readSize = 0;
    float fileSize = [fileSizeNum floatValue];
    NSAutoreleasePool *pool = nil;
    int n = 0;
    
    while (isEnd) {
        if (n%10 == 0) {
            [pool release];
            pool =  [[NSAutoreleasePool alloc] init];
        }
        
        //计算剩下未读文件的大小
        NSInteger subLength = fileSize -readSize;
        NSData *data = nil;
        if (subLength <5000) {//如果剩余文件小于5000，则将剩下的数据全部读完，并且不再循环读取
            isEnd = NO;
            data = [inFile readDataToEndOfFile];
        }
        else{
            data = [inFile readDataOfLength:5000];
            readSize +=5000;
            [inFile seekToFileOffset:readSize];
        }
        
        //
        [outFile writeData:data];
        NSLog(@"%.2lf",readSize/fileSize);
        n++;
    }
    [outFile closeFile];//关闭文件
    
}

