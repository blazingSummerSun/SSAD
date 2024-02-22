#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class GenericStack
{
public:
    const int capacity = 16;
    T stack[];
    GenericStack(int capacity) {
        stack[capacity];
    }
    void push(T item)
    {
        if(stack.size == capacity){
            T new_stack[capacity*2];
        }
        stack.push_back(item);
    }
    T pop()
    {
        if (stack.empty()) {
            throw runtime_error("Stack is empty!");
        }
        else {
            T to_return = stack[stack.size() - 1];
            stack.pop_back();
            return to_return;
        }
    }
    T peek()
    {
        if (stack.empty()) {
            throw runtime_error("Stack is empty!");
        }
        else {
            return stack[stack.size() - 1];
        }
    }
};