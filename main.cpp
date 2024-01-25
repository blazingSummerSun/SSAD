#include <iostream>

using namespace std;

/**
 * Task 2.
 * Write your own function for swapping values of two integers using:
 * a) passing by pointer
 * b) passing by reference
 * */

void swap_via_pointers(int* a, int*b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_via_refs(int&a, int&b){
    int temp = a;
    a = b;
    b = temp;
}
int main() {
    int first;
    int second;

    cin >> first;
    cin >> second;

    swap_via_pointers(&first, &second);
    cout << first << endl << second << endl;

    swap_via_refs(first, second);
    cout << first << endl << second << endl;
    return 0;
}
