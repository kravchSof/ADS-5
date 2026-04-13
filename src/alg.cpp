// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

int getPriority(char op) {
    switch (op) {
        case '(': return 0;
        case ')': return 1;
        case '+': return 2;
        case '-': return 2;
        case '*': return 3;
        case '/': return 3;
        default: return -1;
    }
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result = "";

    for (size_t i = 0; i < inf.length(); ++i) {
        char ch = inf[i];

        if (ch == ' ') {
            continue;
        }

        if (isdigit(ch)) {
            while (i < inf.length() && isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
            --i;
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                result += stack.pop();
                result += ' ';
            }
            if (!stack.isEmpty() && stack.top() == '(') {
                stack.pop();
            }
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!stack.isEmpty() &&
                   getPriority(stack.top()) >= getPriority(ch)) {
                result += stack.pop();
                result += ' ';
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty()) {
        result += stack.pop();
        result += ' ';
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

int eval(const std::string& pref) {
    TStack<int, 100> stack;

    for (size_t i = 0; i < pref.length(); ++i) {
        char ch = pref[i];

        if (ch == ' ') {
            continue;
        }

        if (isdigit(ch)) {
            int number = 0;
            while (i < pref.length() && isdigit(pref[i])) {
                number = number * 10 + (pref[i] - '0');
                ++i;
            }
            stack.push(number);
            --i;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            int operand2 = stack.pop();
            int operand1 = stack.pop();
            int result = 0;

            switch (ch) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
            }
            stack.push(result);
        }
    }

    return stack.pop();
}
