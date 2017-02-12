1,QuickLook.framework 是一个提供文档快速预览的库，支持的类型包括 iWork documents,Microsoft Office,Rich Text Format,PDF,images,text files and comma-separated(csv)files.


2,对于subview加载，4.3无效

API说了QLPreviewController有两种方式
You can push it into view using a UINavigationController object, or can present it modally, full screen, using the presentModalViewController:animated: method of its parent class, UIViewController.
直接加上去好像是不行的