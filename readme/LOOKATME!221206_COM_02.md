# LOOT AT ME!

> **date**: 22.12.06 - <br>
> **author**: timothy-20 <br>
> **subject**: COM 코딩 관례에 대하여.<br>
> **project name**: TKMFCApplication221201

[__uuidof 연산자](https://learn.microsoft.com/en-us/windows/win32/learnwin32/com-coding-practices#the-__uuidof-operator), [IID_PPV_ARGS 매크로](https://learn.microsoft.com/en-us/windows/win32/learnwin32/com-coding-practices#the-iid_ppv_args-macro)
---
1. **__uuidof** 
> unresolved external symbol "struct _GUID const IID_IDrawable"

위와 같은 링커 오류에 대비하기 위한 연산자입니다(해당 오류는 GUID(UUID) 상수가 외부 링크(extern)로 선언되었고 링커가 상수의 정의를 찾을 수 없음을 의미합니다).
```c++
IFileOpenDialog* fileOpenDialog = NULL;
hr = CoCreateInstance(__uuidof(FileOpenDialog), //CLSID_FileOpenDialog, 클래스 GUID 상수 
                      NULL, 
                      CLSCTX_ALL, 
                      __uuidof(fileOpenDialog), //IID_IFileOpenDialog, 인터페이스 GUID 상수 
                      reinterpret_cast<void**>(&fileOpenDialog));
```
MS Visual C++를 사용하는 경우라면 __uuidof 연산자를 사용할 필요는 없습니다.

2. **IID_PPV_ARGS**
> reinterpret_cast<<b style="color: skyblue;">void**</b>>(&fileOpenDialog)

'CoCreateInstance'와 'QueryInterface'의 최종 매게 변수를 void** 타입으로 강제 변환하는데서 오는 유형 불일치를 예방하기 위한 매크로입니다.

'reinterpret_cast'는 C++ 타입 시스템을 우회합니다. 그러므로<br>
**최상의 경우**, 개체가 요청된 인터페이스를 구현하지 않으면 호출이 실패합니다.<br>
**최악의 경우**, 함수가 성공하고 포인터가 일치하지 않습니다.

```c++
//IFileDialogCustomize 인터페이스 구현을 위한 fileOpenDialog(IFileOpenDialog) 인스턴스
__uuidof(IFileDialogCustomize), reinterpret_cast<void**>(&fileOpenDialog)
```
```c++
IID_PPV_ARGS(&fileOpenDialog)
```
위와 같이 사용할 수 있습니다. 최종적으로 소스코드는 이렇습니다.
```c++
IFileOpenDialog* fileOpenDialog = NULL;
hr = CoCreateInstance(__uuidof(FileOpenDialog), 
                      NULL, 
                      CLSCTX_ALL, 
                      IID_PPV_ARGS(&fileOpenDialog));
```

[SafeRelease 패턴](https://learn.microsoft.com/en-us/windows/win32/learnwin32/com-coding-practices#the-saferelease-pattern)
---
```c++
//global
template<typename T>
void TKSafeRelease(T** ppt)
{
	if (*ppt != NULL)
	{
		(*ppt)->Release();
		*ppt = NULL;
	}
}
```
포인터에 대한 null check, Release 호출 이후 null 대입 처리를 수행합니다. 
이러한 처리는 [**댕글링 포인터**](https://ko.wikipedia.org/wiki/%ED%97%88%EC%83%81_%ED%8F%AC%EC%9D%B8%ED%84%B0)에 대한 역참조를 방지합니다.

```c++
IFileOpenDialog* fileOpenDialog = NULL;
hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&fileOpenDialog));

if (FAILED(hr))
    goto Done;

hr = fileOpenDialog->Show(NULL);

if (FAILED(hr))
    goto Done;

IShellItem* item = NULL;
hr = fileOpenDialog->GetResult(&item);

if (FAILED(hr))
    goto Done;

if (SUCCEEDED(hr))
{
    PWSTR pszFilePath;
    hr = item->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

    if (SUCCEEDED(hr))
    {
        MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
        CoTaskMemFree(pszFilePath);
    }
}

Done:
::TKSafeRelease(&item); //item->Release(); 대체
::TKSafeRelease(&fileOpenDialog); //fileOpenDialog->Release(); 대체

return 0
```
이전에는 함수의 결과값(HRESULT)이 분기문에서 'SUCCEEDED == TRUE'로 반환되면 생성한 포인터에 해제를 진행했습니다. 하지만 'SafeRelease'의
null check로 인해 if문 중첩을 피하는 형태로 진행할 수 있게 되었습니다.

[COM 스마트 포인터](https://learn.microsoft.com/en-us/windows/win32/learnwin32/com-coding-practices#com-smart-pointers)
---
하지만 c++에서 new, delete 키워드가 생긴 이유가 그렇듯, 'SafeRelease'를 이용한 포인터의 관리는 여전히 개발자의 실수를 유발시킵니다(각 포인터가 범위를 벗어나기 전에 함수가 호출되어야 하는 점 등).
또한 모든 인터페이스 포인터를 NULL로 초기화한다는 점이 세부적인 구현에 대한 처리를 어렵게 합니다.

[**스마트 포인터**](https://learn.microsoft.com/ko-kr/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170)의 개념처럼 제네릭으로 포인터를 래핑하고 자동으로 초기화 해주는 클래스가 필요하다는 생각도 듭니다. 
```c++
template<typename T>
class TKSmartPointer
{
private:
	T* p_ptr;

public:
	TKSmartPointer(T* p) : p_ptr(p) { }
	~TKSmartPointer()
	{
		if (this->p_ptr != NULL)
			this->p_ptr->Release();
	}
};
```
MSDN에서 소개해주는 모델은 이와 같습니다. 하지만 MS 라이브러리에서 지원하고 있는 스마트 포인터 클래스가 있지는 않을까요?

MS Visual Studio에서는 이미 ATL(Active Template Library)의 일부로 스마트 포인터 클래스를 지원합니다. 이전에 작성해본 
COM 인터페이스 예제(File open dialog)에 적용해 볼 수 있겠습니다.

```c++
CComPtr<IFileOpenDialog> fileOpenDialog = NULL;
hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&fileOpenDialog));

if (FAILED(hr))
    return 0;

hr = fileOpenDialog->Show(NULL);

if (FAILED(hr))
    return 0;

CComPtr<IShellItem> item = NULL;
hr = fileOpenDialog->GetResult(&item);

if (FAILED(hr))
    return 0;

if (SUCCEEDED(hr))
{
    PWSTR pszFilePath;
    hr = item->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

    if (SUCCEEDED(hr))
    {
        MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
        CoTaskMemFree(pszFilePath);
    }
}

//::TKSafeRelease(&item); 필요 없음
//::TKSafeRelease(&fileOpenDialog); 필요 없음 

return 0
```
'IFileOpenDialog','IShellItem' 인터페이스 모두 **CComPtr** 스마트 포인터 클래스로 래핑합니다. 이제 인스턴스들은 
스코프를 벗어나게 되면 자동적으로 초기화 될 것입니다.