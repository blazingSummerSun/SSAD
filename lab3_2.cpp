#include <iostream>
#include <vector>

using namespace std;

template<typename T, typename F>
vector<T> myMap(vector<T> &inputVector, F callback)
{
    vector<T> answer;
    for (T &element: inputVector) {
        answer.push_back(callback(element));
    }
    return answer;
}

template<typename T, typename F>
vector<T> myFilter(vector<T> &inputVector, F callback)
{
    vector<T> answer;
    for (T element: inputVector) {
        if (callback(element)) {
            answer.push_back(element);
        }
    }
    return answer;
}

int main()
{
    vector<int> example = {2, 5, 6, 8, 13};
    auto funcSample1 = [](int x) // Squared all integers in the vector
    { return x * x; };
    auto mapSample1 = myMap(example, funcSample1);
    cout << "First map test:" << "\n";
    for (int num: mapSample1) {
        cout << "Current num is: " << num << "\n";
    }

    auto funcSample2 = [](int x)// Multiply by 5 all integers in the vector
    { return x * 5; };
    auto mapSample2 = myMap(example, funcSample2);
    cout << "\n" << "Second map test:" << "\n";
    for (int num: mapSample2) {
        cout << "Current num is: " << num << "\n";
    }

    auto funcSample3 = [](int x)// Delete all even integers from the vector
    { return x % 2 != 0; };
    auto filterSample1 = myFilter(example, funcSample3);
    cout << "\n" << "First filter test:" << "\n";
    for (int num: filterSample1) {
        cout << "Current num is: " << num << "\n";
    }

    auto funcSample4 = [](int x)// Delete all integers less than 6 from the vector
    { return x > 5; };
    auto filterSample2 = myFilter(example, funcSample4);
    cout << "\n" << "Second filter test:" << "\n";
    for (int num: filterSample2) {
        cout << "Current num is: " << num << "\n";
    }

    return 0;
}
