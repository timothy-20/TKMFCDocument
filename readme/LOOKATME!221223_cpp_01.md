# LOOT AT ME!

> **date**: 22.12.23. - <br>
> **author**: timothy-20 <br>
> **subject**: c++ 문법을 익히던 도중 시도해 본 내용에 대하여.<br>
> **project name**: TKMFCApplication221201
>
[1] 함수 객체 활용
===

[1.1] std::bind
---
> 참고한 글:
> - https://en.cppreference.com/w/cpp/utility/functional/bind
> - 
 
```c++
using namespace std::placeholders;

int n(7);
auto func1(std::bind([](int n1, int n2, int n3, const int& n4, int n5) -> void
    {
        std::cout << n1 << std::endl;
        std::cout << n2 << std::endl;
        std::cout << n3 << std::endl;
        std::cout << n4 << std::endl;
        std::cout << n5 << std::endl;

    }, _2, 10, _1, std::cref(n), n) // 2, 10, 1, 20, 7
);

n = 20;

func1(1, 2, 3);
```
std::placeholder를 이용한 인자의 위치 지정 및 참조 인자를 넘기는 방식에 대해 보여주고 있습니다.

[1.2] timer 구현
---
> 참고한 글 :
> - https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
> - https://stackoverflow.com/questions/14650885/how-to-create-timer-events-using-c-11

```c++
template<typename T, typename... Args>
void Wait(uint32_t seconds, bool isAsync, T&& func, Args... parameters)
{
	std::function<typename std::result_of<T(Args...)>::type()> task(std::bind(std::forward<T>(func), std::forward<Args>(parameters)...));

	if (isAsync)
	{
		std::thread([seconds, task]() -> void
			{
				std::this_thread::sleep_for(std::chrono::seconds(seconds));
				task();
			}
		).detach();

		return;
	}

	std::this_thread::sleep_for(std::chrono::seconds(seconds));
	task();
}

// entry point
uint32_t totalCount(0);
bool flag(0);

::Wait(3, true, [&]() -> void { flag = true; });

do {
    ::Wait(1, false, [&]() -> void { std::cout << "count: " << ++totalCount << std::endl; });	

} while (!flag);
```
'Wait' 함수는 2번째 출처의 내용과 동일합니다(이름만 변경되어 있음). 이후 Timer 클래스를 구현하는 부분에서 응용해보겠습니다. 