# LOOT AT ME!

> **date**: 22.12.05 - <br>
> **author**: timothy-20 <br>
> **subject**: __stdcall, __cdecl과 같은 window programming에서 언급되는 calling convention에 대해서.<br>
> **project name**: TKMFCApplication221201

__stdcall(WINAPI), 당신은 누구인가?
---
> 출처: https://mindgear.tistory.com/73

함수 호출 방식을 표시하는 지정자입니다. 일반적으로 함수명 앞에 적어둡니다. __stdcall을 제외하고도 많은 호출 방식 지정자가 있습니다.
**__cdecl**, **__pascal**, **__stdcall** 등이 그것입니다. 개별적으로 알아보자면

| 키워드       | 설명                                      |
|:----------|:----------------------------------------|
| __cdecl   | win32에서 대부분의 함수들에서 확인할 수                |
| __pascal  | win16에서 실행파일 크기가 줄어들고 속도가 빠르다는 이유로 채용됨. |
| __stdcall |                                         |
