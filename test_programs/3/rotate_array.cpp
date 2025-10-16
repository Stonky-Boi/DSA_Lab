#include <iostream>

void reverse(int arr[], int start, int end)
{
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int main()
{
    int n, k;
    std::cout << "Enter number of elements: ";
    std::cin >> n;
    int nums[n];
    std::cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
        std::cin >> nums[i];
    std::cout << "Enter k: ";
    std::cin >> k;
    k = k % n;
    reverse(nums, 0, n - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, n - 1);
    std::cout << "Rotated array: ";
    for (int i = 0; i < n; i++)
        std::cout << nums[i] << " ";
    std::cout << std::endl;
    return 0;
}