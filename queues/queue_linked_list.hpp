#ifndef queue_using_ll
#define queue_using_ll

#include <iostream>
#include <stdexcept>
#include "../linked_lists/singly_linked_list.hpp"

namespace llq
{
    template <typename T>
    class Queue
    {
    private:
        sll::SinglyLinkedList<T> list;

    public:
        void enqueue(const T &value)
        {
            list.insert_at_end(value);
        }

        void dequeue()
        {
            if (is_empty())
                throw std::runtime_error("Queue underflow: Cannot dequeue from empty queue");
            list.delete_from_beginning();
        }

        T peek() const
        {
            if (is_empty())
                throw std::runtime_error("Queue is empty: No front element");
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