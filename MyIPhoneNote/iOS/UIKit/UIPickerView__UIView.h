1,其父类是UIView.选取起视图的显示区域会被自动设置为默认大小320＊216大小。如果你视图自定义的大小会被忽略掉。
2，单列的Picker
#pragma mark -
#pragma mark Picker Data Source Methods
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
	return 1;
}
- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{
	return [pickerData count];
}
#pragma mark Picker Delegate Methods
- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
	return [pickerData objectAtIndex:row];
}
@end
3，双列的Picker
#pragma mark Picker Data Source Methods
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 2;
}
- (NSInteger)pickerView:(UIPickerView *)pickerView  
numberOfRowsInComponent:(NSInteger)component
{
    if (component == kBreadComponent)
        return [self.breadTypes count];
    
    return [self.fillingTypes count];
}
#pragma mark Picker Delegate Methods
- (NSString *)pickerView:(UIPickerView *)pickerView 
             titleForRow:(NSInteger)row 
            forComponent:(NSInteger)component
{
    if (component == kBreadComponent)
        return [self.breadTypes objectAtIndex:row];
    
    return [self.fillingTypes objectAtIndex:row];
}
4，