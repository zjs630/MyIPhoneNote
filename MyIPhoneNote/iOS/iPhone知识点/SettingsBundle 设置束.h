Settings应用程序的优势：是无需为首选项设计用户界面，应用程序会自动创建。
每个设置束必须包含一个Root.plist的属性列表，它定义根级首选项视图。

1,设置Root.plist文件
Type 的Value可以是PSGroupSpecifier(分组),PSTextFieldSpecifier(文本),PSMultiValueSpecifier(多值),
PSToggleSwitchSpecifier(滑动开关),PSSliderSpecifier(滑动条),PSChildPaneSpecifier(加载其它plist文件).
Title 显示的名称。
Key 的Value是实际存放的值。
a,PSTextFieldSpecifier(文本)
AutocapitalizationType 设为None.取消自动大写。
Autocorrectiontype No,取消自动更正。
IsSecure Boolean 对钩 ,设置是否字母保密。
b,PSMultiValueSpecifier(多值)
Titles Array
Values Array 
DefaultValue string yourValue
c,PSToggleSwitchSpecifier(滑动开关)
TrueValue string value1
FalseValue stirng value2
DefaultValue string value1/value2
d,PSSliderSpecifier(滑动条)
DefaultValue Number 5
MinimumValue Number 1
MaximumValue Number 10
MinimumValueImage string a.png
MaximumValueImage string b.png
e,PSChildPaneSpecifier(加载其它plist文件).
Title string disPlayName
File String More //More.plist为要加载的文件

2，读取SettingsBundle中的数据。
NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
usernameLabel.text = [defaults objectForKey:kUsernameKey];//显示在Label中。
3，设置SettingsBundle中开关和滑动条的值
UISwitch *engineSwitch;
UISlider *warpFactorSlider;
//读取状态
NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
engineSwitch.on  = ([[defaults objectForKey:kWarpDriveKey] 
					 isEqualToString:@"开"]) ? YES : NO;
warpFactorSlider.value = [defaults floatForKey:kWarpFactorKey];
//设置状态
NSString *prefValue = (engineSwitch.on) ? @"开" : @"关";
[defaults setObject:prefValue forKey:kWarpDriveKey];
[defaults setFloat:warpFactorSlider.value forKey:kWarpFactorKey];
/////////////////////////////////
1.Setting页面的格式
a，Setting程序包中的每个Settings页面文件都以属性列表的格式进行存储。
b, 在编译时，Xcode会将工程中基于XML的属性文件自动转换为二进制格式，转换过程
是编译时自动完成的，目的是节省磁盘空间。
c, 每个Seeting页面文件的跟元素，至少包含一个必须的键为PreferenceSpecifiers。
d,任何iPhone应用程序均可在Setting主屏幕中添加首选项。
2. 偏好设置值的读写，
在Foundation框架中，通过NSUserDefaults类库来读写偏好设置的值。或者在Core
Foundation
框架中，可以使用几个与偏好设置相关的函数。
例：
通过Identifier的值，来获取偏好设置的Toggle Switch的状态，on／off。
NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
［defaults boolForkey:@"Identifier_name"］；
// 设置偏好设置中TextFiled的值
［defaults setObject:@"开关状态" forKey：@“Identifier_TextFiledName”］；




