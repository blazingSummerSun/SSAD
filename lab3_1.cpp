#include <iostream>
#include <vector>

using namespace std;

class Animal
{
protected:
    string name;
    int age;
public :
    virtual string makeSound() = 0;
};

class LandAnimal: public virtual Animal
{
public:
    virtual string sunbathe() = 0;
    string makeSound() override
    {
        return "Top-top";
    }
};
class WaterAnimal: public virtual Animal
{
public:
    virtual string breath() = 0;
    string makeSound() override
    {
        return "Guuuurgle";
    }
};

class Lion: public LandAnimal
{
public:
    Lion(int age, string name)
    {
        this->age = age;
        this->name = name;
    }
    string sunbathe() override
    {
        return "Aaaaaaaa-Hhhhhhhhhhhh-Rrrrrrrr";
    }
};
class Dolphin: public WaterAnimal
{
public:
    Dolphin(int age, string name)
    {
        this->age = age;
        this->name = name;
    }
    string breath() override
    {
        return "Eeeee-Eeee-Eeee";
    }

};
class Frog: public LandAnimal, public WaterAnimal
{
public:
    Frog(int age, string name)
    {
        this->age = age;
        this->name = name;
    }
    string makeSound() override
    {
        return "Croooooooaaaaaaaaak";
    }
    string breath() override
    {
        return "The frog is breathing";
    }
    string sunbathe() override
    {
        return "The frog is chilling during sunbathing";
    }
};

int main()
{
    vector<Animal *> zoo;
    Frog frog(12, "Clava");
    Dolphin dolphin(33, "Bone");
    Lion lion(24, "Gone");
    zoo.push_back(&frog);
    zoo.push_back(&dolphin);
    zoo.push_back(&lion);
    for ( auto &animal: zoo) {
        animal->makeSound();
        if (auto creature = dynamic_cast<Dolphin *>(animal)) {
            cout << creature->makeSound() << endl;
            cout << creature->breath() << endl;
            cout << "\n";
        }
        if (auto creature = dynamic_cast<Frog *>(animal)) {
            cout << creature->makeSound() << endl;
            cout << creature->breath() << endl;
            cout << creature->sunbathe() << endl;
            cout << "\n";
        }
        if (auto creature = dynamic_cast<Lion *>(animal)) {
            cout << creature->makeSound() << endl;
            cout << creature->sunbathe() << endl;
            cout << "\n";
        }
    }
    return 0;
}