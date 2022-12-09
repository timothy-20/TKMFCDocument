# LOOT AT ME!

> **date**: 22.12.09. - <br>
> **author**: timothy-20 <br>
> **subject**: c++ 문법에 대하여.<br>
> **project name**: TKMFCApplication221201

Reference
---

> 출처:
> - https://boycoding.tistory.com/207
> - https://boycoding.tistory.com/217

Reference(참조자, 레퍼런스)는 c++에서 지원하는 변수 타입입니다. **별칭**이라는 단어로 이 개념을 설명할 수 있을 것 같습니다.

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