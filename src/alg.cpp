#include "alg.h"
#include "../include/TStack.h"  // Your TStack header
#include <string>
#include <cctype>
#include <map>

// Function to determine operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convert infix to postfix
std::string infx2pstfx(const std::string& infix) {
    TStack<char> stack;
    std::string postfix;
    
    for (char ch : infix) {
        if (isdigit(ch)) {
            postfix += ch;
        } 
        else if (ch == '(') {
            stack.push(ch);
        }
        else if (ch == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                postfix += stack.pop();
            }
            if (!stack.isEmpty()) stack.pop(); // Remove '('
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!stack.isEmpty() && stack.top() != '(' && 
                   precedence(stack.top()) >= precedence(ch)) {
                postfix += stack.pop();
            }
            stack.push(ch);
        }
    }
    
    while (!stack.isEmpty()) {
        postfix += stack.pop();
    }
    
    return postfix;
}

// Evaluate postfix expression
double eval(const std::string& postfix) {
    TStack<double> stack;
    
    for (char ch : postfix) {
        if (isdigit(ch)) {
            stack.push(ch - '0');  // Convert char to int
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            double b = stack.pop();
            double a = stack.pop();
            double result;
            
            switch (ch) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }
            stack.push(result);
        }
    }
    
    return stack.pop();
}
