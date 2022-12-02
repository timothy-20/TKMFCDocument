# LOOT AT ME!

> **date**: 22.12.02 - <br>
> **author**: timothy-20 <br>
> **subject**: windows api programming 코딩 규칙.

#### ※ 해당 README는 문서는 헝가리안 표기법에 대한 참고를 위해 나무위키 문서의 글을 복제한 레플리카입니다.

### [헝가리안 표기법](https://namu.wiki/w/%ED%97%9D%EA%B0%80%EB%A6%AC%EC%95%88%20%ED%91%9C%EA%B8%B0%EB%B2%95)

---

#### 1. 공통 항목

| 접두어                    | 데이터 타입                         |
|------------------------|--------------------------------|
| b                      | byte, boolean                  |
| n(number로 추정)          | int, short                     |
| i(index integer로 추정)   | int, short (주로 인덱스)            |
| c (capacity integer로 추정 | int, short (주로 크기로 사용)         |
| l                      | long                           |
| f                      | float                          |
| ld                     | long double                    |
| w                      | word (unsigned shot)           |
| dw                     | double word (unsigned long)    |
| qw                     | quad word (unsigend long long) |
| ch                     | char                           |
| sz (string to zero로 추정) | NULL로 끝나는 문자열                  |
| str (std::string)      | c++ 문자열                        |
| arr (array)            | 배열 (문자열 제외, 조합 가능)             |
| p                      | 포인터 (16, 32bit, 조합 가능)         |
| lp                     | 포인터 (32, 64bit, 조합 가능          |
| psz                    | NULL로 끝나는 문자열 포인터 (16, 32bit)  |
| lpsz                   | NULL로 끝나는 문자열 포인터 (32, 64bit)  |
| fn (function으로 추정)     | 함수                             |
| pfn                    | 함수 포인터(16, 32bit)              |
| lpfn                   | 함수 포인터(64bit)                  |

#### 2. OOP

#### 1. Windows API