￼

NSRange
//C struct (not a class)
￼Used to specify subranges inside strings and arrays (et. al.).

typedef struct {
    NSUInteger location;
    NSUInteger length;
} NSRange;


1.Important location value NSNotFound.

NSString *greeting = @“hello world”;
NSString *hi = @“hi”;
NSRange r = [greeting rangeOfString:hi]; // finds range of hi characters inside greeting if (r.location == NSNotFound) { /* couldn’t find hi inside greeting */ }
NSRangePointer (just an NSRange * ... used as an out method parameter). There are C functions like NSEqualRanges(), NSMakeRange(), etc.

2.Strings
NSString *string = @"lorem ipsum dolor sit amet";
NSRange range = [string rangeOfString:@"ipsum"];
// {.location=6, .length=5}

NSString *substring = [string substringWithRange:range];
// @"ipsum"
3.Arrays
NSArray *array = @[@"a", @"b", @"c", @"d"];
NSArray *subarray = [array subarrayWithRange:NSMakeRange(1, 2)];
// @[@"b", @"c"]
4.index set
An NSIndexSet can be created from a range

NSRange range = NSMakeRange(0, 10);
NSIndexSet *indexSet = [NSIndexSet indexSetWithIndexesInRange:range];
5.创建NSRange

NSArray *array = @[@1, @2, @3];
NSRange range = NSMakeRange(0, [array count]);
// {.location=0, .length=3}
6.Querying Information

6-1
NSRange range1 = NSMakeRange(0, 6);
NSRange range2 = NSMakeRange(2, 7);
BOOL equal = NSEqualRanges(range1, range2); // NO 判断两个range是否相等

6-2 NSLocationInRange: Returns a Boolean value that indicates whether a specified position is in a given range.
NSRange range = NSMakeRange(3, 4);
BOOL contained = NSLocationInRange(5, range); // YES

6-3 NSMaxRange: Returns the sum of the location and length of the range.
NSRange range = NSMakeRange(3, 4);
NSUInteger max = NSMaxRange(range); // 7

6-4 NSIntersectionRange: Returns the intersection of the specified ranges. If the returned range’s length field is 0, then the two ranges don’t intersect, and the value of the location field is undefined.

NSRange range1 = NSMakeRange(0, 6);
NSRange range2 = NSMakeRange(2, 7);
NSRange intersectionRange = NSIntersectionRange(range1, range2);
// {.location=2, .length=4}
6-5 NSUnionRange: Returns the union of the specified ranges. A range covering all indices in and between range1 and range2. If one range is completely contained in the other, the returned range is equal to the larger range.

NSRange range1 = NSMakeRange(0, 6);
NSRange range2 = NSMakeRange(2, 7);
NSRange unionRange = NSUnionRange(range1, range2);
// {.location=0, .length=9}

7.Converting Between NSString * & NSRange

NSStringFromRange: Returns a string representation of a range.
NSRange range = NSMakeRange(3, 4);
NSString *string = NSStringFromRange(range); // @"{3,4}"

NSRangeFromString: Returns a range from a textual representation.
NSString *string = @"{1,5}";
NSRange range = NSRangeFromString(string);
// {.location=1, .length=5}

If the string passed into NSRangeFromString does not represent a valid range, it will return a range with its location and length set to 0.

NSString *string = @"invalid";
NSRange range = NSRangeFromString(string);
// {.location=0, .length=0}

While one might be tempted to use NSStringFromRange to box NSRange for inclusion within an NSArray, NSValue +valueWithRange: is the way to go:

NSRange range = NSMakeRange(0, 3);
NSValue *value = [NSValue valueWithRange:range];


网络相关
http://nshipster.com/nsrange/
