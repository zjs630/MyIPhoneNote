1,关于UISwitch的实例
CGRect rect = CGRectMake(10,90, 100, 30);
mySwitch = [[UISwitch alloc] initWithFrame:rect];
[mySwitch addTarget:self action:@selector(switchValueChanged:)
   forControlEvents:UIControlEventValueChanged];
mySwitch.backgroundColor = [UIColor clearColor];
[theView addSubview: mySwitch];
//以下是UISwitch 状态变化时调用的函数
- (void)switchValueChanged:(id)sender{
	UISwitch *aSwitch = sender;
	if(mySwitch == aSwitch){
		if([mySwitch isOn] == YES){
			printf("The switch is on\n");
		}
		else
			printf("The switch is off\n");
			}
}

2,ios6下，新增了几个属性，可以设置开关的颜色以及背景
@property(nonatomic,retain) UIColor *