# LOOT AT ME!

> **date**: 22.12.06 - <br>
> **author**: timothy-20 <br>
> **subject**: COM 오류 처리에 대하여.<br>
> **project name**: TKMFCApplication221201

### [COM의 오류 처리](https://learn.microsoft.com/en-us/windows/win32/learnwin32/error-handling-in-com)

---
**HRESULT** 값으로 식별할 수 있는 결과는 8종류가 있습니다. 이 중 6개는 'E_'로 시작하는 에러코드, 2개는 'S_'로 시작하는 성공 여부에 대한 코드입니다.
여기서 주목할 것은 'S_'로 시작하는 성공 코드인 **S_OK**와 **S_FALSE**입니다(나머지 에러 코드에 대해서는 출처로 남긴 MSDN에서 확인 바랍니다).

- S_OK는 일반적인 성공 여부에 대한 값입니다. 함수가 성공하고 동작에 영향을 준 경우가 그렇습니다.
- S_FALSE는 **부정적인 조건**에 대한 성공 여부입니다. 이는 'no-op'(함수가 성공하였으나 효과가 없음)을 의미할 수도 있습니다.

그래서 대개는 'SUCCEEDED', 'FAILED' 함수를 호출해 오류를 감지합니다. 단순히 S_OK 이외의 모든 값을 실패로 처리해서는 안됩니다.

```c++
if (hr != S_OK)
    OutputDebugString(L"Error!\n"); // 잘못된 방식입니다. 다른 경우의 성공 결과(S_FALSE)가 있습니다.
    
if (FAILED(hr))
    OutputDebugString(L"Error!\n");
```
특정 에러에 대해서는 'hr == SOME_ERROR_STATE'와 같이 특정 분기를 만들 수 있습니다.
하지만 그렇지 않은 경우, 해당 함수들을 이용해 나머지 경우를 처리하도록 합시다.

### [오류 처리 패턴](https://learn.microsoft.com/en-us/windows/win32/learnwin32/error-handling-in-com#patterns-for-error-handling)

---
패턴들에는 장, 단점이 있으며 취향의 문제로 선택이 갈릴 수 있습니다. 모쪼록 상황에 맞는 사용이 중요한 것 같습니다.
> 1. HRESULT 값을 반환하는 모든 구간에서 에러 감지.
> 2. 사용하지 않는 리소스의 참조 해제.
> 3. NULL 포인터와 같은 유효하지 않은 리소스에 대해 엑세스하지 않음.
> 4. 해제한 리소스에 대해서는 재사용하지 않음

다음은 위의 4가지 조건을 충족하는 MSDN에서 소개하는 4가지 패턴입니다.

#### 1. 중첩된 if
```c++
...
{
    IFileOpenDialog* p_fileOpen = NULL;
    HRESULT hr = CoCreateInstance(...
    
    if (SUCCEEDED(hr))
    {
        hr = p_fileOpen->Show(NULL);
        
        if (SUCCEEDED(hr))
        {
            ...
        }
        
        p_fileOpen->Release();
    }
}
```
MDNS에서 예제를 소개할 때 줄곧 보여준 패턴입니다.

단점에 대해서만 말하자면, 
1. 가독성이 떨어짐.
2. 해당 오류 처리는 다른 분기 및 루프 문과 혼합되어 있습니다. 이로 인해 프로그램 전체의 논리를 이해하기 어려워질 수 있음.

#### 2. 계단식 if
```c++
...
{
    IFileOpenDialog* p_fileOpen = NULL;
    HRESULT hr = CoCreateInstance(...
            
    if (SUCCEEDED(hr))
        hr->p_fileOpen->Show(NULL);
    
    if (SUCCEEDED(hr))
        ...
    
    SafeRelease(&p_fileOpen);
}
```
제가 예제를 적용할 때 애용했던 패턴입니다.

단점에 대해서만 말하자면,
1. 모든 변수는 함수 상단에서 선언하고 초기화해야 함.
2. 중간에 실패하더라도 함수를 종료하지 않고 나머지 불필요한 검사를 수행함.
3. 2번의 단점의 연장으로, 계속되는 코드에서 유효하지 않은 리소스에 접근할 수 있음.
   - 필자는 이를 개선하기 위해 'FAILED'에 대한 결과로 실패시 함수를 종료시켰습니다(어떻게 보면 '실패 시 jump'와 유사합니다).
4. 루프문  내부의 오류에는 특별한 경우가 필요함.

#### 3. 실패 시, jump
```c++
...
{
    IFileOpenDialog* p_fileOpen = NULL;
    HRESULT hr = CoCreateInstance(...
        
    if (FAILED(hr))
        goto done;
    
    hr->p_fileOpen->Show(NULL);    

    if (FAILED(hr))
        ...

done:    
    SafeRelease(&p_fileOpen);
}
```
해당 패턴도 필자가 C언어 프로그래밍을 했을 때 사용했던 패턴입니다.

단점에 대해서만 말하자면,
1. 모든 변수는 함수 상단에서 선언하고 초기화해야 함('계단식 if'와 동일).
2. 일부 프로그래머들의 <b style="color: red;">goto 혐오</b>.
3. goto 문은 생성자를 건너뜁니다.

#### 4. 실패 시, throw
```c++
#include <comdef.h>  

inline void throw_if_fail(HRESULT hr)
{
    if (FAILED(hr))
        throw _com_error(hr);
}

...
{
    try
    {
        CComPtr<IFileOpenDialog> pFileOpen;
        
        throw_if_fail(CoCreateInstance(...)));
        throw_if_fail(pFileOpen->Show(NULL));

        ...
    }
    catch (_com_error err)
    {
        // Handle error.
    }
}
```
보다 관용적인 C++ 스타일입니다.

단점에 대해서만 말하자면,
1. 리소스 관리를 위해 C++ 개체가 필요합니다.
2. 안전한 예외 처리를 위한 코드 작성법을 이해하고 있어야 합니다.
