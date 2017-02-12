1,AddressBook framework is C-based，User CoreFoundation datatypes and semantics.
2,
ABPersonViewController *personViewController = [[ABPersonViewController alloc] init];

ABRecordRef person = ABPersonCreate(();
ABRecordSetValue(person, KABPersonFirstNameProperty, CFSTR("John"), NULL);
ABRecordSetValue(person, KABPersonLastNameProperty, CFSTR("Apolesseed"), NULL);
personViewController.displayedPerson = person;
CFRelease(person);
personViewController.allowsEditing = YES;



// 一个ABRecordRef代表对一个联系人的引用

//访问记录的函数:
ABRecordID ABRecordGetRecordID(ABRecordRef record);


//获得地址簿的句柄
#import <AddressBook/AddressBook.h >

ABAddressBookRef ab = ABAddressBookCreate();


//提交修改,添加记录,删除记录
CFerrorRef error;
BOOL success = ABAddressBookSave(ab,&error);

CFerrorRef error;
BOOL success = ABAddressBookAddRecord(ab,myRecord,&error);

CFerrorRef error;
BOOL success = ABAddressBookRemoveRecord(ab,myRecord,&error);


//获得记录总个数
CFIndex count = ABAddressBookGetPersonConut(ab );


//获得数据库中所有联系人的列表
NSArray *array = (NSArray *) ABAddressBookCopyArrayOfAllPeople(ab);

//在联系人列表中查找一个特定的名字
NSArray *array = (NSArray *) ABAddressBookCopyPeopleWithName(ab,CFSTR("john Appleseed"));


