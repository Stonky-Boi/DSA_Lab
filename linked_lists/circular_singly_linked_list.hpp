#ifndef circular_singly_linked_list
#define circular_singly_linked_list

#include <iostream>
#include <vector>
#include <stdexcept>

namespace csll
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
    class CircularSinglyLinkedList
    {
    private:
        Node<T> *tail;

    public:
        CircularSinglyLinkedList()
        {
            tail = nullptr;
        }

        ~CircularSinglyLinkedList()
        {
            while (!is_empty())
                delete_from_beginning();
        }

        // Time Complexity: O(1)
        bool is_empty() const
        {
            return !tail;
        }

        // Time Complexity: O(1)
        void insert_at_beginning(const T &value)
        {
            Node<T> *new_node = new Node<T>(value);
            if (is_empty())
            {
                tail = new_node;
                new_node->next = new_node;
            }
            else
            {
                new_node->next = tail->next;
                tail->next = new_node;
            }
        }

        // Time Complexity: O(1)
        void insert_at_end(const T &value)
        {
            insert_at_beginning(value);
            tail = tail->next;
        }

        // Time Complexity: O(n)
        void insert_at_position(int index, const T &value)
        {
            if (index < 0)
                throw std::out_of_range("Invalid index");
            if (index == 0 || is_empty())
            {
                insert_at_beginning(value);
                return;
            }
            Node<T> *curr = tail->next;
            for (int i = 0; i < index - 1 && curr != tail; i++)
                curr = curr->next;
            Node<T> *new_node = new Node<T>(value);
            new_node->next = curr->next;
            curr->next = new_node;
            if (curr == tail)
                tail = new_node;
        }

        // Time Complexity: O(1)
        void delete_from_beginning()
        {
            if (is_empty())
                throw std::runtime_error("List is empty");
            Node<T> *head = tail->next;
            if (head == tail)
            {
                delete head;
                tail = nullptr;
            }
            else
            {
                tail->next = head->next;
                delete head;
            }
        }

        // Time Complexity: O(n)
        void delete_from_end()
        {
            if (is_empty())
                throw std::runtime_error("List is empty");
            Node<T> *head = tail->next;
            if (head == tail)
            {
                delete tail;
                tail = nullptr;
                return;
            }
            Node<T> *curr = head;
            while (curr->next != tail)
                curr = curr->next;
            curr->next = head;
            delete tail;
            tail = curr;
        }

        // Time Complexity: O(n)
        void delete_from_position(int index)
        {
            if (is_empty())
                throw std::runtime_error("List is empty");
            if (index < 0)
                throw std::out_of_range("Invalid index");
            if (index == 0)
            {
                delete_from_beginning();
                return;
            }
            Node<T> *curr = tail->next;
            for (int i = 0; i < index - 1 && curr->next != tail->next; i++)
                curr = curr->next;
            Node<T> *target = curr->next;
            if (target == tail)
                tail = curr;
            if (target == tail->next)
                tail->next = target->next;
            curr->next = target->next;
            delete target;
        }

        // Time Complexity: O(n)
        void delete_element(const T &value)
        {
            if (is_empty())
                throw std::runtime_error("List is empty");
            Node<T> *curr = tail;
            Node<T> *prev = nullptr;
            do
            {
                prev = curr;
                curr = curr->next;
                if (curr->data == value)
                {
                    if (curr == tail)
                        tail = prev;
                    if (curr == tail->next)
                        tail->next = curr->next;
                    prev->next = curr->next;
                    delete curr;
                    return;
                }
            } while (curr != tail);
            throw std::runtime_error("Element not found");
        }

        // Time Complexity: O(n)
        int search(const T &value) const
        {
            if (is_empty())
                return -1;
            Node<T> *curr = tail->next;
            int index = 0;
            do
            {
                if (curr->data == value)
                    return index;
                curr = curr->next;
                index++;
            } while (curr != tail->next);
            throw std::runtime_error("Element not found");
        }

        // Time Complexity: O(n)
        std::vector<int> search_all(const T &value) const
        {
            std::vector<int> indices;
            if (is_empty())
                return indices;
            Node<T> *curr = tail->next;
            int index = 0;
            do
            {
                if (curr->data == value)
                    indices.push_back(index);
                curr = curr->next;
                index++;
            } while (curr != tail->next);
            if (indices.empty())
                throw std::runtime_error("Element not found");
            return indices;
        }

        // Time Complexity: O(n²)
        void sort()
        {
            if (is_empty() || tail->next == tail)
                return;
            bool swapped;
            Node<T> *end = nullptr;
            do
            {
                swapped = false;
                Node<T> *curr = tail->next;
                while (curr->next != end && curr->next != tail->next)
                {
                    if (curr->data > curr->next->data)
                    {
                        std::swap(curr->data, curr->next->data);
                        swapped = true;
                    }
                    curr = curr->next;
                }
                end = curr;
            } while (swapped);
        }

        // Time Complexity: O(1)
        void merge(CircularSinglyLinkedList<T> &other)
        {
            if (other.is_empty())
                return;
            if (is_empty())
            {
                tail = other.tail;
                other.tail = nullptr;
                return;
            }
            Node<T> *temp1 = tail->next;
            Node<T> *temp2 = other.tail->next;
            tail->next = temp2;
            other.tail->next = temp1;
            tail = other.tail;
            other.tail = nullptr;
        }

        // Time Complexity: O(n)
        void display() const
        {
            if (is_empty())
            {
                std::cout << "List is empty" << std::endl;
                return;
            }
            Node<T> *curr = tail->next;
            do
            {
                std::cout << curr->data << " -> ";
                curr = curr->next;
            } while (curr != tail->next);
            std::cout << "(back to start)" << std::endl;
        }

        // Time Complexity: O(n)
        int count() const
        {
            if (is_empty())
                return 0;
            int counter = 0;
            Node<T> *curr = tail->next;
            do
            {
                counter++;
                curr = curr->next;
            } while (curr != tail->next);
            return counter;
        }

        // Time Complexity: O(1)
        bool is_circular() const
        {
            return tail && tail->next && tail->next != tail;
        }
    };
}

#endif