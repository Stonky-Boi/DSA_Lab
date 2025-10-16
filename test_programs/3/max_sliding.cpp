#include <iostream>
#include <deque>

int main()
{
    int n, k;
    std::cout << "Enter number of elements: ";
    std::cin >> n;
    int nums[n];
    std::cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
        std::cin >> nums[i];
    std::cout << "Enter window size: ";
    std::cin >> k;
    int index = 0, result[n - k + 1];
    std::deque<int> dq;
    for (int i = 0; i < n; i++)
    {
        if (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();
        while (!dq.empty() && nums[dq.back()] <= nums[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            result[index++] = nums[dq.front()];
    }
    std::cout << "Sliding Window Maximums: ";
    for (int i = 0; i < n - k + 1; i++)
        std::cout << result[i] << " ";
    std::cout << std::endl;
    return 0;
}