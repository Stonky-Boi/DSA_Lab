#ifndef doubly_linked_list
#define doubly_linked_list

#include <iostream>
#include <stdexcept>
#include <vector>

namespace dll
{
    template <typename T>
    class Node
    {
    public:
        T data;
        Node<T> *next;
        Node<T> *prev;

        Node(const T &value)
        {
            data = value;
            next = nullptr;
            prev = nullptr;
        }
    };

    template <typename T>
    class DoublyLinkedList
    {
    private:
        Node<T> *head;
        Node<T> *tail;

    public:
        DoublyLinkedList()
        {
            head = nullptr;
            tail = nullptr;
        }

        ~DoublyLinkedList()
        {
            while (head)
            {
                Node<T> *temp = head;
                head = head->next;
                delete temp;
            }
        }

        // Time Complexity: O(1)
        void insert_at_beginning(const T &value)
        {
            Node<T> *node = new Node<T>(value);
            node->next = head;
            if (head)
                head->prev = node;
            else
                tail = node;
            head = node;
        }

        // Time Complexity: O(1)
        void insert_at_end(const T &value)
        {
            Node<T> *node = new Node<T>(value);
            node->prev = tail;
            if (tail)
                tail->next = node;
            else
                head = node;
            tail = node;
        }

        // Time Complexity: O(n)
        void insert_at_position(int index, const T &value)
        {
            if (index < 0)
                throw std::out_of_range("Invalid index");
            if (index == 0)
            {
                insert_at_beginning(value);
                return;
            }
            Node<T> *curr = head;
            for (int i = 0; i < index - 1 && curr; i++)
                curr = curr->next;
            if (!curr)
                throw std::out_of_range("Index exceeds list length");
            if (!curr->next)
            {
                insert_at_end(value);
                return;
            }
            Node<T> *node = new Node<T>(value);
            node->next = curr->next;
            node->prev = curr;
            curr->next->prev = node;
            curr->next = node;
        }

        // Time Complexity: O(1)
        void delete_from_beginning()
        {
            if (!head)
                throw std::runtime_error("List is empty");
            Node<T> *temp = head;
            head = head->next;
            if (head)
                head->prev = nullptr;
            else
                tail = nullptr;
            delete temp;
        }

        // Time Complexity: O(1)
        void delete_from_end()
        {
            if (!tail)
                throw std::runtime_error("List is empty");
            Node<T> *temp = tail;
            tail = tail->prev;
            if (tail)
                tail->next = nullptr;
            else
                head = nullptr;
            delete temp;
        }

        // Time Complexity: O(n)
        void delete_from_position(int index)
        {
            if (index < 0)
                throw std::out_of_range("Invalid index");
            if (!head)
                throw std::runtime_error("List is empty");
            if (index == 0)
            {
                delete_from_beginning();
                return;
            }
            Node<T> *curr = head;
            for (int i = 0; i < index && curr; i++)
                curr = curr->next;
            if (!curr)
                throw std::out_of_range("Index exceeds list length");
            if (curr->prev)
                curr->prev->next = curr->next;
            if (curr->next)
                curr->next->prev = curr->prev;
            if (curr == head)
                head = curr->next;
            if (curr == tail)
                tail = curr->prev;
            delete curr;
        }

        // Time Complexity: O(n)
        void delete_element(const T &value)
        {
            if (!head)
                throw std::runtime_error("List is empty");
            Node<T> *curr = head;
            while (curr)
            {
                if (curr->data == value)
                {
                    if (curr == head)
                        delete_from_beginning();
                    else if (curr == tail)
                        delete_from_end();
                    else
                    {
                        curr->prev->next = curr->next;
                        curr->next->prev = curr->prev;
                        delete curr;
                    }
                    return;
                }
                curr = curr->next;
            }
            throw std::runtime_error("Element not found");
        }

        // Time Complexity: O(n)
        int search(const T &value) const
        {
            Node<T> *curr = head;
            int index = 0;
            while (curr)
            {
                if (curr->data == value)
                    return index;
                curr = curr->next;
                index++;
            }
            throw std::runtime_error("Element not found");
        }

        // Time Complexity: O(n)
        std::vector<int> search_all(const T &value) const
        {
            Node<T> *curr = head;
            std::vector<int> indices;
            int index = 0;
            while (curr)
            {
                if (curr->data == value)
                    indices.push_back(index);
                curr = curr->next;
                index++;
            }
            if (indices.empty())
                throw std::runtime_error("Element not found");
            return indices;
        }

        // Time Complexity: O(n²)
        void sort()
        {
            if (!head || !head->next)
                return;
            for (Node<T> *i = head; i; i = i->next)
                for (Node<T> *j = i->next; j; j = j->next)
                    if (j->data < i->data)
                        std::swap(i->data, j->data);
        }

        // Time Complexity: O(1)
        void merge(DoublyLinkedList<T> &other)
        {
            if (!other.head)
                return;
            if (!head)
            {
                head = other.head;
                tail = other.tail;
            }
            else
            {
                tail->next = other.head;
                other.head->prev = tail;
                tail = other.tail;
            }
            other.head = other.tail = nullptr;
        }

        // Time Complexity: O(n)
        void display_forward() const
        {
            Node<T> *curr = head;
            while (curr)
            {
                std::cout << curr->data << " <-> ";
                curr = curr->next;
            }
            std::cout << "NULL" << std::endl;
        }

        // Time Complexity: O(n)
        void display_backward() const
        {
            Node<T> *curr = tail;
            while (curr)
            {
                std::cout << curr->data << " <-> ";
                curr = curr->prev;
            }
            std::cout << "NULL" << std::endl;
        }

        // Time Complexity: O(n)
        int count() const
        {
            int counter = 0;
            Node<T> *curr = head;
            while (curr)
            {
                counter++;
                curr = curr->next;
            }
            return counter;
        }

        // Time Complexity: O(1)
        bool is_empty() const
        {
            return !head;
        }
    };
}

#endif