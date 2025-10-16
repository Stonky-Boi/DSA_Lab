#include <iostream>
#include <stack>

int main()
{
    int n;
    std::cout << "Enter number of elements: ";
    std::cin >> n;
    int strengths[n], next_greater[n];
    std::cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
    {
        std::cin >> strengths[i];
        next_greater[i] = -1;
    }
    std::stack<int> st;
    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && st.top() <= strengths[i])
            st.pop();
        if (!st.empty())
            next_greater[i] = st.top();
        st.push(strengths[i]);
    }
    std::cout << "Next Greater Elements: ";
    for (int i = 0; i < n; i++)
        std::cout << next_greater[i] << " ";
    std::cout << std::endl;
    return 0;
}