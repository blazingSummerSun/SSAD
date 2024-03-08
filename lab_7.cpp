#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class CircularBuffer
{
public:
    CircularBuffer(size_t capacity)
        : capacity(capacity), head(0), tail(0)
    {}
    void push(const T &value)
    {
        storage[tail] = value;
        tail = (tail + 1) % capacity;
    }
    T pop()
    {
        if (storage.size() == 0) {
            throw underflow_error("Circular Buffer is empty");
        }
        T element = storage[head];
        head = (head + 1) % capacity;
        return element;
    }
    bool empty()
    {
        return head == tail;
    }
    int size()
    {
        return (tail - head + capacity) % capacity;
    }
private:
    vector<T> storage;
    size_t capacity;
    size_t head;
    size_t tail;
    friend class CircularBufferIterator;
    class CircularBufferIterator
    {
    public:
        CircularBufferIterator(const CircularBuffer<T> &buffer, bool is_end = false)
            : storage(buffer), index(is_end ? buffer.tail : buffer.head)
        {}
        T& operator*() const {
            return storage.storage[index];
        }

        CircularBufferIterator& operator++() {
            index = (index + 1) % storage.capacity;
            return *this;
        }

        CircularBufferIterator operator++(int) {
            CircularBufferIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator!=(const CircularBufferIterator& other) const {
            return index != other.index % storage.capacity;
        }
    public:
        const CircularBuffer<T> &storage;
        size_t index;
    };
public :
    CircularBufferIterator begin() {
        return CircularBufferIterator(*this);
    }
    CircularBufferIterator end() {
        return CircularBufferIterator(*this, true);
    }
};

int main()
{
    CircularBuffer<int> circularBuffer(5);
    circularBuffer.push(10);
    circularBuffer.push(28);
    circularBuffer.push(33);

    for (int element : circularBuffer) {
        cout << element << " ";
    }
    cout << "\n";

    circularBuffer.pop();
    circularBuffer.push(4);

    for (const int& element : circularBuffer) {
        cout << element << " ";
    }
    return 0;
}