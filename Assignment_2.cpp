#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <type_traits>
#include <fstream>
#include <algorithm>


using namespace std;

class Character
{
private:
    int HP;
    string name;
    string type;

public:
    Character(int HP, string &name, string &type)
        : HP(HP), name(name), type(type)
    {};
    Character()
    {};
    virtual ~Character() = default;
    virtual string getName()
    {
        return name;
    };
    string getType()
    {
        return type;
    }
    virtual int getHP() const
    {
        return HP;
    }
    virtual void setHP(int value)
    {
        HP = value;
    }


private:
    virtual void takeDamage(int damage) = 0;
    virtual void heal(int healValue) = 0;

};
class PhysicalItem
{
protected:
    string name;

public:
    explicit PhysicalItem(string &name)
        : name(name)
    {};
    ~PhysicalItem() = default;
    virtual string &getName()
    {
        return name;
    };
};

class Weapon: public PhysicalItem
{
private:
    int damage;
public:
    Weapon(string &weaponName, int damage)
        : PhysicalItem(weaponName), damage(damage)
    {};
    ~Weapon() = default;
    [[nodiscard]] int getDamage() const
    {
        return damage;
    }
};

class Potion: public PhysicalItem
{
private:
    int healValue;
public:
    Potion(int heal, string &pName)
        : PhysicalItem(pName), healValue(heal)
    {};
    [[nodiscard]] int getHealValue() const
    {
        return healValue;
    }
};

class Spell: public PhysicalItem
{
public:
    explicit Spell(string &spellName)
        : PhysicalItem(spellName)
    {};
};

template<typename T>
class Container
{
private:
    vector<T> elements;
    int maxCapacity;
public:
    explicit Container(int maxElements)
        : maxCapacity(maxElements)
    {};
    ~Container() = default;
};

// Concept for objects derived from PhysicalItem
template<typename T>
concept DerivedFromPhysicalItem = is_base_of<PhysicalItem, T>::value;

template<DerivedFromPhysicalItem T>
class Container<T>
{
private:
    map<string, T> elements;
    int maxCapacity;
public:
    explicit Container(int maxCapacity)
        : maxCapacity(maxCapacity)
    {};
    void addItem(T &newItem, string &name)
    {
        elements.insert({name, newItem});
    }
    T getItem(const string &item)
    {
        if (find(item)) {
            return elements.at(item);
        }
    }
    bool find(const string &itemName)
    {
        return elements.contains(itemName);
    }
    void removeItem(const string &itemName)
    {
        if (find(itemName)) {
            elements.erase(itemName);
        }
    }
    int size()
    {
        return elements.size();
    }
    map<string, T> getContainer()
    {
        return elements;
    }

};

class WeaponUser: virtual public Character
{
public:
    virtual void attack(Character &target, const string &weaponName) = 0;
};

class PotionUser: virtual public Character
{
public:
    virtual void drink(Character &target, const string &pName) = 0;
};

class SpellUser: virtual public Character
{
protected:
public:
    virtual void cast(Character &target, const string &spellName) = 0;

};

class Fighter: public WeaponUser, PotionUser
{
private:
    string name;
    int HP;
    Container<Weapon> arsenal;
    Container<Potion> medicalBag;
    string type;

public:
    Fighter(string &name, int HP, string &type)
        : name(name), HP(HP), type(type), arsenal(Container<Weapon>(3)), medicalBag(Container<Potion>(5))
    {};
    ~Fighter() = default;
    void attack(Character &target, const string &weaponName) override
    {
        Weapon gun = arsenal.getItem(weaponName);
        target.setHP(target.getHP() - gun.getDamage());
    }
    void drink(Character &target, const string &pName) override
    {
        Potion clarity = medicalBag.getItem(pName);
        heal(clarity.getHealValue());
        medicalBag.removeItem(pName);
    }
    Container<Weapon> &getArsenal()
    {
        return arsenal;
    }
    Container<Potion> &getMedicalBag()
    {
        return medicalBag;
    }
    void takeDamage(int damage) override
    {
        HP -= damage;
    }
    void heal(int heal) override
    {
        HP += heal;
    }
    string getName()
    {
        return name;
    }
    int getHP()
    {
        return HP;
    }
    void setHP(int value)
    {
        HP = value;
    }
};
class Archer: public WeaponUser, PotionUser, SpellUser
{
private:
    string name;
    int HP;
    string type;
    Container<Weapon> arsenal;
    Container<Potion> medicalBag;
    Container<Spell> spellBook;
    map<string, vector<string>> targetList; // string - spell name, vector - targets
public:
    Archer(string &name, int HP, string &type)
        : name(name), HP(HP), type(type), medicalBag(Container<Potion>(3)), spellBook(Container<Spell>(2)),
          arsenal(Container<Weapon>(2))
    {};
    ~Archer() = default;
    void attack(Character &target, const string &weaponName) override
    {
        Weapon gun = arsenal.getItem(weaponName);
        target.setHP(target.getHP() - gun.getDamage());
    }
    void drink(Character &target, const string &pName) override
    {
        Potion clarity = medicalBag.getItem(pName);
        heal(clarity.getHealValue());
        medicalBag.removeItem(pName);
    }
    void cast(Character &target, const string &spellName) override
    {
        Spell first = spellBook.getItem(spellName);
        spellBook.removeItem(spellName);
    }
    void takeDamage(int damage) override
    {
        HP -= damage;
    }
    void heal(int heal) override
    {
        HP += heal;
    }
    void setHP(int value)
    {
        HP = value;
    }
    string getName()
    {
        return name;
    }
    int getHP()
    {
        return HP;
    }
    Container<Weapon> &getArsenal()
    {
        return arsenal;
    }
    Container<Spell> &getSpellBook()
    {
        return spellBook;
    }
    Container<Potion> &getMedicalBag()
    {
        return medicalBag;
    }
    map<string, vector<string>> &getTargetList()
    {
        return targetList;
    };

