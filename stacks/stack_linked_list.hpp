#ifndef stack_using_ll
#define stack_using_ll

#include <iostream>
#include <stdexcept>
#include "../linked_lists/singly_linked_list.hpp"

namespace lls
{
    template <typename T>
    class Stack
    {
    private:
        sll::SinglyLinkedList<T> list;

    public:
        void push(const T &value)
        {
            list.insert_at_beginning(value);
        }

        void pop()
        {
            if (is_empty())
                throw std::runtime_error("Stack underflow: Cannot pop from empty stack");
            list.delete_from_beginning();
        }

        T peek() const
        {
            return list.get_head_data();
        }

        bool is_empty() const
        {
            return list.is_empty();
        }

        void display() const
        {
            list.display();
        }
    };
}

#endif