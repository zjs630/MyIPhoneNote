1,保存gif图片到系统相册。
ALAssetsLibrary *library = [[ALAssetsLibrary alloc] init];
[library writeImageDataToSavedPhotosAlbum:photoData metadata:nil completionBlock:^(NSURL *assetURL, NSError *error) {
    [self showProgressHUDCompleteMessage: error ? TTLocalizedString(@"Failed", @"Informing the user a process has failed") : TTLocalizedString(@"Saved", @"Informing the user an item has been saved")];
    [self hideControlsAfterDelay]; // Continue as normal...
}];