    void setTargetList(string &spellName, vector<string> &targets)
    {
        targetList.insert({spellName, targets});
    }
    void removeTarget(string &name)
    {
        targetList.erase(name);
    }
};
class Wizard: public PotionUser, public SpellUser
{
private:
    string name;
    int HP;
    Container<Potion> medicalBag;
    Container<Spell> spellBook;
    string type;
    map<string, vector<string>> targetList;// string - spell name, vector - targets
public:
    Wizard(string &name, int HP, string &type)
        : name(name), HP(HP), type(type), medicalBag(Container<Potion>(10)),
          spellBook(Container<Spell>(10))
    {};
    void drink(Character &target, const string &pName) override
    {
        Potion clarity = medicalBag.getItem(pName);
        heal(clarity.getHealValue());
        medicalBag.removeItem(pName);
    }
    void cast(Character &target, const string &spellName) override
    {
        Spell first = spellBook.getItem(spellName);
        spellBook.removeItem(spellName);
    }
    void takeDamage(int damage) override
    {
        HP -= damage;
    }
    void heal(int heal) override
    {
        HP += heal;
    }
    void setHP(int value) override
    {
        HP = value;
    }
    [[nodiscard]] int getHP() const
    {
        return HP;
    }
    [[nodiscard]] string getName() const
    {
        return name;
    }
    Container<Spell> &getSpellBook()
    {
        return spellBook;
    }
    Container<Potion> &getMedicalBag()
    {
        return medicalBag;
    }
    map<string, vector<string>> &getTargetList()
    {
        return targetList;
    };
    void setTargetList(string &spellName, vector<string> &targets)
    {
        targetList.insert({spellName, targets});
    }
    void removeTarget(string &name)
    {
        targetList.erase(name);
    }
};

