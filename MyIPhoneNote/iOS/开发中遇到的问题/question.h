1，
在项目中提交过svn后，再在本机上删除不用的图片资源后，build后会有   ”xx“is missing from working copy  的警告。
在网上找了些资料后，总结下。

直接在终端下用svn命令删除missing的文件：（需要cd到提示你missing 文件的路径下）
svn delete nameOfMissingFile
例如：//svn --force  delete UserSharePath
或用Git（如果你用的是Git的话）
git rm nameOfMissingFile

2,nested push animation can result in corrupted navigation bar

导致这两种情况的原因那就可能是因为，pop和push的操作太连贯，会造成navgation的动画还没执行完毕，就开始执行下一个了。
解决方案：
//[nav popToRootViewControllerAnimated:YES];这句话的YES，改为NO

UIViewController *vc = self.navigationController.viewControllers[0];
[self.navigationController popViewControllerAnimated:NO];
NSLog(@"%@",self.navigationController.viewControllers);//此时对象为null
[vc performSegueWithIdentifier:@"MySubSegueID" sender:nil];
