关于IOS文件目录的一点记录

IOS的文件系统面向的是设备上的每个运行的应用程序。为了保证IOS系统的可用性和简单性，IOS设备的终端用户是无法直接访问文件系统的，同时设备上的app与用户一样也是不能随便直接访问文件系统的。IOS的app与文件系统之间的交互被限定在了一个指定的空间或者说是一个目录里，该目录存在于每个App自身沙箱(sandbox)内部。每当在IOS设备上安装一个新的app，IOS的设备上的程序安装器会自动为这个新app提供一个主目录(Home Directory),并将app安装在为其创建的主目录下，此外安装器还会创建为app创建其它几个关键性的目录。所有这些创建的目录组合起来就组成了app的文件系统主视图。因此app对文件系统的操作也仅限定在了以上目录的组合，app可以直接读取这些目录及目录下的任何文件，同时app也可以在指定的任何目录创建自己的文件或写入自己的数据。翻过来说，在这个指定范围之外app不能再访问或创建任何目录和文件。比较特殊的情况是，IOS系统会提供系统接口来允许app访问，例如访问用户存储在设备上的联系方式，相册。但访问这些内容背后所对应的文件操作都是由底层的系统框架来完成。这也是app被称为是一个“沙箱”的原因，在自己的沙箱内，app拥有全面的操作控制权；沙箱之外的东西，在有悖访问规则的前提下，app不能做任何事情。

开启iTunes文件共享
之前对Linux/Unix系统不熟悉（现在其实也不熟悉），对苹果的设备环境，开发体系，硬件特点基本上也处于无知状态，记得起初拿到iPad的时候，一直以为作为移动设备，既然iPad能够与PC端连接，那么就可以把它同时当做是一个移动硬盘来用，可以在PC可iPad之间进行文件的传输，存储，共享。我可以想任意App中放置文件，也可以在PC端像浏览Mac上的文件系统一样，去查看App目录下的内容。后来我发现我错了，根本不是想象中的那样。当iPad连接PC之后，并没有一个设备目录浏览管理界面。其实这也比较苹果系统封闭的风格，苹果希望将用户在苹果设备上的文件都能上传到云端，从而实现可以在多台苹果设备上同步用户数据。

通过在app工程的Info.plist文件中指定UIFileSharingEnabled关键字，并将其值设置为YES。我们可以很方便的打开app与iTunes之间的文件共享。但这种共享有一个前提：App必须将任何所需要共享给用户的文件，都要存放在<Application_Home>/Documents目录下，<Application_Home>即在app安装时自动创建的app的主目录。
