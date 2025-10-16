#ifndef queue_using_array
#define queue_using_array

#include <iostream>
#include <stdexcept>

namespace aq
{
    template <typename T>
    class Queue
    {
    private:
        T *arr;
        int capacity;
        int front;
        int rear;
        int count;

    public:

        Queue() {}

        Queue(int size)
        {
            if (size <= 0)
                throw std::invalid_argument("Queue size must be positive.");
            capacity = size;
            arr = new T[capacity];
            front = 0;
            rear = -1;
            count = 0;
        }

        ~Queue()
        {
            delete[] arr;
        }

        bool is_empty() const
        {
            return count == 0;
        }

        bool is_full() const
        {
            return count == capacity;
        }

        void enqueue(const T &value)
        {
            if (is_full())
                throw std::overflow_error("Queue Overflow: Cannot enqueue to full queue.");
            rear = (rear + 1) % capacity;
            arr[rear] = value;
            count++;
        }

        void dequeue()
        {
            if (is_empty())
                throw std::underflow_error("Queue Underflow: Cannot dequeue from empty queue.");
            front = (front + 1) % capacity;
            count--;
        }

        T peek() const
        {
            if (is_empty())
                throw std::underflow_error("Queue is empty: No front element.");
            return arr[front];
        }

        void display() const
        {
            if (is_empty())
            {
                std::cout << "Queue is empty." << std::endl;
                return;
            }
            std::cout << "Queue elements (front to rear): ";
            for (int i = 0; i < count; i++)
            {
                int index = (front + i) % capacity;
                std::cout << arr[index] << " ";
            }
            std::cout << std::endl;
        }
    };
}

#endif