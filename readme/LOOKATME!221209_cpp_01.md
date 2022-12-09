# LOOT AT ME!

> **date**: 22.12.09. - <br>
> **author**: timothy-20 <br>
> **subject**: c++ 문법에 대하여.<br>
> **project name**: TKMFCApplication221201

Literal
---

> 출처: https://modoocode.com/33

```c++
std::cout << &("abcd") << std::endl; //00007FF78409BCDC
```
리터럴 값은 **오직 읽기만 가능한** 메모리 상의 특별한 장소에 보관됩니다. 따라서 위에서 볼수 있는 것처럼 "abcd" 자체도 주소를 가지고 있습니다. 

```c++
char* letter = "abcd";
letter[0] = "A"; 
```
따라서 이런 식의 변경은 불가능합니다.

```c++
const char* letter = "abcd";
```
그리고 Visual Studio 2017 이상에서는 const를 통해서만 선언이 가능하도록 변경되었습니다. 
이는 컴파일 단에서 리터럴에 대한 수정을 방지합니다.

Reference
---

> 출처:
> - https://boycoding.tistory.com/207
> - https://boycoding.tistory.com/217

Reference(참조자, 레퍼런스)는 c++에서 지원하는 변수 타입입니다. **별칭**이라는 단어로 이 개념을 설명할 수 있을 것 같습니다. 
지금부터 레퍼런스의 다양한 용례에 대해 이해해 봅시다.

Reference 예제
---

```c++
int a = 10;
int b = 20;
int& aRef = a;

aRef = b;

std::cout << "a's address: " << &a << std::endl; // 000000E639EFF764
std::cout << "b's address: " << &b << std::endl; // 000000E639EFF784
std::cout << "a reference's address: " << &aRef << std::endl; // 000000E639EFF764
std::cout << "result: " << aRef << std::endl; // 20
```
> 레퍼런스가 **별칭**임을 알 수 있는 예제입니다.

여기서 'aRef'는 'a'의 별명입니다. 따라서 'aRef'에 'b'를 재할당(주소)한다고 생각해도 실제로 원래 'a'에 대한 참조를 'b'로 변경하지 않습니다.
레퍼런스에서는 값에 대한 변경만이 발생할 뿐입니다.

---

```c++
int& aRef = 10; //비 const에 대한 참조는 lvalue여야 합니다.
const int& bRef = 20;
```
> **상수 레퍼런스**에 대한 예제입니다.

기본적으로 레퍼런스는 lvalue에 대한 참조만이 가능합니다. 하지만 상수 레퍼런스를 통해 리터럴 값(rvalue)도 참조할 수 있게됩니다.

---

```c++
void TestFunction1(int*& value) { value = new int(20); }

//entry point
int* integerPointer = nullptr;

::TestFunction1(integerPointer);
std::cout << "result: " << *integerPointer << std::endl; // 20

delete integerPointer;
```
> integer 포인터 레퍼런스(int*&)를 이용한 동적 할당입니다.

포인터 주소 값(integer)에 대한 레퍼런스라고 생각하면 이해가 쉽습니다. 

---
```c++
void TestFunction2(int(&list)[10])
{
	int length(sizeof(list) / sizeof(list[0]));

	std::cout << "Array length: " << length << std::endl;

	for (int element : list)
	{
		std::cout << "element value: " << element << std::endl;
	}
}

//entry point
int integerList[10] = { 2, 3, 4, 5, 5, 6, 8, 2, 5, 3 };

::TestFunction2(integerList);
```
> integer 배열 레퍼런스(int(&)[])를 이용한 배열 값 조회 함수입니다.
---
```c++
template<int LENGTH>
void TestFunction3(int* (&list)[LENGTH])
{
	for (int i = 0; i < LENGTH; i++)
        list[i] = new int(0);
}

//entry point
int* pointerIntegerList[3] = {};

::TestFunction3(pointerIntegerList); // 혹은 TestFunction3<3>(pointerIntegerList);

delete[] pointerIntegerList;
```
> template와 integer 포인터 배열 레퍼런스(int*(&)[LENGTH])를 이용한 배열 값 동적할 당 함수입니다.
---
```c++
//runtime error!
int& GetReferenceValue() 
{
    int a = 10;
    return a;
}

//entry point
int value = ::GetReferenceValue();
```
> 위의 예제는 런타임 에러를 발생시킵니다. 

함수 스코프가 종료되는 시점에서 지역 변수인 'a'는 스택 상에서 사라지기 때문입니다.
이렇게 원래 참조하던 것이 사라지는 레퍼런스를 가르켜 **댕글링 레퍼런스**라고 합니다. 

```c++
int& GetReferenceInteger(int& ref)
{
	ref = 10;

	return ref;
}

//entry point
int a = 10;
int& aRef = a;
int b = ::GetReferenceInteger(aRef);
```

따라서 위와 같이 외부에 있는 레퍼런스 값(aRef)을 넘겨 리턴하는 방식으로 해결할 수 있습니다. 넘겨진 레퍼런스 값은 아직 살아있는 변수이기 때문에 에러가 발생하지 않습니다.

std::move
---
