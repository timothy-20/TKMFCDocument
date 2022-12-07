# LOOT AT ME!

> **date**: 22.12.02 - <br>
> **author**: timothy-20 <br>
> **subject**: windows api programming 코딩 규칙.

#### ※ 해당 README는 문서는 헝가리안 표기법에 대한 참고를 위해 나무위키 문서의 글을 복제한 레플리카입니다.

[헝가리안 표기법](https://namu.wiki/w/%ED%97%9D%EA%B0%80%EB%A6%AC%EC%95%88%20%ED%91%9C%EA%B8%B0%EB%B2%95)
---

#### 1. 공통 항목

| 접두어                     | 데이터 타입                         |
|-------------------------|--------------------------------|
| b                       | byte, boolean                  |
| n (number로 추정)          | int, short                     |
| i (index integer로 추정)   | int, short (주로 인덱스)            |
| c (capacity integer로 추정 | int, short (주로 크기로 사용)         |
| l                       | long                           |
| f                       | float                          |
| ld                      | long double                    |
| w                       | word (unsigned shot)           |
| dw                      | double word (unsigned long)    |
| qw                      | quad word (unsigend long long) |
| ch                      | char                           |
| sz (string to zero로 추정) | NULL로 끝나는 문자열                  |
| str (std::string)       | c++ 문자열                        |
| arr (array)             | 배열 (문자열 제외, 조합 가능)             |
| p                       | 포인터 (16, 32bit, 조합 가능)         |
| lp                      | 포인터 (32, 64bit, 조합 가능          |
| psz                     | NULL로 끝나는 문자열 포인터 (16, 32bit)  |
| lpsz                    | NULL로 끝나는 문자열 포인터 (32, 64bit)  |
| fn (function으로 추정)      | 함수                             |
| pfn                     | 함수 포인터(16, 32bit)              |
| lpfn                    | 함수 포인터(64bit)                  |

이해를 돕기 위한 짧은 설명을 추가해 두었습니다.

#### 2. OOP
| 접두어        | 데이터 타입             |
|------------|--------------------|
| g_(global) | 네임 스페이스의 전역 변수(::~) |
| m_(member) | 클래스의 멤버 변수         |
| s_(static) | 클래스의 static 변수     |
| c_         | 함수의 static 변수      |
해당 접두어들을 private 멤버에 대한 네이밍입니다.

#### 1. Windows API
| 접두어 | 데이터 타입                         |
|-----|--------------------------------|
| h   | 리소스 핸들(HWND를 제외한 모든 HANDLE 타입) |
windows 프로그래밍에서 가장 많이 볼 수 있는 접두어일 것입니다.