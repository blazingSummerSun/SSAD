#include <iostream>

using namespace std;

int main()
{
    int n; // Input data
    int m; // Input data
    int numbers[30];
    cin >> n >> m;
    int *array_ptr = numbers; // Pointer to the first element in the numbers-array;
    for (int i = 0; i < n; i++) {
        int current;
        cin >> current;
        *(array_ptr + i) = current; // Assigning i-th element from the array to the current input
    }
    int results[m]; // Array to store elements received after "sum" command
    int *result_ptr = results; // Pointer to the first element from results-array.
    int size = 0; // Amount of elements in the results-array.
    for (int i = 0; i < m; i++) {
        string command;
        int first; // First input number
        int second; // Second input number
        cin >> command >> first >> second;
        if (command == "sum") { // If current command is "sum" - sum all element from i-th to j-th element.
            int sum = 0;
            for (int j = first; j <= second; j++) {
                sum += *(array_ptr + j); // the same as sum += array_ptr[j].
            }
            *(result_ptr + size) = sum; // the same as result_ptr[size] = sum, e.g. store the sum in the answer array
            size++; // Increment amount of elements in the results-array
        }
        else {
            *(array_ptr+first) = second; // If command is "set" - array[first] = second
        }
    }
    for(int i = 0; i < size; i++){
        cout << *(result_ptr+i) << "\n"; // Output elements received by "sum" command
    }
    for(int i = 0; i < n; i++){
        cout << *(array_ptr+i) << " "; // Output changed array
    }
    return 0;
}