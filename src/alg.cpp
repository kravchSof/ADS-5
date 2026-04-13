// Copyright 2025 NNTU-CS
#include <iostream>
#include <map>
#include <string>
#include <cstdint>
#include "tstack.h"


bool isDigit(char sym) { return sym >= 48 && sym <= 57; }

bool isOperator(char sym) {
  return sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '(' ||
         sym == ')';
}

uint8_t getPrior(char oper) {
  std::map<char, uint8_t> prior = {
      {'(', 0}, {')', 1}, {'+', 2}, {'-', 2}, {'*', 3}, {'/', 3},
  };

  return prior[oper];
}

int calc(char oper, int x, int y) {
  switch (oper) {
  case '+':
    return x + y;
  case '-':
    return x - y;
  case '*':
    return x * y;
  case '/':
    return x / y;
  default:
    return 0;
  }
}

std::string infx2pstfx(const std::string &inf) { //(2-1)*(6+2)
  std::string output;
  TStack<char> operations;
  for (char sym : inf) {
    if (isDigit(sym)) {
      output += sym;
      output += ' ';
    } else if (isOperator(sym)) {
        if (sym == '(') {
        operations.push(sym);
      } else if (sym == ')') {
        while (!operations.isEmpty() && operations.top() != '(') {
          output += operations.pop();
          output += ' ';
        }
        operations.pop();

      } else if (operations.isEmpty() ||
                 getPrior(sym) > getPrior(operations.top())) {
        operations.push(sym);
      } else if (getPrior(sym) <= getPrior(operations.top())) {
        while (!operations.isEmpty() && operations.top() != '(' &&
               getPrior(sym) <= getPrior(operations.top())) {
          output += operations.pop();
          output += ' ';
        }
        operations.push(sym);
      }
    }
  }

  while (!operations.isEmpty()) {
    output += operations.pop();
    output += ' ';
  }
  output.pop_back();
  return output;
}

int eval(const std::string &pref) {
  TStack<int> stack;
  for (char sym : pref) {
    if (isDigit(sym)) {
      stack.push(sym - '0');
    } else if (isOperator(sym)) {
      int y = stack.pop();
      int x = stack.pop();
      int res = calc(sym, x, y);
      stack.push(res);
    }
  }
  return stack.pop();
}
