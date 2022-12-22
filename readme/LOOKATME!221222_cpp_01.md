# LOOT AT ME!

> **date**: 22.12.22. - <br>
> **author**: timothy-20 <br>
> **subject**: c++ 문법을 익히던 도중 시도해 본 내용에 대하여.<br>
> **project name**: TKMFCApplication221201
>
[1] 람다식(Lambda)과 클로져(Closure)
===
> 참고한 글:
> - https://modoocode.com/196

[1.1] 람다식은 어느 시점에 값을 캡쳐하는가?
===
```c++
int a(10);
auto lambda([a] { std::cout << "Captured value: " << a << std::endl; } );

a = 20; // '20' 할당

lambda(); // ?
```
람다식의 캡쳐 값에 대해 공부하면서 무척 인상깊은 부분이었습니다. 이는 캡쳐 값은 **선언된 시점에서 결정**된다는 사실입니다.

<img src="public/result-screenshot/22_12_22_/screenshot-221222-01.png"><br>
이후 캡쳐 값이 원본이 변경된 것과 무관하게, 람다식 내에서는 선언된 시점에서의 값이 '10'이 그대로 출력됩니다.

```c++
auto lambda([&a] { std::cout << "Captured value: " << a << std::endl; } );
```
만일 레퍼런스 값이 캡쳐되어 있다면, 이후 원본 값 변경에 따라 캡쳐 값에 반영됩니다(레퍼런스일 경우 내부에서의 변경 또한 동일하게 반영됩니다). 

[1.2] 변경 가능한 내부 캡쳐 값
---
```c++
int number1(10);
auto makeDouble([number1](void) mutable -> int
    {
        number1 *= 2;
        return number1;
    }
);

std::cout << number1 << std::endl; // 10
std::cout << makeDouble() << std::endl; // 20
```
기본적으로 람다식의 캡쳐 값(=)은 const로 선언됩니다. 그렇기에 값으로써는 복사되었지만, 변경은 불가능하기에 해당 변수를 직접 활용하기 어렵습니다.
이때 **mutable 키워드**를 이용하여 캡쳐 값을 변경 가능하도록 지정합니다.

[1.3] 고차함수 구현 연습
---
> 참고한 글:
> - https://velog.io/@un1945/Swift-%EA%B3%A0%EC%B0%A8%ED%95%A8%EC%88%98-Higher-order-Function

```c++
template<typename T, size_t SIZE>
void Reduce(T(&list)[SIZE], std::function<T(size_t, T)> callback)
{
	for (size_t i(0); i < SIZE; i++)
		list[i] = callback(i, list[i]);
}

// entry point
constexpr size_t size(3);
std::string list[size]{ "timothy", "peco", "ray" };

::Reduce<std::string, size>(list, [](size_t index, std::string element) -> std::string
	{
		if (index == 1)
		return "new one!";

return element;
	}
);
```
Swift의 **고차함수**(higher-order function) 'Reduce'를 template과 람다 함수 객체를 이용해 구현해 보았습니다.


