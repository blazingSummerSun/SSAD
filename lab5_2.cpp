#include <iostream>
#include <memory>
using namespace std;

/**
 * REPORT:
 * unique_ptr implements the semantics of exceptional ownership: At any execution point,
 * only one pointer “owns” the object pointed.
 *
 * shared_ptr implements the semantics of cooperative ownership: several pointers can share the same object,
 * and the object is automatically destroyed when there is no (more) pointers to it
 *
 * weak_ptr is a complementary notion to unique_ptr:
 * No dereferencing operator, no check for “null"
 *
 * In general, smart pointers could prevent memory leakage with automatic memory management that makes programmers'
 * lives easier
 * */


class Box
{
public:
    int value;
    explicit Box(int v)
        : value(v)
    {}
    ~Box() = default;
};

int create_unique(Box &value)
{
    unique_ptr<Box> ptr(new Box(value));
    unique_ptr<Box> ptr_transfer;
    ptr_transfer = move(ptr);
    return ptr_transfer->value;
}

void create_shared_boxes(){
    auto box1 = make_shared<Box>(30);
    shared_ptr<Box> box2 = make_shared<Box>(20);
    cout << "Amount of pointers to the first box: " << box1.use_count() << "\n";
    cout << "Amount of pointers to the second box: " << box2.use_count() << "\n";
    box1 = box2;
    cout << "Amount of pointers to the first box after changes: " << box1.use_count() << "\n";
}

void demonstrate_weak_ptr(){
    auto sharedBox = std::make_shared<Box>(30);
    weak_ptr<Box> weakBox = sharedBox;

    shared_ptr<Box> from_weak = weakBox.lock();
    if(from_weak){
        cout << from_weak->value << "\n";
    }
    else cout << "Impossible to get access";
}

int main()
{
    Box test(6);
    cout << create_unique(test) << "\n";
    create_shared_boxes();
    demonstrate_weak_ptr();
    return 0;
}
