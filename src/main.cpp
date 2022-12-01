#include <stdio.h>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(NULL);

    try
    {
        while(true)
        {
            int* numberList = new int[100000000ul];
        }
    }
    catch (const std::bad_alloc& exception)
    {
        std::cout << exception.what() << '\n';
    }

    while(true)
    {
        int* newNumberList = new(std::nothrow) int[100000000ul];

        if (newNumberList == nullptr) {
            std::cout << "Allocator returned nullptr.\n";
            break;
        }
    }

    return 0;
}
