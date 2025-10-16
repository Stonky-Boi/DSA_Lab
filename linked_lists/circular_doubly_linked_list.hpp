#ifndef circular_doubly_linked_list
#define circular_doubly_linked_list

#include <iostream>
#include <vector>
#include <stdexcept>

namespace cdll
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
            next = prev = nullptr;
        }
    };

    template <typename T>
    class CircularDoublyLinkedList
    {
    private:
        Node<T> *head;

    public:
        CircularDoublyLinkedList()
        {
            head = nullptr;
        }

        ~CircularDoublyLinkedList()
        {
            if (!head)
                return;
            Node<T> *curr = head->next;
            while (curr != head)
            {
                Node<T> *next = curr->next;
                delete curr;
                curr = next;
            }
            delete head;
            head = nullptr;
        }

        // Time Complexity: O(1)
        bool is_empty() const
        {
            return !head;
        }

        // Time Complexity: O(1)
        bool is_circular() const
        {
            return head && head->next && head->prev && head->prev->next == head && head->next->prev == head;
        }

        // Time Complexity: O(n)
        int count() const
        {
            if (!head)
                return 0;
            int counter = 1;
            Node<T> *curr = head->next;
            while (curr != head)
            {
                counter++;
                curr = curr->next;
            }
            return counter;
        }

        // Time Complexity: O(1)
        void insert_at_beginning(const T &value)
        {
            Node<T> *node = new Node<T>(value);
            if (!head)
            {
                node->next = node;
                node->prev = node;
                head = node;
                return;
            }
            Node<T> *tail = head->prev;
            node->next = head;
            node->prev = tail;
            head->prev = node;
            tail->next = node;
            head = node;
        }

        // Time Complexity: O(1)
        void insert_at_end(const T &value)
        {
            if (!head)
            {
                insert_at_beginning(value);
                return;
            }
            Node<T> *node = new Node<T>(value);
            Node<T> *tail = head->prev;
            node->next = head;
            node->prev = tail;
            tail->next = node;
            head->prev = node;
        }

        // Time Complexity: O(n)
        void insert_at_position(int index, const T &value)
        {
            int n = count();
            if (index < 0 || index > n)
                throw std::out_of_range("Invalid index");
            if (index == 0)
            {
                insert_at_beginning(value);
                return;
            }
            if (index == n)
            {
                insert_at_end(value);
                return;
            }
            Node<T> *curr = head;
            for (int i = 0; i < index - 1; i++)
                curr = curr->next;
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
            if (head->next == head)
            {
                delete head;
                head = nullptr;
                return;
            }
            Node<T> *tail = head->prev;
            Node<T> *temp = head;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete temp;
        }

        // Time Complexity: O(1)
        void delete_from_end()
        {
            if (!head)
                throw std::runtime_error("List is empty");
            if (head->next == head)
            {
                delete head;
                head = nullptr;
                return;
            }
            Node<T> *tail = head->prev;
            tail->prev->next = head;
            head->prev = tail->prev;
            delete tail;
        }

        // Time Complexity: O(n)
        void delete_from_position(int index)
        {
            int n = count();
            if (index < 0 || index >= n)
                throw std::out_of_range("Invalid index");
            if (index == 0)
            {
                delete_from_beginning();
                return;
            }
            if (index == n - 1)
            {
                delete_from_end();
                return;
            }
            Node<T> *curr = head;
            for (int i = 0; i < index; i++)
                curr = curr->next;
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
        }

        // Time Complexity: O(n)
        void delete_element(const T &value)
        {
            if (!head)
                throw std::runtime_error("List is empty");
            Node<T> *curr = head;
            int index = 0;
            do
            {
                if (curr->data == value)
                {
                    delete_from_position(index);
                    return;
                }
                curr = curr->next;
                index++;
            } while (curr != head);
            throw std::runtime_error("Element not found");
        }

        // Time Complexity: O(n)
        int search(const T &value) const
        {
            if (!head)
                return -1;
            Node<T> *curr = head;
            int index = 0;
            do
            {
                if (curr->data == value)
                    return index;
                curr = curr->next;
                index++;
            } while (curr != head);
            throw std::runtime_error("Element not found");
        }

        // Time Complexity: O(n)
        std::vector<int> search_all(const T &value) const
        {
            {
                std::vector<int> indices;
                if (!head)
                    return indices;
                Node<T> *temp = head;
                int index = 0;
                do
                {
                    if (temp->data == value)
                        indices.push_back(index);
                    temp = temp->next;
                    index++;
                } while (temp != head);
                if (indices.empty())
                    throw std::runtime_error("Element not found");
                return indices;
            }
        }

        // Time Complexity: O(n²)
        void sort()
        {
            if (!head || head->next == head)
                return;
            bool swapped;
            do
            {
                swapped = false;
                Node<T> *curr = head;
                do
                {
                    Node<T> *next = curr->next;
                    if (next != head && curr->data > next->data)
                    {
                        std::swap(curr->data, next->data);
                        swapped = true;
                    }
                    curr = curr->next;
                } while (curr->next != head);
            } while (swapped);
        }

        // Time Complexity: O(1)
        void merge(CircularDoublyLinkedList<T> &other)
        {
            if (other.is_empty())
                return;
            if (is_empty())
            {
                head = other.head;
                other.head = nullptr;
                return;
            }
            Node<T> *tail1 = head->prev;
            Node<T> *tail2 = other.head->prev;
            tail1->next = other.head;
            other.head->prev = tail1;
            tail2->next = head;
            head->prev = tail2;
            other.head = nullptr;
        }

        // Time Complexity: O(n)
        void display_forward() const
        {
            if (!head)
            {
                std::cout << "List is empty" << std::endl;
                return;
            }
            Node<T> *curr = head;
            do
            {
                std::cout << curr->data << " ";
                curr = curr->next;
            } while (curr != head);
            std::cout << std::endl;
        }

        // Time Complexity: O(n)
        void display_backward() const
        {
            if (!head)
            {
                std::cout << "List is empty" << std::endl;
                return;
            }
            Node<T> *tail = head->prev;
            Node<T> *curr = tail;
            do
            {
                std::cout << curr->data << " ";
                curr = curr->prev;
            } while (curr != tail);
            std::cout << std::endl;
        }
    };
}

#endif