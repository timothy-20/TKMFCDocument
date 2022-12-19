# LOOT AT ME!

> **date**: 22.12.16. - <br>
> **author**: timothy-20 <br>
> **subject**: c++ 문법을 익히던 도중 시도해 본 내용에 대하여.<br>
> **project name**: TKMFCApplication221201
> 
[1] template
===
> 참고한 글들:
> - [template 개념 및 예제](https://modoocode.com/219) 
> - [Linked List 알고리즘](https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=kartmon&logNo=221510676043) 

이제는 c++뿐만 아니라 많은 언어에서도 generic이란 형태로 차용하고 있는 개념이지만, c++만큼 활용도가 높은 언어는 많지 않을 것입니다. 이번에는 필자가 [Linked List]()를 
구현해보면서 template을 활용한 것을 토대로 정리해보겠습니다.
```c++
//template<typename T> class 내부
std::shared_ptr<std::vector<std::string>> container;
container->push_back("ABCDE");

std::shared_ptr<std::vector<T>> templateContainer;
templateContainer->push_back()
```