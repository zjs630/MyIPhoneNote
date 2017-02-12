1,在项目Targets，Build Settings 中，找到Header Search Paths添加 $(BUILT_PRODUCTS_DIR)/three20
2,添加Three20脚本
python ttmodule.py -p /code\ test/Three20Test/Three20Test.xcodeproj Three20 --xcode-version=4
