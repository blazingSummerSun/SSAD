#include <iostream>
#include <unordered_map>

using namespace std;


template<typename K, typename V>
class Dictionary
{
public:
    Dictionary()
    {};
    void put(const K &key, const V &value)
    {
        storage[key] = value;
    }
    V get(const K &key)
    {
        auto to_find = storage.find(key);
        return to_find != storage.end() ? to_find->second : V();
    }
    void remove(const K &key)
    {
        storage.erase(key);
    }
    size_t size()
    {
        return storage.size();
    }

private:
    unordered_map<K, V> storage;
};

template<typename K>
class Dictionary<K, int>
{
public:
    Dictionary()
    {}
    void put(const K &key, const int &value)
    {
        storage[key] = value;
    }

    // Get the absolute value for a key
    int get(const K &key) const
    {
        auto it = storage.find(key);
        return it != storage.end() ? abs(it->second) : -1;
    }

    // Remove a key-value pair
    void remove(const K &key)
    {
        storage.erase(key);
    }

    // Get the sum of all values (specialized for int)
    int size() const
    {
        int sum = 0;
        for (auto pair = storage.begin(); pair != storage.end(); ++pair) {
            sum += pair->second;
        }
        return sum;
    }

private:
    unordered_map<K, int> storage;
};

int main()
{
    Dictionary<string, int> dictionary;
    dictionary.put("bless", 99);
    dictionary.put("curse", 123);
    cout << dictionary.size() << "\n";
    dictionary.put("edge", -12);
    cout << dictionary.get("edge") << "\n";
    cout << dictionary.size();
    return 0;
}