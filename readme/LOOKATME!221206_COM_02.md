# LOOT AT ME!

> **date**: 22.12.06 - <br>
> **author**: timothy-20 <br>
> **subject**: COM 코딩 관례에 대하여.<br>
> **project name**: TKMFCApplication221201

### [__uuidof 연산자](https://learn.microsoft.com/en-us/windows/win32/learnwin32/com-coding-practices#the-__uuidof-operator), [IID_PPV_ARGS 매크로](https://learn.microsoft.com/en-us/windows/win32/learnwin32/com-coding-practices#the-iid_ppv_args-macro)

---
작성 요함

### [SafeRelease 패턴](https://learn.microsoft.com/en-us/windows/win32/learnwin32/com-coding-practices#the-saferelease-pattern)

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

### [COM 스마트 포인터](https://learn.microsoft.com/en-us/windows/win32/learnwin32/com-coding-practices#com-smart-pointers)

---
작성 요함