#ifndef expression_converter
#define expression_converter

#include <iostream>
#include <stdexcept>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include "../stacks/stack_linked_list.hpp"

namespace exp_conv
{
    class convert_expression
    {
    private:
        int precedence(char operand)
        {
            switch (operand)
            {
            case '+':
                return 1;
            case '-':
                return 1;
            case '*':
                return 2;
            case '/':
                return 2;
            case '^':
                return 3;
            default:
                return 0;
            }
        }

        int apply_operation(int a, int b, char operand)
        {
            switch (operand)
            {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                if (b == 0)
                    throw std::runtime_error("Division by zero is not defined");
                return a / b;
            case '^':
                return std::pow(a, b);
            default:
                throw std::runtime_error("Unknown operator");
            }
        }

    public:
        std::string infix_to_prefix(const std::string &infix)
        {
            std::string reversed = infix;
            std::reverse(reversed.begin(), reversed.end());
            for (char &c : reversed)
            {
                if (c == '(')
                    c = ')';
                else if (c == ')')
                    c = '(';
            }
            std::string postfix = infix_to_postfix(reversed);
            std::reverse(postfix.begin(), postfix.end());
            return postfix;
        }

        std::string infix_to_postfix(const std::string &infix)
        {
            lls::Stack<char> stack;
            std::string postfix;
            for (char character : infix)
            {
                if (std::isalnum(character))
                    postfix += character;
                else if (character == '(')
                    stack.push(character);
                else if (character == ')')
                {
                    while (!stack.is_empty() && stack.peek() != '(')
                    {
                        postfix += stack.peek();
                        stack.pop();
                    }
                    stack.pop();
                }
                else
                {
                    while (!stack.is_empty() && precedence(stack.peek()) >= precedence(character))
                    {
                        postfix += stack.peek();
                        stack.pop();
                    }
                    stack.push(character);
                }
            }
            while (!stack.is_empty())
            {
                postfix += stack.peek();
                stack.pop();
            }
            return postfix;
        }

        std::string prefix_to_infix(const std::string &prefix)
        {
            lls::Stack<std::string> stack;
            for (auto it = prefix.rbegin(); it != prefix.rend(); ++it)
            {
                char character = *it;
                if (std::isalnum(character))
                    stack.push(std::string(1, character));
                else
                {
                    std::string a = stack.peek();
                    stack.pop();
                    std::string b = stack.peek();
                    stack.pop();
                    stack.push("(" + a + character + b + ")");
                }
            }
            return stack.peek();
        }

        std::string prefix_to_postfix(const std::string &prefix)
        {
            lls::Stack<std::string> stack;
            for (auto it = prefix.rbegin(); it != prefix.rend(); ++it)
            {
                char character = *it;
                if (std::isalnum(character))
                    stack.push(std::string(1, character));
                else
                {
                    std::string a = stack.peek();
                    stack.pop();
                    std::string b = stack.peek();
                    stack.pop();
                    stack.push(a + b + character);
                }
            }
            return stack.peek();
        }

        std::string postfix_to_infix(const std::string &postfix)
        {
            lls::Stack<std::string> stack;
            for (char character : postfix)
            {
                if (std::isalnum(character))
                    stack.push(std::string(1, character));
                else
                {
                    std::string b = stack.peek();
                    stack.pop();
                    std::string a = stack.peek();
                    stack.pop();
                    stack.push("(" + a + character + b + ")");
                }
            }
            return stack.peek();
        }

        std::string postfix_to_prefix(const std::string &postfix)
        {
            lls::Stack<std::string> stack;
            for (char character : postfix)
            {
                if (std::isalnum(character))
                    stack.push(std::string(1, character));
                else
                {
                    std::string b = stack.peek();
                    stack.pop();
                    std::string a = stack.peek();
                    stack.pop();
                    stack.push(character + a + b);
                }
            }
            return stack.peek();
        }

        int evaluate_infix(const std::string &infix, std::unordered_map<char, int> &values)
        {
            lls::Stack<int> value;
            lls::Stack<char> operations;
            for (char character : infix)
            {
                if (character == ' ')
                    continue;
                if (std::isalnum(character))
                    value.push(values[character]);
                else if (character == '(')
                    operations.push(character);
                else if (character == ')')
                {
                    while (!operations.is_empty() && operations.peek() != '(')
                    {
                        int b = value.peek();
                        value.pop();
                        int a = value.peek();
                        value.pop();
                        char operand = operations.peek();
                        operations.pop();
                        value.push(apply_operation(a, b, operand));
                    }
                    operations.pop();
                }
                else
                {
                    while (!operations.is_empty() && precedence(operations.peek()) >= precedence(character))
                    {
                        int b = value.peek();
                        value.pop();
                        int a = value.peek();
                        value.pop();
                        char operand = operations.peek();
                        operations.pop();
                        value.push(apply_operation(a, b, operand));
                    }
                    operations.push(character);
                }
            }
            while (!operations.is_empty())
            {
                int b = value.peek();
                value.pop();
                int a = value.peek();
                value.pop();
                char operand = operations.peek();
                operations.pop();
                value.push(apply_operation(a, b, operand));
            }
            return value.peek();
        }

        int evaluate_prefix(const std::string &prefix, std::unordered_map<char, int> &values)
        {
            lls::Stack<int> stack;
            for (auto it = prefix.rbegin(); it != prefix.rend(); ++it)
            {
                char character = *it;
                if (std::isalnum(character))
                    stack.push(values[character]);
                else
                {
                    int a = stack.peek();
                    stack.pop();
                    int b = stack.peek();
                    stack.pop();
                    stack.push(apply_operation(a, b, character));
                }
            }
            return stack.peek();
        }

        int evaluate_postfix(const std::string &postfix, std::unordered_map<char, int> &values)
        {
            lls::Stack<int> stack;
            for (char character : postfix)
            {
                if (std::isalnum(character))
                    stack.push(values[character]);
                else
                {
                    int b = stack.peek();
                    stack.pop();
                    int a = stack.peek();
                    stack.pop();
                    stack.push(apply_operation(a, b, character));
                }
            }
            return stack.peek();
        }
    };
}

#endif