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
c++에서 레퍼런스를 더 선호하는 이유는 null pointer 접근으로 인한 위험이 없다는 부분입니다.

[] 복사 생성자, 복사 할당 생성자
===

[] 이동 생성자, 이동 할당 생성자
===