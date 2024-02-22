#include <iostream>
#include <vector>

/**
 * REPORT:
 * GenericStack implementation:
 * All elements store in the vector. push() to add an element at the end of the vector
 * pop() delete last element in the vector, peek() returns last element from the vector
 * isEmpty() checking if vector is empty, size() returns amount of element in the vector.
 *
 * StringStack implementation:
 * push() add only non empty strings, concatTopTwo concatenate 2 last string into the 1.
 *
 * I don't have any problems during the implementation because I've done the same work on DSA course 3 weeks ago.
 * */

using namespace std;

template<typename T>
class GenericStack
{
public:
    const int capacity = 16;
    vector<T> elems;
    GenericStack()
    {
        elems.reserve(capacity);
    }
    void push(T current)
    {
        elems.push_back(current);
    }
    T pop()
    {
        if (elems.empty()) {
            throw runtime_error("Stack is empty!");
        }
        T top = elems.back();
        elems.pop_back();
        return top;
    }
    T peek()
    {
        if (elems.empty()) {
            throw runtime_error("Stack is empty!");
        }
        return elems.back();
    }
    bool isEmpty()
    {
        return elems.empty();
    }
    int size(){
        return elems.size();
    }
};

class StringStack: public GenericStack<string>
{
public:
//    GenericStack<string> string_stack;
    void push(string currentString)
    {
        if(!currentString.empty()){
            elems.push_back(currentString);
        }
        else{
            throw runtime_error("String is empty!");
        }
    }
    string concatTopTwo(){
        if(elems.size() < 2){
            throw runtime_error("Stack's size less than 2");
        }
        else {
            string first = elems[elems.size()-1];
            string second = elems[elems.size()-2];
            elems.pop_back();
            elems.pop_back();
            elems.push_back(first+second);
            return elems.back();
        }
    }
};

int main()
{
    StringStack stringStack;
    StringStack test;
    stringStack.push("World");
    cout << stringStack.peek() << "\n";

    stringStack.push("Hello");
    cout << stringStack.peek() << "\n";

    cout << stringStack.concatTopTwo() << "\n";
    cout << stringStack.peek() << "\n";
    stringStack.pop();
    cout << stringStack.size() << "\n";
    return 0;
}
