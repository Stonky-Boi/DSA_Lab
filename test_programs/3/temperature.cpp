#include <iostream>
#include <stack>

int main()
{
    int n;
    std::cout << "Enter number of days: ";
    std::cin >> n;
    int temperatures[n], answer[n];
    std::cout << "Enter the temperatures: ";
    for (int i = 0; i < n; i++)
    {
        std::cin >> temperatures[i];
        answer[i] = 0;
    }
    std::stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && temperatures[i] > temperatures[st.top()])
        {
            int prev = st.top();
            st.pop();
            answer[prev] = i - prev;
        }
        st.push(i);
    }
    std::cout << "Days to wait for warmer temperature: ";
    for (int i = 0; i < n; i++)
        std::cout << answer[i] << " ";
    std::cout << std::endl;
    return 0;
}