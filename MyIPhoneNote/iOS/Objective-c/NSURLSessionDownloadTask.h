1,下载，不要在主线程中下载。

NSURLRequest *request = [NSURLRequest requestWithURL:[NSURL urlWithString:@"http://..."]];
NSURLConfiguration *configuration = ...;
NSURLSession *session = ...;
NSURLSessionDownloadTask *task;
task = [session downloadTaskWithRequest:request
                    completionHandler:^(NSURL *localfile, NSURLResponse *response, NSError *error) {
                        ￼/* want to do UI things here, can I? */ }];
[task resume];//开始下载任务

//
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//注
The completionHandler block above might execute on the main thread (or not)! depending on how you create the NSURLSession.!
//On the main queue ...!
NSURLSession *session = [NSURLSession sessionWithConfiguration:configuration
                                                      delegate:nil
                                                 delegateQueue:[NSOperationQueue mainQueue]];
你可以在completionHandler中更行UI
//Off the main queue ...!
NSURLSession *session = [NSURLSession sessionWithConfiguration:configuration]; // no delegateQueue
NSURLSessionDownloadTask *task;
task = [session downloadTaskWithRequest:request
                      completionHandler:^(NSURL *localfile, NSURLResponse *response, NSError *error) {
                          dispatch_async(dispatch_get_main_queue(), ^{ /* do UI things */ });
                          //or [self performSelectorOnMainThread:@selector(doUIthings) withObject:nil waitUntilDone:NO];
                      }];
[task resume];