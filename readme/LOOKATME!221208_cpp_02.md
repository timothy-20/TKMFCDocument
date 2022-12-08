# LOOT AT ME!

> **date**: 22.12.08. - <br>
> **author**: timothy-20 <br>
> **subject**: c++ 문법에 대하여.<br>
> **project name**: TKMFCApplication221201

this 포인터
---
>출처: 
> - https://boycoding.tistory.com/250
> - https://stackoverflow.com/questions/17716293/arrow-operator-and-dot-operator-class-pointer

필자가 알고 있다고 생각한 동시에 오해하고 있었던 개념입니다.<br>
필자는 이전에 Objective c를 주로 썼으므로 objc의 **self**와 this를 동일하게 생각하고 있었습니다. 결과적으로는 동일한 개념입니다만,
objc에서는 포인터의 개념이 c++만큼 직접적이지 않았습니다. 대부분 클래스를 통해 래핑되어 있었기 때문에 *(asterisk)를 통해 값 자체에 직접 접근하는 경우는 
많이 없었습니다. 이는 self도 마찬가지였기에 self를 클래스 자신의 포인터가 아닌 키워드로 오해하고 있었습니다.

this는 클래스의 내부에서 멤버 함수, 변수를 호출 및 선언할 때 사용합니다. 기본적으로 숨겨져 있기 때문에 생략이 가능합니다.

```c++
class TKDummyClass
{
private:
    const char* m_description = "";
    
public:
    TKDummyClass(const char* description)
    {
        this->SetDefalutDescription(description);
    }
    
    void SetDefaultDescription(const char* description)
    {
        std::string text = std::string("[DEFAULT] ");
        
        text.append(description);
        
        this->m_description = text.c_str();
    }
};
```
위 코드를 예로 들었을 때, 'TKDummyClass'의 'SetDefaultDescription' 멤버 함수는 

```c++
//entry point
TKDummyClass dummyClass;
dummyClass.SetDefaultDescription("My name is timothy-20.");
```
이렇게 사용하겠지만,

```c++
TKDummyClass dummyClass;
dummyClass.SetDefaultDescription(&dummyClass, "My name is timothy-20.");
```
컴파일하면 이런 모습입니다. 멤버 함수의 첫 번째 매게 변수의 객체(자신)의 주소가 전달되고 있습니다.

cstring과 std::string
---
>출처: https://jhnyang.tistory.com/99
```c++

```

extern, 그리고 static 키워드
---
>출처: https://boycoding.tistory.com/167
```c++

```
