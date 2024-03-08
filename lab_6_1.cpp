#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

template<typename T>
class Wrapper
{
public:
    Wrapper(const T& value)
        : value(value)
    {}
    T getValue()
    {
        return value;
    }
private:
    T value;
};

template<>
class Wrapper<char*>
{
public:
    Wrapper(const char* value) : value(value) {}
    size_t getValue(){
        return strlen(value);
    }
private:
    const char* value;
};


int main()
{
    Wrapper<int> int_check(42);
    cout << int_check.getValue() << "\n";

    Wrapper<char*> string_check = "Goodbye, world";
    cout << string_check.getValue();
    return 0;
}