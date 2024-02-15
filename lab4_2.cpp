#include<iostream>

using namespace std;

class Shape
{
public:
    virtual double perimeter() = 0;
    virtual double area() = 0;
};
class Rectangle: public Shape
{
private:
    double width;
    double height;
public:
    Rectangle(double width, double height)
    {
        this->width = width;
        this->height = height;
    }
    double area()
    {
        return width * height;
    }
    double perimeter()
    {
        return 2 * (width + height);
    }
};
class Circle: public Shape
{
private:
    double radius;
public:
    Circle(double radius)
    {
        this->radius = radius;
    }
    double area() override
    {
        return 3.14 * radius * radius;
    }
    double perimeter() override
    {
        return 2 * 3.14 * radius;
    }
};

int main()
{
    const Rectangle rect(5.0, 3.0);
    Circle circle(4.0);
    // Demonstrate static casting [1]
    // Converting Rectangle to Shape
    const Shape& shapeFromRect = static_cast<const Shape&>(rect);

    // Converting Circle to Shape
    const Shape& shapeFromCircle = static_cast<const Shape&>(circle);

    // Create a const pointer to Rectangle and initialize it with the Shape pointer
    const Rectangle* rectPtr = dynamic_cast<const Rectangle*>(&shapeFromRect);

    // Check if the type of shape dynamically changed into a pointer to Circle
    if (dynamic_cast<const Circle*>(&shapeFromRect)) {
        cout << "shape is a Circle" << endl;
    } else {
        cout << "shape is not a Circle" << endl;
    }

    // Check if the type of shape dynamically changed into a pointer to Circle
    if (dynamic_cast<const Circle*>(&shapeFromCircle)) {
        cout << "shape is a Circle" << endl;
    } else {
        cout << "shape is not a Circle" << endl;
    }

    // Demonstrate const casting [3]
    Rectangle* mutRectPtr = const_cast<Rectangle*>(rectPtr);
    cout << mutRectPtr->area();

    int intValue = 42;
    // Demonstrate reinterpret casting [4]
    double doubleValue = reinterpret_cast<double&>(intValue);
    cout << "intValue: " << intValue << endl;
    cout << "doubleValue: " << doubleValue << endl;

    return 0;
}