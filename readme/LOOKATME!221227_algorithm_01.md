# LOOT AT ME!

> **date**: 22.12.27. - <br>
> **author**: timothy-20 <br>
> **subject**: c++로 구현한 알고리즘에 대하여.<br>
> **project name**: TKMFCApplication221201

[1] Array List
===

[2] Linked List
===
```c++
struct TKListNode
{
    int index;
    TKListNode* next;
    
    TKListNode(int index) : 
        index(index),
        next(nullptr)
    {}
};

template <typename T>
class TKList
{
private:
    T* m_head;
    int T::* m_index;
    T* T::* m_next;

public:
    TKList() :
        m_head(nullptr),
        m_index(&T::index),
        m_next(&T::next)
    {
    }
    
    void AddNode(T& node)
    {
        node.*m_next = this->m_head;
        this->m_head = &node;
    }
    
    void PrintList() const
    {
        T* temp(this->m_head);
        
        while (temp != nullptr)
        {
            std::cout << "Element index: " << temp->*m_index << std::endl;
            
            temp = temp->*m_next;
        }
    }
};

// entry point
TKList<TKListNode> list;
TKListNode firstNode(1);
TKListNode secondNode(2);
TKListNode thirdNode(3);

list.AddNode(firstNode);
list.AddNode(secondNode);
list.AddNode(thirdNode);
list.PrintList();
```
멤버 포인터 객체를 이용한 Linked list 구현입니다. Stackoverflow에서 답변으로 확인한 예제이지만, Linked List로 사용하기에는
약간의 엉성함이 있는 것 같습니다. 좀 더 다듬어 보겠습니다.