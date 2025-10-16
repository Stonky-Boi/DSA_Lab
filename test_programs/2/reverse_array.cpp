#include <iostream>
#include "../../stacks/stack_array.hpp"

int main()
{
    int size, input;
    std::cout << "Enter the size of the array:" << std::endl;
    std::cin >> size;
    as::Stack<int> stack(size);
    std::cout << "Enter the array of integers:" << std::endl;
    for (int index = 0; index < size; index++)
    {
        std::cin >> input;
        stack.push(input);
    }
    std::cout << "The array has been reversed." << std::endl;
    for (int index = 0; index < size; index++)
    {
        std::cout << stack.peek() << std::endl;
        stack.pop();
    }
    return 0;
}