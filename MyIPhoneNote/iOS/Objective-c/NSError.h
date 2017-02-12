1，
NSError *anyError;
BOOL success = [receivedData writeToURL:someLocalFileURL
                                options:0
                                  error:&anyError];
if (!success) {
    NSLog(@"Write failed with error: %@", anyError);
    // present error to user
}

//If you’re not interested in the error object,just pass NULL for the error: parameter.
2，创建你自己的Errors
NSString *domain = @"com.MyCompany.MyApplication.ErrorDomain";
NSString *desc = NSLocalizedString(@"Unable to...", @"");
NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };
NSError *error = [NSError errorWithDomain:domain
                                     code:-101
                                 userInfo:userInfo];

- (BOOL)doSomethingThatMayGenerateAnError:(NSError **)errorPtr {
    ...
    // error occurred
    if (errorPtr) {
        *errorPtr = [NSError errorWithDomain:...
                                        code:...
                                    userInfo:...];
    }
    return NO;
}