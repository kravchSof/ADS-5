// Copyright 2025 NNTU-CS

#include <string>
#include <stack>
#include <cctype>
#include <sstream>
#include <stdexcept>

int Oper(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    std::stack<char> ops;
    std::string output;

    for (size_t i = 0; i < inf.length(); ++i) {
        char tkn = inf[i];

        if (std::isalnum(tkn)) {
            if (!output.empty() && output.back() != ' ') {
                output += ' ';
            }
            output += tkn;
        } else if (tkn == '+' || tkn == '-' ||
                   tkn == '*' || tkn == '/') {
            while (!ops.empty() && ops.top() != '(' &&
                   Oper(ops.top()) >= Oper(tkn)) {
                if (!output.empty() && output.back() != ' ') {
                    output += ' ';
                }
                output += ops.top();
                ops.pop();
            }
            ops.push(tkn);
        } else if (tkn == '(') {
            ops.push(tkn);
        } else if (tkn == ')') {
            bool foundOpeningBracket = false;
            while (!ops.empty()) {
                char topOp = ops.top();
                if (topOp == '(') {
                    foundOpeningBracket = true;
                    ops.pop();
                    break;
                }
                if (!output.empty() && output.back() != ' ') {
                    output += ' ';
                }
                output += topOp;
                ops.pop();
            }

            if (!foundOpeningBracket) {
                throw std::runtime_error("Mismatched parentheses");
            }
        }
    }

    while (!ops.empty()) {
        if (!output.empty() && output.back() != ' ') {
            output += ' ';
        }
        output += ops.top();
        ops.pop();
    }
    if (!output.empty() && output[0] == ' ') {
        output.erase(0, 1);
    }
    return output;
}

int eval(const std::string& post) {
    std::stack<int> values;
    std::istringstream iss(post);
    std::string tkn;

    while (iss >> tkn) {
        if (std::isdigit(tkn[0]) ||
            (tkn[0] == '-' && tkn.length() > 1 &&
             std::isdigit(tkn[1]))) {
            values.push(std::stoi(tkn));
        } else {
            if (values.size() < 2) {
                throw std::runtime_error(
                    "Invalid expression: insufficient operands");
            }
            int right = values.top(); values.pop();
            int left = values.top(); values.pop();

            switch (tkn[0]) {
                case '+':
                    values.push(left + right);
                    break;
                case '-':
                    values.push(left - right);
                    break;
                case '*':
                    values.push(left * right);
                    break;
                case '/':
                    if (right == 0) {
                        throw std::runtime_error("Division by zero");
                    }
                    values.push(left / right);
                    break;
                default:
                    throw std::runtime_error("Unknown operator");
            }
        }
    }

    if (values.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }
    return values.top();
}
