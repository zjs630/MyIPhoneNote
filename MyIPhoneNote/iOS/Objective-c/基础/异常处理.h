@try {
    NSLog(@"This is some code that might raise an exception");
}
@catch (MyException *e){
    NSLog(@"Yep, something went wrong....%@", e);
}
@finally {
    NSLog(@"This is my cleanup code");
}

－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
@try {
    …
} 
@catch (NSException *e) {
    if ([[e …] isEqual: @"…"]) {
        …
    } else {
        @throw e;
    }
}

Cup *cup = [[Cup alloc] init];

－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
－－－－－－－－－－－－－－－－－－－－－－－－－－－－－


@try {
    [cup fill];
}
@catch (NSException *exception) {
    NSLog(@"main: Caught %@: %@", [exception name], [exception reason]);
}
@finally {
    [cup release];
}
