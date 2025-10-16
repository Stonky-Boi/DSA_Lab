#include <iostream>
#include "../../utility/convert_expression.hpp"

int main()
{
    exp_conv::convert_expression converter;

    std::string infix = "a+b*(c^d-e)^(f+g*h)-i";
    std::cout << "Infix to Postfix: " << converter.infix_to_postfix(infix) << std::endl;

    std::string prefix = "*-A/BC-/AKL";
    std::cout << "Prefix to Infix: " << converter.prefix_to_infix(prefix) << std::endl;

    std::unordered_map<char, int> values = {{'A', 2}, {'B', 3}, {'C', 10}, {'D', 8}, {'E', 4}, {'F', 5}, {'G', 2}, {'H', 2}, {'I', 2}, {'J', 1}};

    std::string postfix_eval = "AB^CDE/-*F+GHI^J-*/";
    std::cout << "Postfix Eval: " << converter.evaluate_postfix(postfix_eval, values) << std::endl;

    std::string prefix_eval = "/+*^AB-C/DEF*G-^HIJ";
    std::cout << "Prefix Eval: " << converter.evaluate_prefix(prefix_eval, values) << std::endl;

    std::string infix_eval = "((A^B)*(C-D/E)+F)/(G*(H^I-J))";
    std::cout << "Infix Eval: " << converter.evaluate_infix(infix_eval, values) << std::endl;

    return 0;
}