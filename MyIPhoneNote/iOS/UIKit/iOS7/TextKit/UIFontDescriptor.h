1,Matching
    UIFontDescriptor *helveticaNeueFamily = [UIFontDescriptor fontDescriptorWithFontAttributes:@{UIFontDescriptorFamilyAttribute:@"Helvetica Neue"}];
NSArray *matches = [helveticaNeueFamily matchingFontDescriptorWithMandatoryKeys:nil];

2.
UIFontDescriptor *fontDescriptor = [UIFontDescriptor preferredFontDescriptorWithTextStyle:UIFontTextStyleBody];

UIFontDescriptor *boldFontDescriptor = [fontDescriptor fontDescriptorWithSymbolicTraits:UIFontDescriptorTraitBold];
UIFont *boldFont = [UIFont FontWithDescrtptor:boldFontDescriptor size:0.0];

3,修改字体的例子
NSArray *timeFeatureSettings = @[
  @{
      UIFontFeatureTypeIdentifierKey:@(kNumberSpacingType),
      UIFontFeatureSelectorIdentifierKey:@(KProportionalNumbersSelector)
      
      },
  @{
      UIFontFeatureTypeIdentifierKey:@(kCharacterAlternativesType),
      UIFontFeatureSelectorIdentifierKey:@(1)
      }];

UIFont *font = ...;
UIFontDescriptor *originalDescriptor = [font fontDescriptor];
UIFontDescriptor *timeDescriptor = [originalDescriptor fontDescriptorByAddingAttributes:@{UIFontDescriptorFeatureSettingsAttribute:timeFeatureSettings}];
UIFont *boldFont = [UIFont FontWithDescrtptor:timeDescriptor size:0.0];




