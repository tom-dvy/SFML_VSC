#include <iostream>

enum ItemType
{
    Sword,
    Shield,
    Wand,
    Bow
};

struct Item
{
    ItemType type;
    int durability = 100;
    int quality = 100;
};

void DisplayItem(Item &item);

int main()
{
    Item sword;
    sword.type = Sword;

    Item shield;
    shield.type = Shield;

    Item wand;
    wand.type = Wand;

    Item bow;
    bow.type = Bow;

    DisplayItem(sword);
    DisplayItem(shield);
    DisplayItem(wand);
    DisplayItem(bow);

}

void DisplayItem(Item &item)
{
    std::cout << "------------------" << std::endl;
    std::cout << "Item Type : " << item.type << std::endl;
    std::cout << "Durability : " << item.durability << std::endl;
    std::cout << "Quality : " << item.quality << std::endl;
}