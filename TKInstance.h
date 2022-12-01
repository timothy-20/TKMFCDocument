//
// Created by aircuve on 2022-11-30.
//

#ifndef TKCPPALGORITHM221130_TKINSTANCE_H
#define TKCPPALGORITHM221130_TKINSTANCE_H

#include <iostream>

extern constexpr uint32_t CONSTEXPR_UNIQUE_ID = 64;
int a = 10;

//static 키워드는 명시적으로 선언하여 전역 변수가 내부 연결을 가지도록 강제할 수 있습니다.
//따라서 extern으로 해당 전역 변수를 연결할 수 없습니다.
static int b= 20;

class TKInstance
{
private:
    std::string* name;

public:
    TKInstance();
    TKInstance(std::string* name);
    ~TKInstance();
};


#endif //TKCPPALGORITHM221130_TKINSTANCE_H
