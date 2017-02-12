1，Bundle versions string, short 和 Bundle version 区别

Bundle version is the internal version number of your app.
Short version string is the publically visible version of your app.

So for example, if you iterate your version number every time you do an internal build for your beta testers (or whatever), your bundle version might be 2.0.0.12345b7, but you don't want the public to see that, so you set your short version string to 2.0.

Short version string seems to be optional, so if you leave it blank then the bundle version is what people will see (i.e. that's what will be displayed on the App Store).
                                                                                                                     
                                                                                                                     Your short version string can't have more than 3 parts, e.g. 2.0.1 is okay, but 2.0.0.1 isn't. If you don't have a short version string, then the same rules apply to your bundle ID (basically the public app version has this restriction and the private app version doesn't).



iTunes Connect
This is the version number shown in the App Store; This must be a pure version number like1.2.3

Bundle Version (CFBundleVersion)
This doesn't need to be a pure version number. This can be something like 12345 or 1.2.3 (Build 12345AB). This is shown in the About window for Mac OS X apps for example and is often more a "Build Number" than a "Version Number".

Bundle Version String (CFBundleShortVersionString) This value is used as the "real" version number. This must be the same string as used for the version in iTunes Connect.