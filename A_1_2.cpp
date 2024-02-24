#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class Complex
{
public:
    double real; // Real part of complex number
    double imaginary; // Imaginary part of comple number
    Complex(double real_part, double imaginary_part) // Constructor
    {
        real = real_part;
        imaginary = imaginary_part;
    }
    ~Complex() = default; // Destructor
    Complex operator+(Complex current) // Addition of complex numbers
    {
        return Complex(real + current.real, imaginary + current.imaginary);

    }
    Complex operator-(Complex current) // Subtraction of complex numbers
    {
        return Complex(real - current.real, imaginary - current.imaginary);
    }
    Complex operator*(Complex current) // Multiplication of complex numbers
    {
        return Complex(real * current.real - imaginary * current.imaginary,
                       real * current.imaginary + imaginary * current.real);
    }
    Complex operator/(Complex current) // Division of complex numbers
    {
        double denominator = current.real * current.real + current.imaginary * current.imaginary;
        return Complex((real * current.real + imaginary * current.imaginary) / denominator,
                       (imaginary * current.real - real * current.imaginary) / denominator);
    }
    bool operator=(Complex current) // Comparing of 2 complex numbers
    {
        return (real == current.real && imaginary == current.imaginary);
    }
};

int main()
{
    int n;
    cin >> n;
    vector<string> solutions; // Vector storing results after operations over complex numbers
    for (int i = 0; i < n; i++) {
        string ops;
        double real_first; // Real part of the first number
        double img_first; // Imaginary part of the first number
        double real_second; // Real part of the second number
        double img_second; // Imaginary part of the second number
        cin >> ops >> real_first >> img_first >> real_second >> img_second;
        Complex first(real_first, img_first); // Creating complex number instance
        Complex second(real_second, img_second); // Creating complex number instance
        if (ops == "+") { // If current operation is addition
            Complex answer = first + second;
            // Checking whether real part of the complex number has float part
            bool real_zeros = ((int) answer.real == answer.real);
            // Checking whether imaginary part of the complex number has float part
            bool img_zeros = ((int) answer.imaginary == answer.imaginary);
            // String storing result of a real part
            string real_answer = "";
            // String storing result of an imaginary part
            string img_answer = "";
            if (real_zeros) {
                // If a number's real part doesn't have float part -> just add .00 after int part.
                real_answer = to_string((int) answer.real) + ".00";
            }
            else {
                // Otherwise, round a number
                int real_rounded = (round(answer.real * 100));
                // Checking whether should we add a minus sign to the real part in the final string
                bool add_minus = false;
                if (answer.real < 0) {
                    add_minus = true;
                }
                int main_part = answer.real; // Casting double to int to achieve necessary form of output
                int float_part = real_rounded % 100;
                // If float part is negative, make it positive for more convenience
                if (float_part < 0) float_part *= -1;
                // If float part has only 1 digit, add one more zero to achieve necessary form of output
                if (to_string(float_part).length() == 1) {
                    real_answer = to_string(main_part) + "." + "0" + to_string(float_part);
                }
                    // If number is negative, append minus before the output string
                else if (add_minus) {
                    real_answer = "-" + to_string(main_part) + "." + to_string(float_part);
                }
                    // In other cases, just concatenate main and float parts.
                else {
                    real_answer = to_string(main_part) + "." + to_string(float_part);
                }

            }
            // If imaginary part doesn't have float part, append 2 zeros in the final string.
            if (img_zeros) {
                img_answer = to_string((int) answer.imaginary) + ".00i";
            }
            else {
                // Otherwise, round an imaginary part
                int img_rounded = (round(answer.imaginary * 100));
                // Do the same operations with imaginary part, as with a real part
                int main_part = answer.imaginary;
                int float_part = img_rounded % 100;
                if (float_part < 0) float_part *= -1;
                // If imaginary part has 1 digit in the float, append one more zero.
                if (to_string(float_part).length() == 1) {
                    img_answer = to_string(main_part) + "." + "0" + to_string(float_part) + "i";
                }
                    // In other cases, just concatenate integer and float part in the string.
                else {
                    img_answer = to_string(main_part) + "." + to_string(float_part) + "i";
                }
            }
            // If both parts are positive, append '+' sign between real and imaginary part
            if (answer.imaginary >= 0 || answer.imaginary >= -0.005) {
                solutions.push_back(real_answer + "+" + img_answer);
            }
                // Otherwise, there will be minus sign.
            else {
                solutions.push_back(real_answer + img_answer);
            }
        }
        // If current operation is '-'
        if (ops == "-") {
            Complex answer = first - second;
            // Checking whether real part of the complex number has float part
            bool real_zeros = ((int) answer.real == answer.real);
            // Checking whether imaginary part of the complex number has float part
            bool img_zeros = ((int) answer.imaginary == answer.imaginary);
            string real_answer = ""; // String storing a result of a real part
            string img_answer = ""; // String storing a result of an imaginary part
            if (real_zeros) {
                // If real part doesn't have float part, append '.00' to achieve correct output form
                real_answer = to_string((int) answer.real) + ".00";
            }
            else {
                // Otherwise, round a real part
                int real_rounded = (round(answer.real * 100));
                bool add_minus = false;
                // Checking, whether real part is negative
                if (answer.real < 0) {
                    add_minus = true;
                }
                int main_part = answer.real;
                int float_part = real_rounded % 100;
                // If float part is negative, make it positive for more convenience
                if (float_part < 0) float_part *= -1;
                if (to_string(float_part).length() == 1) {
                    // If real part has only 1 digit in the float part, append additional zero
                    real_answer = to_string(main_part) + "." + "0" + to_string(float_part);
                }
                else {
                    // In other cases, concatenate 2 part together
                    real_answer = to_string(main_part) + "." + to_string(float_part);
                }

            }
            if (img_zeros) {
                // Appending 2 zeros if imaginary part doesn't have float part
                img_answer = to_string((int) answer.imaginary) + ".00i";
            }
            else {
                // Otherwise, round an imaginary part
                int img_rounded = (round(answer.imaginary * 100));
                int main_part = answer.imaginary;
                // Do the same operations with an imaginary part, as with real part before
                int float_part = img_rounded % 100;
                if (float_part < 0) float_part *= -1;
                if (to_string(float_part).length() == 1) {
                    // If imag. part has exact 1 zero in float part, append 1 more zero for correct form
                    img_answer = to_string(main_part) + "." + "0" + to_string(float_part) + "i";
                }
                else {
                    // In other cases, concatenate integer and float part together
                    img_answer = to_string(main_part) + "." + to_string(float_part) + "i";
                }
            }
            // If imaginary part is positive, append '+' sign between real and img. parts
            if (answer.imaginary >= 0 || answer.imaginary >= -0.005) {
                solutions.push_back(real_answer + "+" + img_answer);
            }
                // Otherwise, there will be minus sign
            else {
                solutions.push_back(real_answer + img_answer);
            }
        }
        // If current operation is multiplying
        if (ops == "*") {
            Complex answer = first * second;
            // Checking whether real part of the complex number has float part
            bool real_zeros = ((int) answer.real == answer.real);
            // Checking whether imag. part of the complex number has float part
            bool img_zeros = ((int) answer.imaginary == answer.imaginary);
            string real_answer = ""; // String storing a result of a real part
            string img_answer = ""; // String storing a result of an imag. part
            if (real_zeros) {
                // If real part doesn't have float part, append '.00' to achieve correct output form
                real_answer = to_string((int) answer.real) + ".00";
            }
            else {
                // Otherwise, round a real part
                int real_rounded = (round(answer.real * 100));
                // Checking, whether real part is negative
                bool main_minus = answer.real < 0;
                int main_part = answer.real;
                int float_part = real_rounded % 100;
                // If float part is negative, make it positive for more convenience
                if (float_part < 0) float_part *= -1;
                if (to_string(float_part).length() == 1) {
                    // If real part has only 1 digit in the float part, append additional zero
                    real_answer = to_string(main_part) + "." + "0" + to_string(float_part);
                }
                else {
                    // If an integer part was negative, add a minus sign before the string
                    if (main_minus && main_part == 0) {
                        real_answer = "-" + to_string(main_part) + "." + to_string(float_part);
                    }
                        // In other cases, concatenate 2 part together
                    else { real_answer = to_string(main_part) + "." + to_string(float_part); }
                }
            }
            if (img_zeros) {
                // Appending 2 zeros if imaginary part doesn't have float part
                img_answer = to_string((int) answer.imaginary) + ".00i";
            }
            else {
                // Otherwise, round an imaginary part
                int img_rounded = (round(answer.imaginary * 100));
                bool add_minus = false;
                if (answer.imaginary < 0.005) {
                    add_minus = true;
                }
                // Checking, whether imag. part is negative
                bool img_minus = answer.imaginary < 0;
                int main_part = answer.imaginary;
                // Do the same operations with an imaginary part, as with real part before
                int float_part = img_rounded % 100;
                if (float_part < 0) float_part *= -1;
                if (to_string(float_part).length() == 1) {
                    // If imag. part has exact 1 zero in float part, append 1 more zero for correct form
                    img_answer = to_string(main_part) + "." + "0" + to_string(float_part) + "i";
                }
                else {
                    // If an integer part was negative, add a minus sign before the string
                    if (img_minus && main_part == 0) {
                        img_answer = "-" + to_string(main_part) + "." + to_string(float_part) + "i";
                    }
                    // In other cases, concatenate integer and float part together
                    else { img_answer = to_string(main_part) + "." + to_string(float_part) + "i"; }
                }
            }
            // If imag. part is positive, append 'plus' sign between real and imag. parts
            if (answer.imaginary >= 0 || answer.imaginary >= -0.005) {
                solutions.push_back(real_answer + "+" + img_answer);
            }
            // Otherwise, there will be a minus sign.
            else {
                solutions.push_back(real_answer + img_answer);
            }
        }
        // If current operation is division.
        if (ops == "/") {
            Complex answer = first / second;
            // Checking whether real part of the complex number has float part
            bool real_zeros = ((int) answer.real == answer.real);
            // Checking whether imag. part of the complex number has float part
            bool img_zeros = ((int) answer.imaginary == answer.imaginary);
            string real_answer = ""; // String storing a result of a real part
            string img_answer = ""; // String storing a result of an imag. part
            if (real_zeros) {
                // If real part doesn't have float part, append '.00' to achieve correct output form
                real_answer = to_string((int) answer.real) + ".00";
            }
            else {
                // Otherwise, round a real part
                int real_rounded = (round(answer.real * 100));
                bool add_minus = false;
                // Checking, whether real part is negative
                if (answer.real < 0) {
                    add_minus = true;
                }
                bool main_minus = answer.real < 0;
                int main_part = answer.real;
                int float_part = real_rounded % 100;
                // If float part is negative, make it positive for more convenience
                if (float_part < 0) float_part *= -1;
                if (to_string(float_part).length() == 1) {
                    if (add_minus && main_part == 0) {
                        // If a real part has only 1 digit in the float part, and int part is zero, append minus sign, and one more zero
                        real_answer = "-" + to_string(main_part) + "." + "0" + to_string(float_part);
                    }
                    else {
                        // Otherwise, just append additional zero
                        real_answer = to_string(main_part) + "." + "0" + to_string(float_part);
                    }
                }
                else {
                    // If an integer part was negative, add a minus sign before the string
                    if (add_minus && main_part == 0) {
                        real_answer = "-" + to_string(main_part) + "." + to_string(float_part);
                    }
                    else {
                        // In other cases, concatenate 2 part together
                        real_answer = to_string(main_part) + "." + to_string(float_part);
                    }
                }
            }
            if (img_zeros) {
                // Appending 2 zeros if imaginary part doesn't have float part
                img_answer = to_string((int) answer.imaginary) + ".00i";
            }
            else {
                // Otherwise, round an imaginary part
                int img_rounded = (round(answer.imaginary * 100));
                bool add_minus = false;
                // Checking, whether imag. part is negative
                if (answer.imaginary < 0) {
                    add_minus = true;
                }
                int main_part = answer.imaginary;
                // Do the same operations with an imaginary part, as with real part before
                int float_part = img_rounded % 100;
                if (float_part < 0) float_part *= -1;
                if (to_string(float_part).length() == 1) {
                    if (add_minus && main_part == 0) {
                        // If a real part has only 1 digit in the float part, and int part is zero, append minus sign, and one more zero
                        img_answer = "-" + to_string(main_part) + "." + "0" + to_string(float_part) + "i";
                    }
                    else {
                        // Otherwise, just append additional zero
                        img_answer = to_string(main_part) + "." + "0" + to_string(float_part) + "i";
                    }
                }
                else {
                    // If an integer part was negative, add a minus sign before the string
                    if (add_minus && main_part == 0) {
                        img_answer = "-" + to_string(main_part) + "." + to_string(float_part) + "i";
                    }
                        // In other cases, concatenate 2 part together
                    else { img_answer = to_string(main_part) + "." + to_string(float_part) + "i"; }
                }
            }
            // If imag. part is positive, append '+' sign between real and imag. parts
            if (answer.imaginary >= 0 || answer.imaginary >= -0.005) {
                solutions.push_back(real_answer + "+" + img_answer);
            }
            else {
                // Otherwise, there will be minus sign.
                solutions.push_back(real_answer + img_answer);
            }
        }
        // If current sign is comparing sign.
        if (ops == "=") {
            // If numbers are equal, append true in the answer vector.
            if (first = second) {
                solutions.push_back("true");
            }
            // Otherwise, append false
            else {
                solutions.push_back("false");
            }
        }
    }
    // Iterating through answer vector and output results
    for (int i = 0; i < n; i++) {
        cout << solutions[i];
        if (i != n - 1) {
            cout << "\n";
        }
    }
    return 0;
}