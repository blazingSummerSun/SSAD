#include <iostream>
using namespace std;

/**
* Write a program that accepts number of elements (N) of the array of integers and then N elements.
* After user inserts the array, your program should remove all duplicates from it.
* You should solve this task using:
* a) arrays
* b) vectors
* */


int main() {
    int n;
    cin >> n;
    int numbers[n];
    for(int i = 0; i < n; i++){
        int current;
        cin >> current;
        numbers[i] = current;
    }

    // With arrays:
    int answer[n];
    int amount_of_numbers = 0;
    for(int i = 0; i< n; i++){
        bool flag = true;
        for(int j = 0; j < n; j++){
            int current_i = numbers[i];
            int current_j = answer[j];
            if(current_i == current_j){
                flag = false;
            }
        }
        if(flag){
            answer[amount_of_numbers] = numbers[i];
            amount_of_numbers++;
        }
    }
    for(int i = 0; i < amount_of_numbers; i++){
        cout << answer[i] << " ";
    }

    // With vectors:
//    vector<int>nums;
//    for(int i = 0; i < n; i++){
//        int current_num = numbers[i];
//        nums.push_back(current_num);
//    }
//    vector<int>vec_answer;
//    int vector_numbers = 0;
//    for(int i = 0; i< n; i++){
//        bool flag = true;
//        for(int j = 0; j < vec_answer.size(); j++){
//            int current_i = nums[i];
//            int current_j = vec_answer[j];
//            if(current_i == current_j){
//                flag = false;
//            }
//        }
//        if(flag){
//            vec_answer.push_back(nums[i]);
//            vector_numbers++;
//        }
//    }
//    for(int i = 0; i < vector_numbers; i++){
//        cout << vec_answer[i] << " ";
//    }
    return 0;
}