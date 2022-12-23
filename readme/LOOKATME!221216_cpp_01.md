# LOOT AT ME!

> **date**: 22.12.16. - <br>
> **author**: timothy-20 <br>
> **subject**: c++ 문법을 익히던 도중 시도해 본 내용에 대하여.<br>
> **project name**: TKMFCApplication221201
> 
[1] template
===
> 참고한 글:
> - [template 개념 및 예제](https://modoocode.com/219)

이제는 c++뿐만 아니라 많은 언어에서도 generic이란 형태로 차용하고 있는 개념이지만, c++만큼 활용도가 높은 언어는 많지 않을 것입니다. 


[2] template 응용
===
[2.1] type이 다른 template 검사
---
> 참고한 글:
> - https://stackoverflow.com/questions/17390605/doing-a-static-assert-that-a-template-type-is-another-template
> - https://stackoverflow.com/questions/17392621/using-a-template-alias-instead-of-a-template-within-a-template

```c++
template<typename T>
struct TKDummyTemplate {};

template<typename T>
struct IsInstantiationOfDummy : public std::false_type {};

template<typename ...Ts>
struct IsInstantiationOfDummy<TKDummyTemplate<Ts...>> : public std::true_type {};

template<typename T>
struct TKTemplateChecker
{
	static_assert(IsInstantiationOfDummy<T>::value, "Fail template type!");
};

template<typename T> using TKDummyTemplateAlt = TKDummyTemplate<T>;

// entry point
TKTemplateChecker<TKDummyTemplate<int>> template1;
TKTemplateChecker<TKDummyTemplateAlt<int>> templateAlt1;
```
template 항목 정리 이후 마저 작성할 것.