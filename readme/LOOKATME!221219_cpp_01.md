# LOOT AT ME!

> **date**: 22.12.19. - <br>
> **author**: timothy-20 <br>
> **subject**: c++의 특수 멤버 함수에 대하여.<br>
> **project name**: TKMFCApplication221201

[1] 레퍼런스와 포인터의 차이를 잘 느끼게 해준 예제
===
```c++
int& Func1(int& a) { return a; }
int* Func2(int* a) { return a; }

//entry point
int result1(0);
::Func1(result1) = 10;

int result2(0);
*(Func2(&result2)) = 10;
```
실제로 컴파일러 내에서는 레퍼런스가 포인터로 해석된다고 합니다. 그런 의미에서 레퍼런스와 포인터의 차이는 null 값의 유무라고 볼 수 있겠습니다.
c++에서 레퍼런스를 더 선호하는 이유는 null pointer 접근으로 인한 위험이 없다는 부분에 있습니다.

[2] 복사 생성자, 복사 할당 생성자
===

[3] 이동 생성자, 이동 할당 생성자
===

[3.1] 복사 생략과 반환 값 최적화
---
> 참고한 글:
> - https://modoocode.com/227#page-heading-0
> - https://ansohxxn.github.io/cpp/chapter9-10/

```c++
TKCopying c(TKCopying(2));
```
위 함수의 수행을 생각해보자면, 
1. 초기값 2로 TKCopying 생성자를 통해 객체 생성.
2. 생성자를 통해 만들어진 임시 객체(rvalue)가 TKCopying의 복사 생성자를 통해 복사 생성.

의 순서로 생각해 볼 수 있습니다. 하지만 위 구문은 아래처럼 구현할 수도 있습니다.

```c++
TKCopying c2(2); // TKCopying c1 = TKCopying(2);
```
실제로 컴파일러에서는 위의 생성, 복사 생성의 번거로운 과정을 수행하지 않습니다. 
첫 번재 소스를 컴파일해 보면 생성자만 한 번 호출됨을 확인할 수 있습니다.

비슷한 맥락으로 컴파일러는 높은 비용이 드는 복사 연산을 피함으로써 최적화를 진행하는데 실질적인 경우로
call by value(std::move를 다루며 언급하겠습니다), **함수의 결과 반환 시의 복사**가 있습니다.

기본적으로 스택 상의 객체들은 자신이 해당한 범주가 끝나는 시점에서 제거됩니다. 함수도 그러한 범주의 일종이기 때문에
함수 밖으로 값을 전달하기 위해서는 'return'을 통해 함수 몸체 내부의 값을 복사하여 내보내게 됩니다.

```c++
class TKCopying
{
public:
	TKCopying()
	{
		std::cout << "생성자 실행." << std::endl;
	}
	TKCopying(const TKCopying& copy)
	{
		std::cout << "복사 생성자 실행." << std::endl;
	}
};

TKCopying GetCopying()
{
	return TKCopying();
}

// entry poing
TKCopying c = ::GetCopying();
```
그렇기에 위의 함수는 앞선 예상처럼 객체 생성 및 복사가 발생하는 최악의 경우를 상상해 볼 수 있습니다.

하지만 이는 틀렸습니다. 컴파일러는 이 역시 생성자만 호출하고, 생성된 객체의 주소를 lvalue인 'c'에 넘김으로써
최적화를 수행합니다.

[3.2] 이동 연산자
---
> 참고한 글:
> - https://en.cppreference.com/w/cpp/language/move_constructor

```c++
struct TKCopying
{
private:
	int m_id;
	std::vector<std::string>* m_container;

public:
	TKCopying() :
		m_id(0),
		m_container(nullptr)
	{
		std::cout << "기본 생성자 호출." << std::endl;
	}
	TKCopying(int id) : 
		m_id(id),
		m_container(new std::vector<std::string>)
	{ 
		std::cout << "생성자 호출. 객체 식별 번호: " << this->m_id << std::endl; 
	}
	TKCopying(const TKCopying& copy) :
		m_id(copy.m_id),
		m_container(new std::vector<std::string>(*copy.m_container))
	{
		std::cout << "복사 생성자 호출. 객체 식별 번호: " << this->m_id << std::endl;
	}
	TKCopying(TKCopying&& copy) noexcept :
		m_id(std::move(copy.m_id)),
		m_container(std::move(copy.m_container))
	{
		/*this->m_id = copy.m_id;
		this->m_container = copy.m_container;
		copy.m_container = nullptr;*/

		std::cout << "이동 생성자 호출. 객체 식별 번호: " << this->m_id << std::endl;
	}
	~TKCopying()
	{
		delete this->m_container;

		std::cout << "소멸자 호출. 객체 식별 변호: " << this->m_id << std::endl;
	}
	
	// Utils
	TKCopying operator+(const TKCopying& copy)
	{
		TKCopying object(this->m_id + copy.m_id);

		object.m_container = new std::vector<std::string>(*this->m_container);
		
		for (auto constIter(copy.m_container->cbegin()); constIter != copy.m_container->cend(); constIter++)
			object.m_container->push_back(*constIter);

		std::cout << &object << std::endl;

		return object;
	}
	void AddElement(const std::string& element) const
	{
		this->m_container->push_back(element);
	}
	int GetId() const 
	{ 
		return this->m_id; 
	}
	std::vector<std::string> GetContainer() const 
	{ 
		return *this->m_container; 
	}
};
```
> 이동 생성자 구현 연습을 위해 만든 'TKCopying' 클래스 입니다.

```c++
// entry point
TKCopying copy1(2);

copy1.AddElement("Timothy");
copy1.AddElement("Peco");

TKCopying copy2(3);

copy2.AddElement("Ray");

TKCopying copy4 = TKCopying(std::move(copy1 + copy2));
// TKCopying copy3 = TKCopying(std::forward<TKCopying>(copy1 + copy2));
TKCopying copy5 = TKCopying(copy1 + copy2);
```
> 테스트 코드입니다.

[3.3] 보편적인 참조 및 완전한 전달
---
> 참고한 글:
> - https://modoocode.com/228#page-heading-6
> - https://hwan-shell.tistory.com/132

```c++
template<typename T>
void Wrapper(T&& value) //간과하기 쉽지만, 해당 인자는 이름이 있기에 'lvalue'입니다.
{
    ::InnerWrapper(std::forward<T>(value));
}

class TKClass {};

void InnerWrapper(TKClass& value) { std::cout << "좌측값 레퍼런스 " << std::endl; }
void InnerWrapper(const TKClass& value) { std::cout << "상수 좌측값 레퍼런스 " << std::endl; }
void InnerWrapper(TKClass&& value) { std::cout << "우측값 레퍼런스 " << std::endl; }

// entry point
TKClass a;
const TKClass b;

::Wrapper(a);
::Wrapper(b);
::Wrapper(TKClass());
```