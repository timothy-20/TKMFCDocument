# LOOT AT ME!

> **date**: 22.12.16. - <br>
> **author**: timothy-20 <br>
> **subject**: c++ 문법을 익히던 도중 시도해 본 내용에 대하여.<br>
> **project name**: TKMFCApplication221201
> 
[1] template
===
> 참고한 글:
> - https://modoocode.com/219
> - https://learn.microsoft.com/en-us/cpp/cpp/templates-cpp?view=msvc-170#template_parameters

이제는 c++뿐만 아니라 많은 언어에서도 generic이란 형태로 차용하고 있는 개념이지만, c++만큼 활용도가 높은 언어는 많지 않을 것입니다. 

[1.1] 매개변수 템플릿 및 기본 템플릿 인수
---
```c++
template<typename T, size_t SIZE>
class TKArray
{
public:
    std::vector<T> value = std::vector<T>(SIZE);
};

template<typename T, template<typename = T, size_t = 0> class Arr = TKArray>
class TKClass2
{
public:
    T value;
    Arr<> list;
};

// entry point
TKClass2<int> class1;
auto list(class1.list.value);

list.push_back(10);
list.push_back(20);
list.push_back(30);

for (auto element : list)
    std::cout << "value:" << element << std::endl;
```
해당 문법을 전부 활용해 본 예제입니다. 하나씩 뜯어보겠습니다.

TKClass2의 2번째 템플릿 인자인 

```c++
template<typename, size_t> class Arr
```
'Arr'는 템플릿 내부에서 템플릿 인자를 가지는 클래스 타입을 의미합니다. 템플릿 인자로써 사용되는
템플릿의 인자들은 이름을 가지지 않을 수 있습니다(명시해 둘 수는 있으나, 'Arr' 템플릿 매개 변수에는 본문이 없으므로
사용할 곳이 없습니다). 'Arr' 템플릿 인자는 타입 및 값 인자를 가집니다.

```c++
Arr<int, 10> m_list;
```
위와같이 TKClass2의 멤버로써 사용할 수 있습니다. 

```c++
template<typename T, template<typename = T, size_t = 0> class Arr = TKArray>
```
템플릿은 클래스의 멤버 함수 인자처럼 기본 인자를 가질 수 있습니다. 만일 템플릿의 인자의 아무 타입 혹은 값을
지정하지 않았다면 기본 인자로 대체됩니다. 위 코드에서는 **템플릿 인자의 기본 인자**를 보여주고 있습니다.

```c++
template<typename T = int, template<typename = T, size_t = 0> class Arr = TKArray>
class TKClass2
{ ... };
        
// entry point
TKClass2<> classA; // TKClass2<int, TKArray<int, 0>> classA; 로 연역됩니다.
```
만일 모든 템플릿의 인자가 기본 인자로 대체될 인스턴스를 생성할 경우, 타입 이후에 빈 괄호를 통해 
템플릿 타입임을 명시해 주어야 합니다.

[1.2] 템플릿 특수화
---
```c++

```

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