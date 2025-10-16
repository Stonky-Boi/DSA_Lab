// Print all elements of a queue without using extra space

#include <iostream>
#include <queue>

void print(std::queue<int> &qu)
{
    int size = qu.size();
    for (int i = 0; i < size; i++)
    {
        int val = qu.front();
        qu.pop();
        std::cout << val << " ";
        qu.push(val);
    }
    std::cout << std::endl;
}

int main()
{
    std::queue<int> qu;
    qu.push(4);
    qu.push(8);
    qu.push(98);
    qu.push(12);
    qu.push(3);
    qu.push(55);
    print(qu);
    return 0;
}