#ifndef stack_using_queue
#define stack_using_queue

#include <iostream>
#include <stdexcept>
#include "../queues/queue_linked_list.hpp"

namespace sq
{
    template <typename T>
    class Stack
    {
    private:
        llq::Queue<T> q1, q2;

    public:
        void push(const T &value)
        {
            q1.enqueue(value);
        }

        void pop()
        {
            if (is_empty())
                throw std::runtime_error("Stack underflow: Cannot pop from empty stack");
            while (true)
            {
                T front = q1.peek();
                q1.dequeue();
                if (q1.is_empty())
                    break;
                q2.enqueue(front);
            }
            std::swap(q1, q2);
        }

        T peek()
        {
            if (is_empty())
                throw std::runtime_error("Stack is empty: No top element");
            T top_element;
            while (true)
            {
                T front = q1.peek();
                q1.dequeue();
                if (q1.is_empty())
                {
                    top_element = front;
                    q2.enqueue(front);
                    break;
                }
                q2.enqueue(front);
            }
            std::swap(q1, q2);
            return top_element;
        }

        bool is_empty() const
        {
            return q1.is_empty();
        }

        void display() const
        {
            q1.display();
        }
    };
}

#endif