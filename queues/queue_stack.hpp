#ifndef queue_using_stack
#define queue_using_stack

#include <iostream>
#include <stdexcept>
#include "../stacks/stack_linked_list.hpp"

namespace qs
{
    template <typename T>
    class Queue
    {
    private:
        lls::Stack<T> s1, s2;

        void transfer_s1_to_s2()
        {
            while (!s1.is_empty())
            {
                T value = s1.peek();
                s1.pop();
                s2.push(value);
            }
        }

    public:
        void enqueue(const T &value)
        {
            s1.push(value);
        }

        void dequeue()
        {
            if (is_empty())
                throw std::runtime_error("Queue underflow: Cannot dequeue from empty queue");
            if (s2.is_empty())
                transfer_s1_to_s2();
            s2.pop();
        }

        T peek()
        {
            if (is_empty())
                throw std::runtime_error("Queue is empty: No front element");
            if (s2.is_empty())
                transfer_s1_to_s2();
            return s2.peek();
        }

        bool is_empty() const
        {
            return s1.is_empty() && s2.is_empty();
        }

        void display()
        {
            if (is_empty())
            {
                std::cout << "Queue is empty." << std::endl;
                return;
            }
            if (s2.is_empty())
                transfer_s1_to_s2();
            s2.display();
        }
    };
}

#endif