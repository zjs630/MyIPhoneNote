1,iPhone设置字体样式及使用方法
IPhone 所支持的字体：

* "Courier"
* "AppleGothic"  
* "Arial"
* "STHeiti TC"
* "Hiragino Kaku Gothic ProN"
* "Courier New"
* "Zapfino"
* "Arial Unicode MS"
* "STHeiti SC"
* "American Typewriter"
* "Helvetica"
* "Marker Felt"
* "Helvetica Neue"
* "DB LCD Temp"
* "Verdana"
* "Times New Roman"
* "Georgia"
* "STHeiti J"
* "Arial Rounded MT Bold"
* "Trebuchet MS"
* "STHeiti K"

UIFont *tFont = [UIFont fontWithName:[[UIFont fontNamesForFamilyName:@"Helvetica"] objectAtIndex:N] size:17];
//UIFont *tFont = [UIFont fontWithName:@"Arial" size:18];
[textLabel setFont:tFont];
//textLabel.font = tFont;

//    [countdownLabel setFont:[UIFont fontWithName:@"DBLCDTempBlack" size:128.0]];//设置LCD字体。

每一种FamilyName都是个Array类型的变量，N一般取0基本没有错误，如果N取其他数，且Array里没有那么多，则报错.

设置字体大小
myTextField.font = [UIFont systemFontOfSize:17.0];
myTextField.font = [UIFont boldSystemFontOfSize: 17.0f];设置为粗体
myTextField.font = [UIFont italicSystemFontOfSize:17.0];
2.
使用以下代码可以获得系统的所有字体。
NSArray *familyNames = [UIFont familyNames];
for( NSString *familyName in familyNames ){
	printf( "Family: %s \n", [familyName UTF8String] );
	NSArray *fontNames = [UIFont fontNamesForFamilyName:familyName];
	for( NSString *fontName in fontNames ){
		printf( "\tFont: %s \n", [fontName UTF8String] );
	}
} 我从iPhone中获得了下面的这些字体：
Family: Hiragino Kaku Gothic ProN W3 
Font: HiraKakuProN-W3 
Family: Courier 
Font: Courier 
Font: Courier-BoldOblique 
Font: Courier-Oblique 
Font: Courier-Bold 
Family: Arial 
Font: ArialMT 
Font: Arial-BoldMT 
Font: Arial-BoldItalicMT 
Font: Arial-ItalicMT 
Family: STHeiti TC 
Font: STHeitiTC-Light 
Font: STHeitiTC-Medium 
Family: AppleGothic 
Font: AppleGothic 
Family: Courier New 
Font: CourierNewPS-BoldMT 
Font: CourierNewPS-ItalicMT 
Font: CourierNewPS-BoldItalicMT 
Font: CourierNewPSMT 
Family: Zapfino 
Font: Zapfino 
Family: Hiragino Kaku Gothic ProN W6 
Font: HiraKakuProN-W6 
Family: Arial Unicode MS 
Font: ArialUnicodeMS 
Family: STHeiti SC 
Font: STHeitiSC-Medium 
Font: STHeitiSC-Light 
Family: American Typewriter 
Font: AmericanTypewriter 
Font: AmericanTypewriter-Bold 
Family: Helvetica 
Font: Helvetica-Oblique 
Font: Helvetica-BoldOblique 
Font: Helvetica 
Font: Helvetica-Bold 
Family: Marker Felt 
Font: MarkerFelt-Thin 
Family: Helvetica Neue 
Font: HelveticaNeue 
Font: HelveticaNeue-Bold 
Family: DB LCD Temp 
Font: DBLCDTempBlack 
Family: Verdana 
Font: Verdana-Bold 
Font: Verdana-BoldItalic 
Font: Verdana 
Font: Verdana-Italic 
Family: Times New Roman 
Font: TimesNewRomanPSMT 
Font: TimesNewRomanPS-BoldMT 
Font: TimesNewRomanPS-BoldItalicMT 
Font: TimesNewRomanPS-ItalicMT 
Family: Georgia 
Font: Georgia-Bold 
Font: Georgia 
Font: Georgia-BoldItalic 
Font: Georgia-Italic 
Family: STHeiti J 
Font: STHeitiJ-Medium 
Font: STHeitiJ-Light 
Family: Arial Rounded MT Bold 
Font: ArialRoundedMTBold 
Family: Trebuchet MS 
Font: TrebuchetMS-Italic 
Font: TrebuchetMS 
Font: Trebuchet-BoldItalic 
Font: TrebuchetMS-Bold 
Family: STHeiti K 
Font: STHeitiK-Medium 
Font: STHeitiK-Light

