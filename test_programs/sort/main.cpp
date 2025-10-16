#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "../../utility/sort.hpp"

void print_header(const std::string &title)
{
    std::cout << std::endl;
    std::cout << "==================== " << title << " ====================";
    std::cout << std::endl;
}

std::vector<int> generate_large_random(int size)
{
    std::vector<int> v(size);
    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> dist(0, size * 10);
    for (int i = 0; i < size; i++)
        v[i] = dist(rng);
    return v;
}

int main()
{
    Sort sorter;
    std::vector<std::vector<int>> test_cases;
    test_cases.push_back({});
    test_cases.push_back({42});
    test_cases.push_back({1, 2, 3, 4, 5});
    test_cases.push_back({5, 4, 3, 2, 1});
    test_cases.push_back({7, 7, 7, 7, 7});
    test_cases.push_back(generate_large_random(100000));

    std::vector<std::string> test_names = {"Empty", "Single element", "Already sorted", "Reverse sorted", "All identical", "Large random"};

    for (int i = 0; i < test_cases.size(); i++)
    {
        print_header("Test case: " + test_names[i]);
        std::vector<int> arr;
        arr = test_cases[i];
        sorter.bubble_sort(arr, true);
        arr = test_cases[i];
        sorter.selection_sort(arr);
        arr = test_cases[i];
        sorter.insertion_sort(arr);
        sorter.quick_sort(arr, "first");
        arr = test_cases[i];
        sorter.quick_sort(arr, "last");
        arr = test_cases[i];
        sorter.quick_sort(arr, "random");
        arr = test_cases[i];
        sorter.merge_sort(arr);
        arr = test_cases[i];
        sorter.merge_sort_iterative(arr);
        arr = test_cases[i];
        bool show_heap = (arr.size() <= 10);
        sorter.heap_sort(arr, show_heap);
    }

    print_header("Theoretical Analysis");
    std::cout << "1. Time Complexity (Best / Worst / Average):" << std::endl;
    std::cout << "Bubble Sort: O(n) / O(n^2) / O(n^2)" << std::endl;
    std::cout << "Selection Sort: O(n^2) / O(n^2) / O(n^2)" << std::endl;
    std::cout << "Insertion Sort: O(n) / O(n^2) / O(n^2)" << std::endl;
    std::cout << "Quick Sort: O(n log n) / O(n^2) / O(n log n)" << std::endl;
    std::cout << "Merge Sort: O(n log n) / O(n log n) / O(n log n)" << std::endl;
    std::cout << "Heap Sort: O(n log n) / O(n log n) / O(n log n)" << std::endl;

    std::cout << std::endl;

    std::cout << "2. Space Complexity:" << std::endl;
    std::cout << "Bubble / Selection / Insertion / Heap / Quick: O(1) (in-place, Quick recursion stack O(log n) avg)" << std::endl;
    std::cout << "Merge Sort: O(n) for auxiliary arrays" << std::endl;

    std::cout << std::endl;

    std::cout << "3. Stability:" << std::endl;
    std::cout << "Stable: Bubble, Insertion, Merge" << std::endl;
    std::cout << "Not Stable: Selection, Quick, Heap" << std::endl;

    std::cout << std::endl;

    std::cout << "4. Practical Usability:" << std::endl;
    std::cout << "- Large datasets: Quick Sort, Merge Sort, Heap Sort" << std::endl;
    std::cout << "- Nearly sorted: Insertion Sort" << std::endl;
    std::cout << "- Small datasets: Bubble, Selection" << std::endl;

    std::cout << std::endl;

    std::cout << "5. Recursive vs Iterative:" << std::endl;
    std::cout << "- Recursive: Quick, Merge (stack usage must be considered)" << std::endl;
    std::cout << "- Iterative: Iterative Merge, Heap, Bubble, Selection, Insertion" << std::endl;

    return 0;
}