int main()
{
    ofstream output("output.txt");
    ifstream input("input.txt");

    int rows;
    input >> rows;
    // storage with Fighters
    map<string, Fighter> fighters;
    // storage with Archers
    map<string, Archer> archers;
    // storage with Wizards
    map<string, Wizard> wizards;
    // Storage with all characters
    map<string, string> info;
    // storage for checking if specific potion exist
    map<string, string> potions;

    for (int i = 0; i < rows; i++) {
        string f_command;
        input >> f_command;

        if (f_command == "Dialogue") {
            string name;
            int word_amounts;
            input >> name;
            input >> word_amounts;
            vector<string> speech;
            for (int j = 0; j < word_amounts; j++) {
                string current_word;
                input >> current_word;
                speech.push_back(current_word);
            }
            // Output the dialogue of specific character
            if (info.contains(name) || name == "Narrator") {
                output << name << ": ";
                for (int k = 0; k < word_amounts; k++) {
                    output << speech[k] << " ";
                }
                output << "\n";
            }
            else {
                output << "Error caught\n";
            }
        }

        else if (f_command == "Create") {
            string s_command;
            input >> s_command;
            if (s_command == "item") {
                string item_type;
                input >> item_type;
                if (item_type == "weapon") {
                    string own;
                    string weaponName;
                    int damage;
                    input >> own;
                    input >> weaponName;
                    input >> damage;
                    if (damage <= 0) {
                        output << "Error caught\n";
                    }
                    else {
                        if (info.contains(own)) {
                            // Creating weapon for the fighter
                            if (fighters.contains(own)) {
                                Fighter fighter = fighters.at(own);
                                if (fighter.getArsenal().size() < 3) {
                                    Weapon weapon(weaponName, damage);
                                    fighter.getArsenal().addItem(weapon, weaponName);
                                    fighters.erase(own);
                                    fighters.insert({own, fighter});
                                    output << own << " just obtained a new weapon called " << weaponName
                                           << ".\n";
                                }
                                else {
                                    output << "Error caught\n";
                                }

                            }
                            else if (archers.contains(own)) {
                                // Creating weapon for the archer
                                Archer archer = archers.at(own);
                                if (archer.getArsenal().size() < 2) {
                                    Weapon weapon(weaponName, damage);
                                    archer.getArsenal().addItem(weapon, weaponName);
                                    archers.erase(own);
                                    archers.insert({own, archer});
                                    output << own << " just obtained a new weapon called " << weaponName
                                           << ".\n";
                                }
                                else {
                                    output << "Error caught\n";
                                }
                            }
                            else {
                                output << "Error caught\n";
                            }
                        }
                        else {
                            output << "Error caught\n";
                        }

                    }
                }
                else if (item_type == "potion") {
                    string own;
                    string pName;
                    int heal;
                    input >> own;
                    input >> pName;
                    input >> heal;
                    if (heal <= 0) {
                        output << "Error caught\n";
                    }
                    else {
                        if (info.contains(own)) {
                            if (fighters.contains(own)) {
                                // Creating potion for the fighter
                                Fighter fighter = fighters.at(own);
                                if (fighter.getMedicalBag().size() < 5) {
                                    Potion potion(heal, pName);
                                    fighter.getMedicalBag().addItem(potion, pName);
                                    fighters.erase(own);
                                    fighters.insert({own, fighter});
                                    potions.insert({pName, "fighter"});
                                    output << own << " just obtained a new potion called " << pName
                                           << ".\n";
                                }
                                else {
                                    output << "Error caught\n";
                                }

                            }
                            else if (archers.contains(own)) {
                                // Creating potion for the archer
                                Archer archer = archers.at(own);
                                if (archer.getMedicalBag().size() < 3) {
                                    Potion potion(heal, pName);
                                    archer.getMedicalBag().addItem(potion, pName);
                                    archers.erase(own);
                                    archers.insert({own, archer});
                                    potions.insert({pName, "archer"});
                                    output << own << " just obtained a new potion called " << pName
                                           << ".\n";
                                }
                                else {
                                    output << "Error caught\n";
                                }
                            }
                            else if (wizards.contains(own)) {
                                // Creating potion for the wizard
                                Wizard wizard = wizards.at(own);
                                if (wizard.getMedicalBag().size() < 10) {
                                    Potion potion(heal, pName);
                                    wizard.getMedicalBag().addItem(potion, pName);
                                    wizards.erase(own);
                                    wizards.insert({own, wizard});
                                    potions.insert({pName, "archer"});
                                    output << own << " just obtained a new potion called " << pName
                                           << ".\n";
                                }
                                else {
                                    output << "Error caught\n";
                                }
                            }
                            else {
                                output << "Error caught\n";
                            }

                        }
                        else {
                            output << "Error caught\n";
                        }
                    }
                }
                else if (item_type == "spell") {
                    string own;
                    string spellName;
                    int num_targets;
                    input >> own;
                    input >> spellName;
                    input >> num_targets;
                    vector<string> target_list;
                    for (int k = 0; k < num_targets; k++) {
                        string current_name;
                        input >> current_name;
                        if (info.contains(current_name)) {
                            target_list.push_back(current_name);
                        }
                    }
                    if (target_list.size() == num_targets) {
                        if (wizards.contains(own)) {
                            // Creating spell for the wizard
                            Wizard wizard = wizards.at(own);
                            if (wizard.getTargetList().size() < 10) {
                                wizard.setTargetList(spellName, target_list);
                                output << own << " just obtained a new spell called " << spellName << ".\n";
                                wizards.erase(own);
                                wizards.insert({own, wizard});

                            }
                            else {
                                output << "Error caught\n";
                            }
                        }
                        else if (archers.contains(own)) {
                            // Creating spell for the archer
                            Archer archer = archers.at(own);
                            if (archer.getTargetList().size() < 2) {
                                archer.setTargetList(spellName, target_list);
                                output << own << " just obtained a new spell called " << spellName << ".\n";
                                archers.erase(own);
                                archers.insert({own, archer});

                            }
                            else {
                                output << "Error caught\n";
                            }
                        }
                        else {
                            output << "Error caught\n";
                        }
                    }
                    else {
                        output << "Error caught\n";
                    }
                }
            }
            else if (s_command == "character") {
                string type_char;
                input >> type_char;
                // Creating a new fighter
                if (type_char == "fighter") {
                    string char_name;
                    input >> char_name;
                    int health_points;
                    input >> health_points;
                    string fighter_type = "fighter";
                    Fighter fighter(char_name, health_points, fighter_type);
                    fighters.insert({char_name, fighter});
                    info.insert({char_name, "fighter"});
                    output << "A new fighter came to town, " << char_name << ".\n";
                }
                    // Creating a new archer
                else if (type_char == "archer") {
                    string char_name;
                    input >> char_name;
                    int health_points;
                    input >> health_points;
                    string archer_type = "archer";
                    Archer archer(char_name, health_points, archer_type);
                    archers.insert({char_name, archer});

                    info.insert({char_name, "archer"});
                    output << "A new archer came to town, " << char_name << ".\n";
                }
                    // Creating a new wizard
                else if (type_char == "wizard") {
                    string char_name;
                    input >> char_name;
                    int health_points;
                    input >> health_points;
                    string wizard_type = "wizard";
                    Wizard wizard(char_name, health_points, wizard_type);
                    wizards.insert({char_name, wizard});
                    info.insert({char_name, "wizard"});
                    output << "A new wizard came to town, " << char_name << ".\n";
                }
            }

        }
        else if (f_command == "Attack") {
            string attacker;
            string target;
            string attack_type;
            input >> attacker;
            input >> target;
            input >> attack_type;
            if (info.contains(attacker) && info.contains(target)) {
                if (fighters.contains(attacker)) {
                    // If attacker is a Fighter
                    Fighter killer = fighters.at(attacker);
                    if (killer.getArsenal().find(attack_type)) {
                        // If target is a fighter
                        if (fighters.contains(target)) {
                            // If a person attacks himself
                            if (attacker == target) {
                                killer.setHP(killer.getHP()
                                                 - killer.getArsenal().getItem(attack_type).getDamage());
                                output << attacker << " attacks " << target << " with their " << attack_type << "!\n";
                                // If a fighter has dead
                                if (killer.getHP() <= 0) {
                                    info.erase(attacker);
                                    fighters.erase(attacker);
                                    output << target << " has died...\n";
                                }
                                else {
                                    fighters.erase(attacker);
                                    fighters.insert({attacker, killer});
                                }

                            }
                                // If attacker attacks another fighter
                            else {
                                Fighter victim = fighters.at(target);
                                victim.setHP(
                                    victim.getHP() - killer.getArsenal().getItem(attack_type).getDamage());
                                output << attacker << " attacks " << target << " with their " << attack_type << "!\n";
                                // If the fighter has dead
                                if (victim.getHP() <= 0) {
                                    info.erase(target);
                                    fighters.erase(target);
                                    output << target << " has died...\n";
                                }
                                else {
                                    fighters.erase(target);
                                    fighters.insert({target, victim});
                                }
                            }
                        }
                        else if (archers.contains(target)) {
                            // If target is an archer
                            Archer victim = archers.at(target);
                            victim.setHP(
                                victim.getHP() - killer.getArsenal().getItem(attack_type).getDamage());
                            output << attacker << " attacks " << target << " with their " << attack_type << "!\n";
                            // If target has dead
                            if (victim.getHP() <= 0) {
                                info.erase(target);
                                archers.erase(target);
                                output << target << " has died...\n";
                            }
                            else {
                                archers.erase(target);
                                archers.insert({target, victim});
                            }
                        }
                            // If target is a wizard
                        else if (wizards.contains(target)) {
                            Wizard victim = wizards.at(target);
                            victim.setHP(
                                victim.getHP() - killer.getArsenal().getItem(attack_type).getDamage());
                            output << attacker << " attacks " << target << " with their " << attack_type << "!\n";
                            // If target has dead
                            if (victim.getHP() <= 0) {
                                info.erase(target);
                                wizards.erase(target);
                                output << target << " has died...\n";
                            }
                            else {
                                wizards.erase(target);
                                wizards.insert({target, victim});
                            }
                        }
                    }
                    else {
                        output << "Error caught\n";
                    }
                }
                    // If attacker is an archer
                else if (archers.contains(attacker)) {
                    Archer killer = archers.at(attacker);
                    if (killer.getArsenal().find(attack_type)) {
                        // if target is a fighter
                        if (fighters.contains(target)) {
                            Fighter victim = fighters.at(target);
                            victim.setHP(
                                victim.getHP() - killer.getArsenal().getItem(attack_type).getDamage());
                            output << attacker << " attacks " << target << " with their " << attack_type << "!\n";
                            // if target has dead
                            if (victim.getHP() <= 0) {
                                info.erase(target);
                                fighters.erase(target);
                                output << target << " has died...\n";
                            }
                            else {
                                fighters.erase(target);
                                fighters.insert({target, victim});
                            }
                        }
                        else if (archers.contains(target)) {
                            // if archer attacks himself
                            if (attacker == target) {
                                killer.setHP(killer.getHP()
                                                 - killer.getArsenal().getItem(attack_type).getDamage());
                                output << attacker << " attacks " << target << " with their " << attack_type << "!\n";
                                // if archer has dead
                                if (killer.getHP() <= 0) {
                                    info.erase(attacker);
                                    archers.erase(attacker);
                                    output << target << " has died...\n";
                                }
                                else {
                                    archers.erase(attacker);
                                    archers.insert({attacker, killer});
                                }
                            }
                            else {
                                // if archer attacks another archer
                                Archer victim = archers.at(target);
                                victim.setHP(
                                    victim.getHP() - killer.getArsenal().getItem(attack_type).getDamage());
                                output << attacker << " attacks " << target << " with their " << attack_type << "!\n";
                                // if target has dead
                                if (victim.getHP() <= 0) {
                                    info.erase(target);
                                    archers.erase(target);
                                    output << target << " has died...\n";
                                }
                                else {
                                    archers.erase(target);
                                    archers.insert({target, victim});
                                }
                            }
                        }
                            // if archer attacks a wizard
                        else if (wizards.contains(target)) {
                            Wizard victim = wizards.at(target);
                            victim.setHP(
                                victim.getHP() - killer.getArsenal().getItem(attack_type).getDamage());
                            output << attacker << " attacks " << target << " with their " << attack_type << "!\n";
                            // if wizard has dead
                            if (victim.getHP() <= 0) {
                                info.erase(target);
                                wizards.erase(target);
                                output << target << " has died...\n";
                            }
                            else {
                                wizards.erase(target);
                                wizards.insert({target, victim});
                            }
                        }
                    }
                    else {
                        output << "Error caught\n";
                    }

                }
                else {
                    output << "Error caught\n";
                }
            }
            else {
                output << "Error caught\n";
            }
        }
        else if (f_command == "Cast") {
            string caster;
            string target;
            string spell_name;
            input >> caster;
            input >> target;
            input >> spell_name;
            if (info.contains(caster) && info.contains(target)) {
                if (archers.contains(caster)) {
                    // if archer attacks a fighter
                    if (fighters.contains(target)) {
                        Archer killer = archers.at(caster);
                        Fighter victim = fighters.at(target);
                        map<string, vector<string>> wanted_map = killer.getTargetList();
                        vector<string> wanted_list;
                        if (killer.getTargetList().contains(spell_name)) {
                            wanted_list = killer.getTargetList().at(spell_name);
                        }
                        bool flag = false;
                        for (int k = 0; k < wanted_list.size(); k++) {
                            if (wanted_list[k] == target) {
                                flag = true;
                                break;
                            }
                        }
                        if (flag) {
                            info.erase(target);
                            fighters.erase(target);
                            killer.getSpellBook().removeItem(spell_name);
                            killer.removeTarget(spell_name);

                            archers.erase(caster);
                            archers.insert({caster, killer});

                            output << caster << " casts " << spell_name << " on " << target << "!\n";
                            output << target << " has died...\n";
                        }
                        else {
                            output << "Error caught\n";
                        }
                    }

                    else if (archers.contains(target)) {
                        // if archer attacks himself
                        if (target == caster) {
                            Archer victim = archers.at(caster);
                            map<string, vector<string>> wanted_string = victim.getTargetList();
                            vector<string> wanted_list;
                            if (victim.getTargetList().contains(spell_name)) {
                                wanted_list = victim.getTargetList().at(spell_name);
                            }
                            bool flag = false;
                            for (int k = 0; k < wanted_list.size(); k++) {
                                if (wanted_list[k] == target) {
                                    flag = true;
                                    break;
                                }
                            }
                            if (flag) {
                                victim.getSpellBook().removeItem(spell_name);
                                info.erase(target);
                                archers.erase(target);
                                output << caster << " casts " << spell_name << " on " << target << "!\n";
                                output << target << " has died...\n";
                            }
                            else {
                                output << "Error caught\n";
                            }
                        }
                        else {
                            // if archer attacks another archer
                            Archer killer = archers.at(caster);
                            Archer victim = archers.at(target);
                            map<string, vector<string>> wanted_map = killer.getTargetList();
                            vector<string> wanted_list;
                            if (killer.getTargetList().contains(spell_name)) {
                                wanted_list = killer.getTargetList().at(spell_name);
                            }
                            bool flag = false;
                            for (int k = 0; k < wanted_list.size(); k++) {
                                if (wanted_list[k] == target) {
                                    flag = true;
                                    break;
                                }
                            }
                            if (flag) {
                                info.erase(target);
                                archers.erase(target);
                                killer.getSpellBook().removeItem(spell_name);
                                killer.removeTarget(spell_name);

                                archers.erase(caster);
                                archers.insert({caster, killer});

                                output << caster << " casts " << spell_name << " on " << target << "!\n";
                                output << target << " has died...\n";
                            }
                            else {
                                output << "Error caught\n";
                            }
                        }
                    }
                        // if archer attacks a wizard
                    else if (wizards.contains(target)) {
                        Archer killer = archers.at(caster);
                        Wizard victim = wizards.at(target);
                        map<string, vector<string>> wanted_map = killer.getTargetList();
                        vector<string> wanted_list;
                        if (killer.getTargetList().contains(spell_name)) {
                            wanted_list = killer.getTargetList().at(spell_name);
                        }
                        bool flag = false;
                        for (int k = 0; k < wanted_list.size(); k++) {
                            if (wanted_list[k] == target) {
                                flag = true;
                                break;
                            }
                        }
                        if (flag) {
                            info.erase(target);
                            wizards.erase(target);
                            killer.getSpellBook().removeItem(spell_name);
                            killer.removeTarget(spell_name);
                            archers.erase(caster);
                            archers.insert({caster, killer});

                            output << caster << " casts " << spell_name << " on " << target << "!\n";
                            output << target << " has died...\n";
                        }
                        else {
                            output << "Error caught\n";
                        }
                    }
                    else {
                        output << "Error caught\n";
                    }
                }
                    // if wizard casts a spell
                else if (wizards.contains(caster)) {
                    // if wizard casts a spell on a fighter
                    if (fighters.contains(target)) {
                        Wizard killer = wizards.at(caster);
                        Fighter victim = fighters.at(target);
                        map<string, vector<string>> wanted_map = killer.getTargetList();
                        vector<string> wanted_list;
                        if (killer.getTargetList().contains(spell_name)) {
                            wanted_list = killer.getTargetList().at(spell_name);
                        }
                        bool flag = false;
                        for (int k = 0; k < wanted_list.size(); k++) {
                            if (wanted_list[k] == target) {
                                flag = true;
                                break;
                            }
                        }
                        if (flag) {
                            info.erase(target);
                            fighters.erase(target);
                            killer.getSpellBook().removeItem(spell_name);
                            killer.removeTarget(spell_name);
                            wizards.erase(caster);
                            wizards.insert({caster, killer});

                            output << caster << " casts " << spell_name << " on " << target << "!\n";
                            output << target << " has died...\n";
                        }
                        else {
                            output << "Error caught\n";
                        }
                    }
                        // if wizard casts a spell on an archer
                    else if (archers.contains(target)) {
                        Wizard killer = wizards.at(caster);
                        Archer victim = archers.at(target);
                        map<string, vector<string>> wanted_map = killer.getTargetList();
                        vector<string> wanted_list;
                        if (killer.getTargetList().contains(spell_name)) {
                            wanted_list = killer.getTargetList().at(spell_name);
                        }
                        bool flag = false;
                        for (int k = 0; k < wanted_list.size(); k++) {
                            if (wanted_list[k] == target) {
                                flag = true;
                                break;
                            }
                        }
                        if (flag) {
                            info.erase(target);
                            archers.erase(target);
                            killer.getSpellBook().removeItem(spell_name);
                            killer.removeTarget(spell_name);

                            wizards.erase(caster);
                            wizards.insert({caster, killer});

                            output << caster << " casts " << spell_name << " on " << target << "!\n";
                            output << target << " has died...\n";
                        }
                        else {
                            output << "Error caught\n";
                        }
                    }
                    else if (wizards.contains(target)) {
                        // if wizard casts a spell on himself
                        if (caster == target) {
                            Wizard victim = wizards.at(caster);
                            map<string, vector<string>> wanted_map = victim.getTargetList();
                            vector<string> wanted_list;
                            if (victim.getTargetList().contains(spell_name)) {
                                wanted_list = victim.getTargetList().at(spell_name);
                            }
                            bool flag = false;
                            for (int k = 0; k < wanted_list.size(); k++) {
                                if (wanted_list[k] == target) {
                                    flag = true;
                                    break;
                                }
                            }
                            if (flag) {
                                victim.getSpellBook().removeItem(spell_name);
                                info.erase(target);
                                wizards.erase(target);

                                output << caster << " casts " << spell_name << " on " << target << "!\n";
                                output << target << " has died...\n";
                            }
                            else {
                                output << "Error caught\n";
                            }
                        }
                            // if wizard casts a spell on another wizard
                        else {
                            Wizard killer = wizards.at(caster);
                            Wizard victim = wizards.at(target);
                            map<string, vector<string>> wanted_map = killer.getTargetList();
                            vector<string> wanted_list;
                            if (killer.getTargetList().contains(spell_name)) {
                                wanted_list = killer.getTargetList().at(spell_name);
                            }
                            bool flag = false;
                            for (int k = 0; k < wanted_list.size(); k++) {
                                if (wanted_list[k] == target) {
                                    flag = true;
                                    break;
                                }
                            }
                            if (flag) {
                                info.erase(target);
                                wizards.erase(target);
                                killer.getSpellBook().removeItem(spell_name);
                                killer.removeTarget(spell_name);

                                wizards.erase(caster);
                                wizards.insert({caster, killer});

                                output << caster << " casts " << spell_name << " on " << target << "!\n";
                                output << target << " has died...\n";
                            }
                            else {
                                output << "Error caught\n";
                            }
                        }
                    }
                    else {
                        output << "Error caught\n";
                    }
                }
                else {
                    output << "Error caught\n";
                }
            }
            else {
                output << "Error caught\n";
            }

        }
        else if (f_command == "Drink") {
            string supplier;
            string drinker;
            string pName;
            input >> supplier;
            input >> drinker;
            input >> pName;
            if (potions.contains(pName) && info.contains(supplier) && info.contains(drinker)) {
                if (fighters.contains(supplier)) {
                    Fighter fighter_supplier = fighters.at(supplier);
                    if (fighter_supplier.getMedicalBag().find(pName)) {
                        Potion potion = fighter_supplier.getMedicalBag().getItem(pName);
                        if (fighters.contains(drinker)) {
                            // if a fighter drinks his potion
                            if (supplier == drinker) {
                                fighter_supplier.setHP(fighter_supplier.getHP() + potion.getHealValue());
                                fighter_supplier.getMedicalBag().removeItem(pName);
                                potions.erase(pName);
                                fighters.erase(fighter_supplier.getName());
                                fighters.insert({fighter_supplier.getName(), fighter_supplier});
                                output << drinker << " drinks " << pName << " from " << supplier << ".\n";
                            }
                                // if a fighter drinks a potion from another fighter
                            else {
                                Fighter fighter_drinker = fighters.at(drinker);
                                fighter_supplier.getMedicalBag().removeItem(pName);
                                fighter_drinker.setHP(fighter_drinker.getHP() + potion.getHealValue());
                                fighters.erase(fighter_supplier.getName());
                                fighters.erase(fighter_drinker.getName());
                                potions.erase(pName);

                                fighters.insert({fighter_supplier.getName(), fighter_supplier});
                                fighters.insert({fighter_drinker.getName(), fighter_drinker});
                                output << drinker << " drinks " << pName << " from " << supplier << ".\n";
                            }
                        }
                            // if a fighter drinks a potion from an archer
                        else if (archers.contains(drinker)) {
                            Archer archer_drinker = archers.at(drinker);
                            fighter_supplier.getMedicalBag().removeItem(pName);
                            archer_drinker.setHP(archer_drinker.getHP() + potion.getHealValue());
                            fighters.erase(fighter_supplier.getName());
                            archers.erase(archer_drinker.getName());
                            potions.erase(pName);
                            fighters.insert({fighter_supplier.getName(), fighter_supplier});
                            archers.insert({archer_drinker.getName(), archer_drinker});
                            output << drinker << " drinks " << pName << " from " << supplier << ".\n";
                        }
                            // if a fighter drinks a potion from a wizard
                        else if (wizards.contains(drinker)) {
                            Wizard wizard_drinker = wizards.at(drinker);
                            fighter_supplier.getMedicalBag().removeItem(pName);
                            wizard_drinker.setHP(wizard_drinker.getHP() + potion.getHealValue());

                            fighters.erase(fighter_supplier.getName());
                            wizards.erase(wizard_drinker.getName());
                            potions.erase(pName);
                            fighters.insert({fighter_supplier.getName(), fighter_supplier});
                            wizards.insert({wizard_drinker.getName(), wizard_drinker});
                            output << drinker << " drinks " << pName << " from " << supplier << ".\n";
                        }
                        else {
                            output << "Error caught\n";
                        }
                    }
                    else {
                        output << "Error caught\n";
                    }

                }

                else if (archers.contains(supplier)) {
                    Archer archer_supplier = archers.at(supplier);
                    if (archer_supplier.getMedicalBag().find(pName)) {
                        Potion potion = archer_supplier.getMedicalBag().getItem(pName);
                        // if an archer drinks a potion from another fighter
                        if (fighters.contains(drinker)) {
                            Fighter fighter_drinker = fighters.at(drinker);
                            archer_supplier.getMedicalBag().removeItem(pName);
                            fighter_drinker.setHP(fighter_drinker.getHP() + potion.getHealValue());
                            potions.erase(pName);

                            archers.erase(archer_supplier.getName());
                            fighters.erase(fighter_drinker.getName());
                            archers.insert({archer_supplier.getName(), archer_supplier});
                            fighters.insert({fighter_drinker.getName(), fighter_drinker});
                            output << drinker << " drinks " << pName << " from " << supplier << ".\n";
                        }
                        else if (archers.contains(drinker)) {
                            // if an archer drinks his potion
                            if (supplier == drinker) {
                                archer_supplier.setHP(archer_supplier.getHP() + potion.getHealValue());
                                archer_supplier.getMedicalBag().removeItem(pName);
                                potions.erase(pName);
                                archers.erase(archer_supplier.getName());
                                archers.insert({archer_supplier.getName(), archer_supplier});
                                output << drinker << " drinks " << pName << " from " << supplier << ".\n";
                            }
                                // if an archer drinks a potion from another archer
                            else {
                                Archer archer_drinker = archers.at(drinker);
                                archer_supplier.getMedicalBag().removeItem(pName);
                                archer_drinker.setHP(archer_drinker.getHP() + potion.getHealValue());
                                archers.erase(archer_supplier.getName());
                                archers.erase(archer_drinker.getName());
                                potions.erase(pName);
                                archers.insert({archer_supplier.getName(), archer_supplier});
                                archers.insert({archer_drinker.getName(), archer_drinker});
                                output << drinker << " drinks " << pName << " from " << supplier << ".\n";
                            }
                        }
                            // if an archer drinks a potion from wizard
                        else if (wizards.contains(drinker)) {
                            Wizard wizard_drinker = wizards.at(drinker);
                            archer_supplier.getMedicalBag().removeItem(pName);
                            wizard_drinker.setHP(wizard_drinker.getHP() + potion.getHealValue());
                            archers.erase(archer_supplier.getName());
                            wizards.erase(wizard_drinker.getName());
                            potions.erase(pName);
                            archers.insert({archer_supplier.getName(), archer_supplier});
                            wizards.insert({wizard_drinker.getName(), wizard_drinker});
                            output << drinker << " drinks " << pName << " from " << supplier << ".\n";
                        }
                        else {
                            output << "Error caught\n";
                        }
                    }
                    else {
                        output << "Error caught\n";
                    }

                }

                else if (wizards.contains(supplier)) {
                    Wizard wizard_supplier = wizards.at(supplier);
                    if (wizard_supplier.getMedicalBag().find(pName)) {
                        Potion potion = wizard_supplier.getMedicalBag().getItem(pName);
                        // if a wizard drinks a potion from a fighter
                        if (fighters.contains(drinker)) {
                            Fighter fighter_drinker = fighters.at(drinker);
                            wizard_supplier.getMedicalBag().removeItem(pName);
                            fighter_drinker.setHP(fighter_drinker.getHP() + potion.getHealValue());

                            wizards.erase(wizard_supplier.getName());
                            fighters.erase(fighter_drinker.getName());
                            potions.erase(pName);

                            wizards.insert({wizard_supplier.getName(), wizard_supplier});
                            fighters.insert({fighter_drinker.getName(), fighter_drinker});
                            output << drinker << " drinks " << pName << " from " << supplier << ".\n";
                        }
                            // if a wizard drinks a potion from an archer
                        else if (archers.contains(drinker)) {
                            Archer archer_drinker = archers.at(drinker);
                            wizard_supplier.getMedicalBag().removeItem(pName);
                            archer_drinker.setHP(archer_drinker.getHP() + potion.getHealValue());

                            wizards.erase(wizard_supplier.getName());
                            archers.erase(archer_drinker.getName());
                            potions.erase(pName);

                            wizards.insert({wizard_supplier.getName(), wizard_supplier});
                            archers.insert({archer_drinker.getName(), archer_drinker});
                            output << drinker << " drinks " << pName << " from " << supplier << ".\n";
                        }

                        else if (wizards.contains(supplier)) {
                            // if a wizard drinks his potion
                            if (supplier == drinker) {
                                wizard_supplier.setHP(wizard_supplier.getHP() + potion.getHealValue());
                                wizard_supplier.getMedicalBag().removeItem(pName);
                                potions.erase(pName);
                                wizards.erase(wizard_supplier.getName());
                                wizards.insert({wizard_supplier.getName(), wizard_supplier});
                                output << drinker << " drinks " << pName << " from " << supplier << ".\n";
                            }
                                // if a wizard drinks a potion from another wizard
                            else {
                                Wizard wizard_drinker = wizards.at(drinker);
                                wizard_supplier.getMedicalBag().removeItem(pName);
                                wizard_drinker.setHP(wizard_drinker.getHP() + potion.getHealValue());

                                wizards.erase(wizard_supplier.getName());
                                wizards.erase(wizard_drinker.getName());
                                potions.erase(pName);

                                wizards.insert({wizard_supplier.getName(), wizard_supplier});
                                wizards.insert({wizard_drinker.getName(), wizard_drinker});
                                output << drinker << " drinks " << pName << " from " << supplier << ".\n";
                            }
                        }
                        else {
                            output << "Error caught\n";
                        }
                    }
                    else {
                        output << "Error caught\n";
                    }

                }
            }
            else {
                output << "Error caught\n";
            }
        }
        else if (f_command == "Show") {
            string show_type;
            input >> show_type;
            if (show_type == "characters") {
                vector<string> all_characters;
                for (auto k = info.begin(); k != info.end(); k++) {
                    all_characters.push_back(k->first);
                }
                sort(all_characters.begin(), all_characters.end());
                // Showing characters by alphabetic order
                for (int k = 0; k < all_characters.size(); k++) {
                    if (info.at(all_characters[k]) == "fighter") {
                        output << fighters.at(all_characters[k]).getName() << ":" << "fighter" << ":"
                               << fighters.at(all_characters[k]).getHP() << " ";
                    }
                    else if (info.at(all_characters[k]) == "archer") {
                        output << archers.at(all_characters[k]).getName() << ":" << "archer" << ":"
                               << archers.at(all_characters[k]).getHP() << " ";
                    }
                    else if (info.at(all_characters[k]) == "wizard") {
                        output << wizards.at(all_characters[k]).getName() << ":" << "wizard" << ":"
                               << wizards.at(all_characters[k]).getHP() << " ";
                    }
                }
                output << "\n";
            }
            else if (show_type == "weapons") {
                string character_name;
                input >> character_name;
                if (info.contains(character_name)) {
                    if (fighters.contains(character_name)) {

                        Fighter fighter = fighters.at(character_name);
                        map<string, Weapon> weapon_map = fighter.getArsenal().getContainer();
                        vector<string> weapon_sort;
                        for (auto k = weapon_map.begin(); k != weapon_map.end(); k++) {
                            weapon_sort.push_back(k->first);
                        }
                        // Showing the fighter's weapons
                        sort(weapon_sort.begin(), weapon_sort.end());
                        for (int k = 0; k < weapon_sort.size(); k++) {
                            output << weapon_sort[k] << ":" << weapon_map.at(weapon_sort[k]).getDamage() << " ";
                        }
                        output << "\n";
                    }
                    else if (archers.contains(character_name)) {
                        Archer archer = archers.at(character_name);
                        map<string, Weapon> weapon_map = archer.getArsenal().getContainer();
                        vector<string> weapon_sort;
                        for (auto k = weapon_map.begin(); k != weapon_map.end(); k++) {
                            weapon_sort.push_back(k->first);
                        }
                        sort(weapon_sort.begin(), weapon_sort.end());
                        // Showing the archer's weapons
                        for (int k = 0; k < weapon_sort.size(); k++) {
                            output << weapon_sort[k] << ":" << weapon_map.at(weapon_sort[k]).getDamage() << " ";
                        }
                        output << "\n";
                    }
                    else {
                        output << "Error caught\n";
                    }
                }
                else {
                    output << "Error caught\n";
                }
            }
            else if (show_type == "potions") {
                string character_name;
                input >> character_name;
                if (info.contains(character_name)) {
                    if (fighters.contains(character_name)) {
                        Fighter fighter = fighters.at(character_name);
                        map<string, Potion> potion_map = fighter.getMedicalBag().getContainer();
                        vector<string> potion_sort;
                        for (auto k = potion_map.begin(); k != potion_map.end(); k++) {
                            potion_sort.push_back(k->first);
                        }
                        // Showing the fighter's potions
                        sort(potion_sort.begin(), potion_sort.end());
                        for (int k = 0; k < potion_sort.size(); k++) {
                            output << potion_sort[k] << ":" << potion_map.at(potion_sort[k]).getHealValue()
                                   << " ";
                        }
                        output << "\n";
                    }
                    else if (archers.contains(character_name)) {
                        Archer archer = archers.at(character_name);
                        map<string, Potion> potion_map = archer.getMedicalBag().getContainer();
                        vector<string> potion_sort;
                        int iterator = 0;
                        for (auto k = potion_map.begin(); k != potion_map.end(); k++) {
                            potion_sort.push_back(k->first);
                        }
                        sort(potion_sort.begin(), potion_sort.end());
                        // Showing the archer's potions
                        for (int k = 0; k < potion_sort.size(); k++) {
                            output << potion_sort[k] << ":" << potion_map.at(potion_sort[k]).getHealValue()
                                   << " ";
                        }
                        output << "\n";
                    }
                    else if (wizards.contains(character_name)) {
                        Wizard wizard = wizards.at(character_name);
                        map<string, Potion> potion_map = wizard.getMedicalBag().getContainer();
                        vector<string> potion_sort;
                        for (auto k = potion_map.begin(); k != potion_map.end(); k++) {
                            potion_sort.push_back(k->first);
                        }
                        sort(potion_sort.begin(), potion_sort.end());
                        // Showing the wizard's potions
                        for (int k = 0; k < potion_sort.size(); k++) {
                            output << potion_sort[k] << ":" << potion_map.at(potion_sort[k]).getHealValue()
                                   << " ";
                        }
                        output << "\n";
                    }
                }
                else {
                    output << "Error caught\n";
                }

            }
            else if (show_type == "spells") {
                string character_name;
                input >> character_name;
                if (info.contains(character_name)) {
                    if (archers.contains(character_name)) {
                        Archer archer = archers.at(character_name);
                        map<string, vector<string>> spell_map = archer.getTargetList();
                        vector<string> spell_sort;
                        int iterator = 0;
                        for (auto k = spell_map.begin(); k != spell_map.end(); k++) {
                            spell_sort.push_back(k->first);
                        }
                        sort(spell_sort.begin(), spell_sort.end());
                        // Showing the archer's spells
                        for (int k = 0; k < spell_sort.size(); k++) {
                            output << spell_sort[k] << ":" << archer.getTargetList().at(spell_sort[k]).size() << " ";
                        }
                        output << "\n";

                    }
                    else if (wizards.contains(character_name)) {
                        Wizard wizard = wizards.at(character_name);
                        map<string, vector<string>> spell_map = wizard.getTargetList();
                        vector<string> spell_sort;
                        int iterator = 0;
                        for (auto k = spell_map.begin(); k != spell_map.end(); k++) {
                            spell_sort.push_back(k->first);
                        }
                        sort(spell_sort.begin(), spell_sort.end());
                        // Showing the wizard's spells
                        for (int k = 0; k < spell_sort.size(); k++) {
                            output << spell_sort[k] << ":" << wizard.getTargetList().at(spell_sort[k]).size() << " ";
                        }
                        output << "\n";
                    }
                    else {
                        output << "Error caught\n";
                    }
                }
                else {
                    output << "Error caught\n";
                }
            }
        }
    }
    input.
        close();
    output.
        close();
    return 0;
}