iphone上预装了下列字体:

American Typewriter
Apple Gothic
Arial
Arial  Ronuded MT Bold
Courier
Courier New
Georgia
Helvetica
Helvetica Neue
Marker Felt
Times 
Times New Roman
Trebuchet MS
Verdana
Zapfino

UIFont

It is best to get a UIFont by asking for the preferred font for a given text style ... UIFont *font = [UIFont preferredFontForTextStyle:UIFontTextStyleBody];
Some other styles (see UIFontDescriptor documentation for even more styles) ... UIFontTextStyleHeadline, UIFontTextStyleCaption1, UIFontTextStyleFootnote, etc.
There are also “system” fonts.
They are used in places like button titles.
+ (UIFont *)systemFontOfSize:(CGFloat)pointSize;
+ (UIFont *)boldSystemFontOfSize:(CGFloat)pointSize; You should never uses these for your user’s content.
Use preferredFontForTextStyle: for that.



UIFontDescriptor

Fonts are designed by artists.
They aren’t always designed to fit any sort of categorization. Some fonts have Narrow or Bold or Condensed faces, some do not. Even “size” is sometimes a designed-in aspect of a particular font.
A UIFontDescriptor attempts to categorize a font anyway.
It does so by family, face, size, and other attributes.
You can then ask for fonts that have those attributes and get a “best match.”
Understand that a best match for a “bold” font may not be bold if there’s no such designed face.
You can get a font descriptor from an existing UIFont with this UIFont method ...
- (UIFontDescriptor *)fontDescriptor;
You might well have gotten the original UIFont using preferredFontForTextStyle:.
Then you might modify it to create a new descriptor with methods in UIFontDescriptor like ...
- (UIFontDescriptor *)fontDescriptorByAddingAttributes:(NSDictionary *)attributes;
(the attributes and their values can be found in the class reference page for UIFontDescriptor) You can also create a UIFontDescriptor directly from attributes (though this is rare) using ...
+ (UIFontDescriptor *)fontDescriptorWithFontAttributes:(NSDictionary *)attributes;

UIFontDescriptor *scriptFontDescriptor = [UIFontDescriptor fontDescriptorWithFontAttributes:
                                          @{UIFontDescriptorFamilyAttribute: @"Zapfino",
                                            UIFontDescriptorSizeAttribute: @15.0}
                                          ];
self.scriptTextLabel.font = [UIFont fontWithDescriptor:scriptFontDescriptor size:0.0];


3,ios中不支持中文倾斜，于是只有设置倾斜角度。

CGAffineTransform matrix =  CGAffineTransformMake(1, 0, tanf(15 * (CGFloat)M_PI / 180), 1, 0, 0);

UIFontDescriptor *desc = [ UIFontDescriptor fontDescriptorWithName :[ UIFont systemFontOfSize :17 ]. fontName matrix :matrix];

font = [ UIFont fontWithDescriptor :desc size :17];


第一行代码：设置反射。倾斜15度。

第二行代码：取得系统字符并设置反射。

第三行代码：获取字体。

上面的代码，通过舍子font的f可以实现，可以实现中文斜体。后面可以用

[string. text drawInRect :dr withFont :font lineBreakMode : NSLineBreakByTruncatingTail ];
