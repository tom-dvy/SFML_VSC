#include <iostream>

// ---- Les types d'items ----
enum ItemType
{
    Sword,
    Shield,
    Wand,
    Bow
};

// ---- Les mains disponibles ----
enum Hand
{
    Left,
    Right,
    Both
};

// ---- Caractéristiques d'un item ----
struct Item
{
    ItemType type;
    int durability = 100;
    int quality = 100;
};

// ---- Caractéristiques d'un player ----
struct Player
{
    std::string name;
    int health = 100;
    Item *rightHand;
    Item *leftHand;
};

// ---- Prototypes ----
void DisplayItem(Item &item);
void Grab(Player &playerA, Item &item, Hand hand);
void Drop(Player &playerA, Hand hand);

int main()
{
// ---- Création des items ----
    Item sword;
    sword.type = Sword;

    Item shield;
    shield.type = Shield;

    Item wand;
    wand.type = Wand;

    Item bow;
    bow.type = Bow;

// ---- Affichage des items ----
    DisplayItem(sword);
    DisplayItem(shield);
    DisplayItem(wand);
    DisplayItem(bow);

// ---- Création du player ----
    Player playerA;
    playerA.name = "Homer";
    playerA.rightHand = nullptr;
    playerA.leftHand = nullptr;

// ---- Le player attrape des items ----
    Grab(playerA, sword, Left);

// ---- Le player lâche les items ----
    Drop(playerA, Left);
}

// ---- Affichage des caractéristiques d'un item ----
void DisplayItem(Item &item)
{
    std::cout << "Item Type : " << item.type << std::endl;
    std::cout << "Durability : " << item.durability << std::endl;
    std::cout << "Quality : " << item.quality << std::endl;
    std::cout << "------------------" << std::endl;
}

// ---- Fonction permettant au player de prendre un item ----
void Grab(Player &playerA,Item &item, Hand hand)
{
    if (hand == Both)
    {
        if (playerA.rightHand != nullptr || playerA.leftHand != nullptr)
        {
            std::cout << "Les mains sont déjà prises" << std::endl;
            return;
        }

        playerA.rightHand = &item;
        playerA.leftHand = &item;
        std::cout << item.type <<" dans les deux mains" << std::endl;
    }
    else
    if (hand == Right)
    {
        if (playerA.rightHand != nullptr)
        {
            std::cout << "Main droite déjà prise" << std::endl;
            return;
        }

        playerA.rightHand = &item;
        std::cout << item.type << " dans la main droite" << std::endl;
    }
    else 
    if (hand == Left)
    {
        if (playerA.leftHand != nullptr)
        {
            std::cout << "Main gauche déjà prise" << std::endl;
            return;
        }

        playerA.leftHand = &item;
        std::cout << item.type << " dans la main gauche" << std::endl;
    }
}

// ---- Fonction permettant au player de lâcher un item ----
void Drop(Player &playerA, Hand hand)
{
    playerA.leftHand = nullptr;
    playerA.rightHand = nullptr;

    std::cout << "Les mains sont vides, les items ont été lâchés" << std::endl;
}