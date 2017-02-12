UIImagePickerController类提供了摄像头和照片库的实现。其他程序有标准的系统接口，包括摄像和照片程序。
当你打开摄像头接口，此接口控制器就监视用户的交互，并将图像传给程序。
iPhone 4和4s 有2个摄像头，iPhone 3G 和 3GS都只有一个。第一代iPad没有摄像头。

1,Getting still photos or video from the user (either from camera or photo library)

2,使用UIImagePickerController类来创建图像选区器。
UIImagePickerController *picker = [[UIImagePickerController alloc] init];
//设置图像来源1,TypePhotoLibrary 相片库 2，TypeCamera 照相机 3，TypeSavedPhotosAlbum 保存的照片
picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
//开启图像编辑功能
picker.allowsEditing = YES;//默认选择正方形截图
picker.delegate = self;
[self.view addSubview:picker.view];//或者[self presentModalViewController:picker animated:YES];

3,检查摄像头是否能用。
if([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]){
    //2.
}
//或者写成一个函数调用
- (BOOL) isCameraAvailable{
    return [UIImagePickerController isSourceTypeAvailable: UIImagePickerControllerSourceTypeCamera];
}
//判断前置摄像头是否能用
- (BOOL) isFrontCameraAvailable{
    return [UIImagePickerController isCameraDeviceAvailable:UIImagePickerControllerCameraDeviceFront];
}
//判断后置摄像头是否能用
- (BOOL) isRearCameraAvailable{
    return [UIImagePickerController isCameraDeviceAvailable:UIImagePickerControllerCameraDeviceRear];
}