#ifndef sorting
#define sorting

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

class Sort
{
public:
    long long max_quick_recursion_depth;
    Sort() : max_quick_recursion_depth(0) {}

    void bubble_sort(std::vector<int> arr, bool early_stop = false)
    {
        auto start = std::chrono::high_resolution_clock::now();
        int n = arr.size();
        long long comparisons = 0, swaps = 0;
        for (int i = 0; i < n - 1; i++)
        {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++)
            {
                comparisons++;
                if (arr[j] > arr[j + 1])
                {
                    std::swap(arr[j], arr[j + 1]);
                    swaps++;
                    swapped = true;
                }
            }
            if (early_stop && !swapped)
                break;
        }
        auto end = std::chrono::high_resolution_clock::now();
        print_metrics("Bubble Sort", comparisons, swaps, end - start);
    }

    void selection_sort(std::vector<int> arr)
    {
        auto start = std::chrono::high_resolution_clock::now();
        int n = arr.size();
        long long comparisons = 0, swaps = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int min_idx = i;
            for (int j = i + 1; j < n; j++)
            {
                comparisons++;
                if (arr[j] < arr[min_idx])
                    min_idx = j;
            }
            if (min_idx != i)
            {
                std::swap(arr[i], arr[min_idx]);
                swaps++;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        print_metrics("Selection Sort", comparisons, swaps, end - start);
    }

    void insertion_sort(std::vector<int> arr)
    {
        auto start = std::chrono::high_resolution_clock::now();
        int n = arr.size();
        long long comparisons = 0, swaps = 0;
        for (int i = 1; i < n; i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && (++comparisons && arr[j] > key))
            {
                arr[j + 1] = arr[j];
                j--;
                swaps++;
            }
            arr[j + 1] = key;
        }
        auto end = std::chrono::high_resolution_clock::now();
        print_metrics("Insertion Sort", comparisons, swaps, end - start);
    }

    void quick_sort(std::vector<int> arr, std::string pivot_type = "first")
    {
        max_quick_recursion_depth = 0;
        int current_depth = 0;
        auto start = std::chrono::high_resolution_clock::now();
        long long comparisons = 0, swaps = 0;
        quick_sort_helper(arr, 0, arr.size() - 1, comparisons, swaps, pivot_type, current_depth);
        auto end = std::chrono::high_resolution_clock::now();
        print_metrics("Quick Sort (pivot=" + pivot_type + ")", comparisons, swaps, end - start, max_quick_recursion_depth);
    }

    void merge_sort(std::vector<int> arr)
    {
        auto start = std::chrono::high_resolution_clock::now();
        long long comparisons = 0;
        merge_sort_recursive(arr, 0, arr.size() - 1, comparisons);
        auto end = std::chrono::high_resolution_clock::now();
        print_metrics("Merge Sort (recursive)", comparisons, 0, end - start);
    }

    void merge_sort_iterative(std::vector<int> arr)
    {
        auto start = std::chrono::high_resolution_clock::now();
        int n = arr.size();
        long long comparisons = 0;
        size_t total_memory = 0;
        for (int curr_size = 1; curr_size < n; curr_size *= 2)
        {
            for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
            {
                int mid = std::min(left_start + curr_size - 1, n - 1);
                int right_end = std::min(left_start + 2 * curr_size - 1, n - 1);
                std::vector<int> L(arr.begin() + left_start, arr.begin() + mid + 1);
                std::vector<int> R(arr.begin() + mid + 1, arr.begin() + right_end + 1);
                total_memory += (L.size() + R.size()) * sizeof(int);
                int i = 0, j = 0, k = left_start;
                while (i < L.size() && j < R.size())
                {
                    comparisons++;
                    if (L[i] <= R[j])
                        arr[k++] = L[i++];
                    else
                        arr[k++] = R[j++];
                }
                while (i < L.size())
                    arr[k++] = L[i++];
                while (j < R.size())
                    arr[k++] = R[j++];
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        print_metrics("Merge Sort (iterative)", comparisons, 0, end - start, 0, total_memory);
    }

    void heap_sort(std::vector<int> arr, bool show_intermediate = false)
    {
        auto start = std::chrono::high_resolution_clock::now();
        int n = arr.size();
        long long comparisons = 0, swaps = 0;
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i, comparisons, swaps, show_intermediate);
        for (int i = n - 1; i > 0; i--)
        {
            std::swap(arr[0], arr[i]);
            swaps++;
            if (show_intermediate)
            {
                std::cout << "Heap after swap: ";
                print_array(arr);
            }
            heapify(arr, i, 0, comparisons, swaps, show_intermediate);
        }
        auto end = std::chrono::high_resolution_clock::now();
        print_metrics("Heap Sort", comparisons, swaps, end - start);
    }

private:
    void print_metrics(const std::string &name, long long comparisons, long long swaps, std::chrono::duration<double> duration, long long extra1 = 0, size_t extra2 = 0)
    {
        std::cout << std::endl;
        std::cout << "=== " << name << " ===" << std::endl;
        std::cout << "Comparisons: " << comparisons << std::endl;
        std::cout << "Swaps:       " << swaps << std::endl;
        std::cout << "Time:        " << duration.count() << " seconds" << std::endl;
        if (extra1 > 0)
            std::cout << "Max Recursion Depth: " << extra1 << std::endl;
        if (extra2 > 0)
            std::cout << "Memory Used (bytes): " << extra2 << std::endl;
        std::cout << "----------------------------" << std::endl;
    }

    void quick_sort_helper(std::vector<int> &arr, int low, int high, long long &comparisons, long long &swaps, std::string pivot_type, int current_depth)
    {
        if (low < high)
        {
            current_depth++;
            if (current_depth > max_quick_recursion_depth)
                max_quick_recursion_depth = current_depth;
            int pi = partition(arr, low, high, comparisons, swaps, pivot_type);
            quick_sort_helper(arr, low, pi - 1, comparisons, swaps, pivot_type, current_depth);
            quick_sort_helper(arr, pi + 1, high, comparisons, swaps, pivot_type, current_depth);
        }
    }

    int partition(std::vector<int> &arr, int low, int high, long long &comparisons, long long &swaps, std::string pivot_type)
    {
        int pivot_idx = low;
        if (pivot_type == "last")
            pivot_idx = high;
        else if (pivot_type == "random")
            pivot_idx = low + rand() % (high - low + 1);
        std::swap(arr[pivot_idx], arr[high]);
        swaps++;
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            comparisons++;
            if (arr[j] < pivot)
            {
                i++;
                std::swap(arr[i], arr[j]);
                swaps++;
            }
        }
        std::swap(arr[i + 1], arr[high]);
        swaps++;
        return i + 1;
    }

    void merge_sort_recursive(std::vector<int> &arr, int l, int r, long long &comparisons)
    {
        if (l >= r)
            return;
        int m = l + (r - l) / 2;
        merge_sort_recursive(arr, l, m, comparisons);
        merge_sort_recursive(arr, m + 1, r, comparisons);
        merge(arr, l, m, r, comparisons);
    }

    void merge(std::vector<int> &arr, int l, int m, int r, long long &comparisons)
    {
        std::vector<int> L(arr.begin() + l, arr.begin() + m + 1);
        std::vector<int> R(arr.begin() + m + 1, arr.begin() + r + 1);
        int i = 0, j = 0, k = l;
        while (i < L.size() && j < R.size())
        {
            comparisons++;
            if (L[i] <= R[j])
                arr[k++] = L[i++];
            else
                arr[k++] = R[j++];
        }
        while (i < L.size())
            arr[k++] = L[i++];
        while (j < R.size())
            arr[k++] = R[j++];
    }

    void heapify(std::vector<int> &arr, int n, int i, long long &comparisons, long long &swaps, bool show)
    {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && (++comparisons && arr[l] > arr[largest]))
            largest = l;
        if (r < n && (++comparisons && arr[r] > arr[largest]))
            largest = r;
        if (largest != i)
        {
            std::swap(arr[i], arr[largest]);
            swaps++;
            if (show)
            {
                std::cout << "Heap after heapify: ";
                print_array(arr);
            }
            heapify(arr, n, largest, comparisons, swaps, show);
        }
    }

    void print_array(const std::vector<int> &arr)
    {
        for (int x : arr)
            std::cout << x << " ";
        std::cout << std::endl;
    }
};

#endif