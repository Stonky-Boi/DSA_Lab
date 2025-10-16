#ifndef singly_linked_list
#define singly_linked_list

#include <iostream>
#include <stdexcept>
#include <vector>

namespace sll
{
    template <typename T>
    class Node
    {
    public:
        T data;
        Node<T> *next;

        Node(const T &value)
        {
            data = value;
            next = nullptr;
        }
    };

    template <typename T>
    class SinglyLinkedList
    {
    private:
        Node<T> *head;

    public:
        SinglyLinkedList()
        {
            head = nullptr;
        }

        ~SinglyLinkedList()
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
            head = node;
        }

        // Time Complexity: O(n)
        void insert_at_end(const T &value)
        {
            Node<T> *node = new Node<T>(value);
            if (!head)
            {
                head = node;
                return;
            }
            Node<T> *curr = head;
            while (curr->next)
                curr = curr->next;
            curr->next = node;
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
            Node<T> *node = new Node<T>(value);
            node->next = curr->next;
            curr->next = node;
        }

        // Time Complexity: O(1)
        void delete_from_beginning()
        {
            if (!head)
                throw std::runtime_error("List is empty");
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }

        // Time Complexity: O(n)
        void delete_from_end()
        {
            if (!head)
                throw std::runtime_error("List is empty");
            if (!head->next)
            {
                delete head;
                head = nullptr;
                return;
            }
            Node<T> *curr = head;
            while (curr->next->next)
                curr = curr->next;
            delete curr->next;
            curr->next = nullptr;
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
            for (int i = 0; i < index - 1 && curr->next; i++)
                curr = curr->next;
            if (!curr->next)
                throw std::out_of_range("Index exceeds list length");
            Node<T> *temp = curr->next;
            curr->next = temp->next;
            delete temp;
        }

        // Time Complexity: O(n)
        void delete_element(const T &value)
        {
            if (!head)
                throw std::runtime_error("List is empty");
            if (head->data == value)
            {
                delete_from_beginning();
                return;
            }
            Node<T> *curr = head;
            while (curr->next && curr->next->data != value)
                curr = curr->next;
            if (!curr->next)
                throw std::runtime_error("Element not found");
            Node<T> *temp = curr->next;
            curr->next = temp->next;
            delete temp;
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

        // Time Complexity: O(n)
        void merge(SinglyLinkedList<T> &other)
        {
            if (!head)
            {
                head = other.head;
                other.head = nullptr;
                return;
            }
            Node<T> *curr = head;
            while (curr->next)
                curr = curr->next;
            curr->next = other.head;
            other.head = nullptr;
        }

        // Time Complexity: O(n)
        void reverse()
        {
            Node<T> *prev = nullptr;
            Node<T> *curr = head;
            while (curr)
            {
                Node<T> *next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            head = prev;
        }

        // Time Complexity: O(n)
        void display() const
        {
            Node<T> *curr = head;
            while (curr)
            {
                std::cout << curr->data << " -> ";
                curr = curr->next;
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

        // Time Complexity: O(n)
        T find_max() const
        {
            if (!head)
                throw std::runtime_error("Empty list");
            T max_value = head->data;
            Node<T> *curr = head->next;
            while (curr)
            {
                if (curr->data > max_value)
                    max_value = curr->data;
                curr = curr->next;
            }
            return max_value;
        }

        // Time Complexity: O(n)
        T find_min() const
        {
            if (!head)
                throw std::runtime_error("Empty list");
            T min_val = head->data;
            Node<T> *curr = head->next;
            while (curr)
            {
                if (curr->data < min_val)
                    min_val = curr->data;
                curr = curr->next;
            }
            return min_val;
        }

        // This is a helper function to aid in implementing peek function in stack and queue
        T get_head_data() const
        {
            if (!head)
                throw std::runtime_error("List is empty");
            return head->data;
        }
    };
}

#endif