#include <iostream>
#include <stack>

int main()
{
    std::string s;
    std::cout << "Enter the string of brackets: ";
    std::cin >> s;
    std::stack<char> st;
    bool valid = true;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
            st.push(s[i]);
        else
        {
            if (st.empty())
            {
                valid = false;
                break;
            }
            char top = st.top();
            st.pop();
            if ((s[i] == ')' && top != '(') || (s[i] == '}' && top != '{') || (s[i] == ']' && top != '['))
            {
                valid = false;
                break;
            }
        }
    }
    if (!st.empty())
        valid = false;
    std::cout << (valid ? "The string is valid." : "The string is invalid.") << std::endl;
    return 0;
}