// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#define SIZE 100

template <typename T> class TStack {
 private:
  T stack[SIZE];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  int push(T value) {
    if (topIndex >= SIZE - 1) {
      throw std::runtime_error("Stack overflow!");
    }
    stack[++topIndex] = value;
    return 0;
  }

  T pop() {
    if (isEmpty()) {
      throw std::runtime_error("Stack is empty!!");
    }
    return stack[topIndex--];
  }

  T top() const {
    if (isEmpty()) {
      throw std::runtime_error("Stack is empty!");
    }
    return stack[topIndex];
  }

  bool isEmpty() const { return topIndex == -1; }

  bool isFull() const { return topIndex == SIZE - 1; }

  int getSize() const { return topIndex + 1; }
};

#endif // INCLUDE_TSTACK_H_
