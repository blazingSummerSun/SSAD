#include <iostream>
#include <vector>

using namespace std;

class DataStructure
{
public :
    // Virtual functions DataStructure's class
    virtual void insert(int value) = 0;
    virtual void remove() = 0;
    virtual bool search(int x) const = 0;
    // Destructor
    virtual ~DataStructure()
    {};
};

class SequentialDataStructure: DataStructure
{
public:
    // Virtual functions SequentialDataStructure's class
    virtual void pushBack(int value) = 0;
    virtual void pushFront(int x) = 0;
    virtual void popBack() = 0;
    virtual void popFront() = 0;
    // Destructor
    virtual ~SequentialDataStructure()
    {};

};

class DynamicDataStructure: DataStructure
{
public:
    // Virtual functions DynamicDataStructure's class
    virtual void resize(int new_size) = 0;
    virtual void clear() = 0;
    // Destructor
    virtual ~DynamicDataStructure()
    {};
};

class List: SequentialDataStructure, DynamicDataStructure
{
public:
    // Vector to store elements
    vector<int> storage;
    // Insert an element in the ent of a storage vector.
    void insert(int value) override
    {
        storage.push_back(value);
    }
    // Remove an element from the end of the storage vector
    void remove() override
    {
        if (!storage.empty()) {
            storage.pop_back();
        }
    }
    // Searching for the specific element in the storage vector
    bool search(int value) const override
    {
        for (int i = 0; i < storage.size(); i++) {
            if (storage[i] == value) {
                return true;
            }
        }
        return false;
    }
    // Push an element at the end of the storage vector
    void pushBack(int value) override
    {
        storage.push_back(value);
    }
    // Push an element in the start of the storage vector
    void pushFront(int value) override
    {
        vector<int> replace;
        replace.push_back(value);
        for (int i = 0; i < storage.size(); i++) {
            replace.push_back(storage[i]);
        }
        storage = replace;
    }
    // Pop an element from the end of the storage vector
    void popBack() override
    {
        if (!storage.empty()) {
            storage.pop_back();
        }
    }
    // Pop an element from the start of the storage vector
    void popFront() override
    {
        if (!storage.empty()) {
            storage.erase(storage.begin());
        }
    }
    // Resize the storage vector
    void resize(int new_size) override
    {
        storage.resize(new_size);
    }
    // Clear the storage vector
    void clear() override
    {
        storage.clear();
    }
    // Size getter
    int getSize() const
    {
        return storage.size();
    }
    // Value getter by index
    int getValue(int index)
    {
        return storage[index];
    }

};

int main()
{
    int n;
    cin >> n;
    List answer; // List to store input elements
    List results; // List to store 'search' calls results
    for (int i = 0; i < n; i++) {
        string command;
        int value;
        cin >> command;
        // If current command is 'remove' - call the corresponding function
        if (command == "remove") {
            answer.remove();
        }
            // If current command is 'insert' - call the corresponding function
        else if (command == "insert") {
            cin >> value;
            answer.insert(value);
        }
            // If current command is 'search' - call the corresponding function
        else if (command == "search") {
            cin >> value;
            // Appending in the results list corresponding answer
            results.pushBack(answer.search(value));
        }

    }
    // Iterating through results list and output corresponding answer
    for (int i = 0; i < results.getSize(); i++) {
        if (results.getValue(i) == 0) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
        }
    }
    // Iterating through main list with all elements
    for (int i = 0; i < answer.getSize(); i++) {
        cout << answer.getValue(i) << " ";
    }

    return 0;
}