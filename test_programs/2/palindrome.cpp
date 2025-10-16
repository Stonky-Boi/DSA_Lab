#include <iostream>
#include "../../stacks/stack_linked_list.hpp"

int main()
{
    std::string original, reversed;
    std::cout << "Enter the string:" << std::endl;
    std::getline(std::cin, original);
    lls::Stack<char> stack;
    for (int index = 0; index < original.length(); index++)
        stack.push(original[index]);
    for (int index = 0; index < original.length(); index++)
    {
        reversed += stack.peek();
        stack.pop();
    }
    std::cout << ((original == reversed) ? "The string is a palindrome." : "The string is not a palindrome.") << std::endl;
    return 0;
}