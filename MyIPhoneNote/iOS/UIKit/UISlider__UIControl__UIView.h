1，当滑块的Value Changed 调用下面的函数，通过label来获取值。

- (IBAction)updateValue:(id)sender
{
	UISlider *slider = (UISlider *)sender;
	int progressAsInt = (int)(slider.value + 0.5f);//四舍五入为整型值。
	NSString *newText2 =[[NSString alloc] initWithFormat:@"%d",progressAsInt];
	NSLog(@"%d",[newText2 retainCount]);//1
	numValue.text = newText2;
	[newText2 release];
}

2，How can we set the thumb image of UISlider to stop once it reaches the max value
[slider setContinuous:YES];
[slider addTarget:self action:@selector(sliderChanged:) forControlEvents:UIControlEventValueChanged];

- (void)sliderChanged:(UISlider*)sender {
    if ([slider value] >= [slider maximumValue]) {
		[slider setEnabled:NO];
    }
}
3,
// Build the slider
UISlider *slider = [[UISlider alloc] initWithFrame:CGRectMake(50.0f, 160.0f, 220.0f, 40.0f)];
slider.backgroundColor = [UIColor clearColor];
slider.minimumValue = 0.0f;
slider.maximumValue = 100.0f;
slider.continuous = YES;
slider.value = 50.0f;

[slider addTarget:self action:@selector(updateValue:) forControlEvents:UIControlEventValueChanged];
[contentView addSubview: slider];
[slider release];


4,关于UISlider的实例

UISlider *mySlider = [[UISlider alloc] initWithFrame:CGRectMake(10,60, 200, 30)];
[mySlider addTarget:self action:@selector(sliderValueChanged:) forControlEvents:UIControlEventValueChanged];
mySlider.backgroundColor = [UIColor clearColor];
mySlider.minimumValue = 0.0;
mySlider.maximumValue = 10.0;
mySlider.continuous = YES;
mySlider.value = 5.0;
[self.view addSubview: mySlider];
[mySlider release];

//slider变化调用函数如下
- (void)sliderValueChanged:(id)sender{
	UISlider *slider = sender;
	if(mySlider == slider){
		printf("Value of slider is %f\n", [mySlider value]);
	}
}
