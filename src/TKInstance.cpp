//
// Created by aircuve on 2022-11-30.
//

#include "TKInstance.h"

// const 전역 변수는 기본적으로 내부 연결입니다. extern을 선언해주지 않으면 외부 번역 단위(파일)에서 읽을 수 없습니다.
extern uint32_t const CONSTRAINT_UNIQUE_ID = 32;

// non-const 전역 변수는 기본적으로 외부 연결이 있습니다.
std::string uniqueName = "timothy-20";

// 자유 함수는 전역 또는 네임 스페이스 범위에서 정의되는 함수입니다.
// 아래의 uniqueFunction은 전역 범위에서의 자유함수입니다.
void uniqueFunction()
{
    std::cout << "Hello, timothy-20!" << std::endl;
}

TKInstance::TKInstance()
{
    // 운영체제에서 충분한 메모리를 할당받지 못한 경우의 예외를 방지하기 위한 할당입니다.
    // 할당에 실패할 경우 예외를 던지는 것이 아닌, null을 반환합니다.
    this->name = new(std::nothrow) std::string("");
}

TKInstance::TKInstance(std::string* name)
{
    this->name = name;
}

TKInstance::~TKInstance()
{
    delete this->name;
    this->name = nullptr;
}