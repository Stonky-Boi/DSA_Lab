// Design and Implement an LRU using queue and hashing

#include <iostream>
#include <map>
#include <queue>

void refer(int x, int capacity, std::queue<int> &q, std::map<int, bool> &hash)
{
    if (!hash[x])
    {
        if (q.size() == capacity)
        {
            int lru = q.front();
            q.pop();
            hash[lru] = false;
        }
    }
    else
    {
        std::queue<int> temp;
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            if (curr != x)
                temp.push(curr);
        }
        q = temp;
    }
    q.push(x);
    hash[x] = true;
}

int main()
{
    int capacity = 3;
    std::queue<int> q;
    std::map<int, bool> hash;
    refer(1, capacity, q, hash);
    refer(2, capacity, q, hash);
    refer(3, capacity, q, hash);
    refer(1, capacity, q, hash);
    refer(4, capacity, q, hash);
    std::cout << "LRU Cache: ";
    std::queue<int> temp = q;
    while (!temp.empty())
    {
        std::cout << temp.front() << " ";
        temp.pop();
    }
    std::cout << std::endl;
    return 0;
}