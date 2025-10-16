#ifndef stack_using_array
#define stack_using_array

#include <iostream>
#include <stdexcept>

namespace as
{
    template <typename T>
    class Stack
    {
    private:
        T *arr;
        int capacity;
        int top;

    public:
        Stack() {}

        Stack(int size)
        {
            if (size <= 0)
                throw std::invalid_argument("Stack size must be positive.");
            capacity = size;
            arr = new T[capacity];
            top = -1;
        }

        ~Stack()
        {
            delete[] arr;
        }

        bool is_empty() const
        {
            return top == -1;
        }

        bool is_full() const
        {
            return top == capacity - 1;
        }

        void push(const T &value)
        {
            if (is_full())
                throw std::overflow_error("Stack Overflow: Cannot push to full stack.");
            arr[++top] = value;
        }

        void pop()
        {
            if (is_empty())
                throw std::underflow_error("Stack Underflow: Cannot pop from empty stack.");
            top--;
        }

        T peek() const
        {
            if (is_empty())
                throw std::underflow_error("Stack is empty: No top element.");
            return arr[top];
        }

        void display() const
        {
            if (is_empty())
            {
                std::cout << "Stack is empty." << std::endl;
                return;
            }
            std::cout << "Stack elements (top to bottom): ";
            for (int i = top; i >= 0; i--)
                std::cout << arr[i] << " ";
            std::cout << std::endl;
        }
    };
}

#endif