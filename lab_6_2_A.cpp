#include <iostream>
#include <unordered_map>

using namespace std;


template<typename K, typename V>
class Dictionary{
public:
    Dictionary(){};
    void put(const K& key, const V& value){
        storage[key] = value;
    }
    V get(const K& key){
        auto to_find = storage.find(key);
        return to_find != storage.end() ? to_find->second : V();
    }
    void remove(const K& key){
        storage.erase(key);
    }
    size_t size(){
        return storage.size();
    }

private:
    unordered_map<K, V> storage;
};

int main(){
    Dictionary<int, string> dictionary;
    dictionary.put(1, "pills");
    dictionary.put(2, "borrow");
    cout << dictionary.size() << "\n";
    cout << dictionary.get(2) << "\n";
    dictionary.remove(2);
    cout << dictionary.size() << "\n";
    return 0;
}