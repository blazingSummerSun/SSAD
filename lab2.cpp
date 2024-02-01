#include <iostream>
using namespace std;

/**
 * Task:
 * Write a program that contains a class Box.
 * - Box should have the length, width, and height as member variables.
 * The variables should be of type unsigned int.
 * - Box should have three constructors: default, copy, conversion.
 * - Box should have the assignment operator
 * Add and implement the following member functions to the class Box:
 * unsigned getVolume();
 * void scale(unsigned scaleValue);
 * bool isBigger(unknown other);
 * bool isSmaller(unknown other);
 * Add the following operators to the class Box: { *, ==}
 * Add another class Cube. Add an operator to convert an object of type Cube to object of type Box.
 * */
int max(unsigned int a, unsigned int b)
{
    if (a > b) {
        return a;
    }
    return b;
}
static int min(int a, int b)
{
    if (a < b) {
        return a;
    }
    return b;
}

class Box
{
private:
    unsigned int length;
    unsigned int width;
    unsigned int height;
public:
    Box()
        : length(9), width(6), height(3)
    {}
    Box(unsigned int size)
        : height(size), width(size), length(size)
    {}
    Box(Box &other)
    { this->length = other.length, this->width = other.width, this->height = other.height; }

    void operator=(Box &other)
    {
        length = other.length;
        width = other.width;
        height = other.height;
    }
    void operator*(unsigned int scaleValue)
    {
        length = length * scaleValue;
        width = width * scaleValue;
        height = height * scaleValue;
    }
    bool operator==(Box &other)
    {
        unsigned int minOther = other.length;
        unsigned int midOther = other.width;
        unsigned int topOther = other.height;
        unsigned int sumOther = minOther + midOther + topOther;
        unsigned int sumCurrent = length + width + height;
        return (sumCurrent == sumOther && (length == minOther || length == midOther || length == topOther) &&
            (width == minOther || width == midOther || width == topOther));
    }
    unsigned int getVolume()
    {
        return length * width * height;
    }
    void scale(unsigned scaleValue)
    {
        length = length * scaleValue;
        width = width * scaleValue;
        height = height * scaleValue;
    }
    bool isBigger(Box other)
    {
        return getVolume() > other.getVolume();
    }
    bool isSmaller(Box other)
    {
        return getVolume() < other.getVolume();
    }

};

class Cube
{
private:
    unsigned int side;
public:
    Cube(unsigned int size)
        : side(size)
    {}
    operator Box() const
    {
        return Box(side);
    }
};

int main()
{
    Box first;
    Box second;
    Cube third(11);

    cout << "Comparing the first box with the second: " << first.operator==(second) << endl;
    cout << "Volume of the first box is : " << first.getVolume() << endl;
    first.scale(3);
    cout << "Volume of the first box is : " << first.getVolume() << endl;
    Box sample = third; // Convert a Cube to the Box;

    cout << "Volume of the converted Cube is: " << sample.getVolume() << endl;
    cout << "Comparing the first box with converted Cube : " << first.isBigger(sample) << endl;
    return 0;
}