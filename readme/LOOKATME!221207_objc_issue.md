# LOOT AT ME!

> **date**: 22.12.07 - <br>
> **author**: timothy-20 <br>
> **subject**: objc __bridge 키워드 복습 중 막힌 부분에 대하여.<br>
> **project name**: TKMFCApplication221201

22.12.07. 17:14에 발견한 이슈
---
> 도움이 되었던 글:
> - http://seorenn.blogspot.com/2015/01/objective-c-arc.html

``` objective-c++
//ViewController.m

//main view 생성 이후에 상황을 모니터링 하기 위해서 'viewDidAppear에서 선언해 두었음.
-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    CFStringRef strs[3] = {CFSTR("A"), CFSTR("B"), CFSTR("C")};
    CFArrayRef cfArray = CFArrayCreate(kCFAllocatorDefault, (const void**)strs, 3, &kCFTypeArrayCallBacks);
    NSArray* nsArray = (__bridge NSArray*)cfArray;
}
```
**CFArrayRef**를 **NSArray**로 형 변환(bridge) 이후, 'cfArray' 변수를 **CFRelease**를 통해 메모리를 해제해 주지 않았습니다. 
이는 이전에 필자가 Core Foundation 라이브러리를 사용하는 과정에서 빈번히 간과했던 부분이었는데, 이번에 __bridge 키워드를 사용하게 되면서
재점검해 보았습니다.

<img src="public/result-screenshot/22_12_07_/debug-result-221207-01.png">

xcode 디버거의 memory graph를 이용해 메모리 릭이 발생하는 것을 확인했습니다. 

<img src="public/result-screenshot/22_12_07_/debug-result-221207-02.png">

역시 제가 형 변환 이후 할당 해제하지 않은 'cfArray' 입니다.

해결 방안
---
``` objective-c++
CFRelease(cfArray);
```
앞서 말했듯, 할당 해제 해주면 됩니다.

기본적으로 NSType에서 CFType으로의 bridge 형 변환에 대해서는 CFType의 변수에 대해서 할당 해제해 줄 필요가 없지만(NSType 원본 값이 ARC를 통해 스코프를 벗어나면 할당 해제됩니다), 
CFType이 원본인 경우에 원본 값에 대한 어떤한 retain 혹은 release를 걸지 않습니다(일반적인 RC 방식으로 관리해주어야 합니다).

그렇기에 CFArrayCreate에서 Retain 걸린 것을 반드시 스코프가 종료되기 이전에 할당 헤제해 주어야 합니다.

번외
---
기본형인 __bridge에 대해서 안 김에 **__bridge_retained** 및 **__bridge_transfer** 또한 소개하도록 하겠습니다.

1. __bridge_retained
``` objective-c++
NSArray *nsArray2 = [[NSArray alloc] initWithObjects:@"A2", @"B2", @"C2", nil];
CFArrayRef cfArray2 = (__bridge_retained CFArrayRef)nsArray2;
CFRelease(cfArray2); //할당 해제 필수!
```
> 혹은 **CFBridgingRetain**도 가능합니다.<br>
> //CFArrayRef cfArray = (CFArrayRef)CFBridgingRetain(array)

NSType에서 CFType으로 bridge할 때 사용합니다. 특징적이라고 할 수 있는 부분은, 키워드명에서 볼 수 있듯이 
형 변환 이후 CFType 값에 retain을 하기 때문에 CFType 변수에 대해서 메모리 할당 해제를 해주어야 합니다.

2. __bridge_transfer
``` objective-c++
CFStringRef strs[3] = {CFSTR("A1"), CFSTR("B1"), CFSTR("C1")};
CFArrayRef cfArray1 = CFArrayCreate(kCFAllocatorDefault, (const void**)strs, 3, &kCFTypeArrayCallBacks);
NSArray* nsArray1 = (__bridge_transfer NSArray*)cfArray1;
```
> 혹은 **CFBridgingRelease**도 가능합니다.<br>
> //NSArray *array = (NSArray *)CFBridgingRelease(cfArray); 

CFType에서 NSType으로 bridge할 때 사용합니다. 앞서 '__bridge'에서
원본 값인 CFType 변수에 대해서 메모리 할당 해제를 해주어야 되었지만, '__bridge_transfer'는 알아서 메모리를 해제합니다.

<img src="public/result-screenshot/22_12_07_/debug-result-221207-03.png">

혹시나 해서 메모리 릭 체크를 해보았는데, 재미있는 결과가 눈에 뜁니다. 그건 'cfArray1'의 초기화 값인 'strs' 변수(CFStringRef[])와
요소들은 메모리가 할당되지 않았다는 사실입니다! 이 부분은 좀 더 자세히 알아보아야 할 것 같습니다.