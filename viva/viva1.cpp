// Sort a stack using recursion

#include <iostream>
#include <stack>

void insert(std::stack<int> &st, int element)
{
    if (st.empty() || element > st.top())
    {
        st.push(element);
        return;
    }
    int top = st.top();
    st.pop();
    insert(st, element);
    st.push(top);
}

void sort(std::stack<int> &st)
{
    if (st.empty())
        return;
    int element = st.top();
    st.pop();
    sort(st);
    insert(st, element);
}

int main()
{
    std::stack<int> st;
    st.push(2);
    st.push(7);
    st.push(5);
    st.push(8);
    sort(st);
    std::cout << st.top() << std::endl;
    st.pop();
    std::cout << st.top() << std::endl;
    st.pop();
    std::cout << st.top() << std::endl;
    st.pop();
    std::cout << st.top() << std::endl;
    st.pop();
    return 0;
}