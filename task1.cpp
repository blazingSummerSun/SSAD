#include <iostream>

using namespace std;

/**
 * Task 1.
 * Write a program that accepts time period given in seconds and returns it in the following format:
 * hours : minutes : seconds
 * */
int main() {
    int seconds;
    cin >> seconds;
    int minutes = seconds / 60;
    int hours = minutes / 60;
    cout << hours << ":" << minutes%60 << ":" << seconds%60;
    return 0;
}