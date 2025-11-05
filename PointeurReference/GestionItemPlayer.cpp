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

struct Player;

// ---- Caractéristiques d'un item ----
struct Item
{
    ItemType type;
    int durability = 100;
    int quality = 100;
    Player *owner = nullptr;
};

// ---- Caractéristiques d'un player ----
struct Player
{
    std::string name;
    int health = 100;
    Item *rightHand;
    Item *leftHand;
};

// ---- Juste pour la lisibilité dans la console ----
std::string ItemTypeToString(ItemType type)
{
    switch (type)
    {
    case Sword:
        return "Sword";
    case Shield:
        return "Shield";
    case Wand:
        return "Wand";
    case Bow:
        return "Bow";
    default:
        return "Empty";
    }
}

// ---- Prototypes ----
void DisplayItem(Item &item);
void Grab(Player &player, Item &item, Hand hand);
void Drop(Player &player, Hand hand);
void DisplayPlayer(Player &player);

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

    Player playerB;
    playerB.name = "José";
    playerB.rightHand = nullptr;
    playerB.leftHand = nullptr;

    // ---- Le player attrape des items ----
    Grab(playerA, sword, Left);
    Grab(playerA, shield, Right);

    // ---- Le player lâche les items ----
    Drop(playerA, Left);
    Drop(playerA, Right);

    Grab(playerB, bow, Both);
    Grab(playerA, wand, Right);

    // ---- Affichage du player ----
    DisplayPlayer(playerA);
    DisplayPlayer(playerB);
}

// ---- Affichage des caractéristiques d'un item ----
void DisplayItem(Item &item)
{
    std::cout << "Type d'item : " << ItemTypeToString(item.type) << std::endl;
    std::cout << "Durabilité : " << item.durability << std::endl;
    std::cout << "Qualité : " << item.quality << std::endl;
    std::cout << "------------------" << std::endl;
}

// ---- Affichage des caractéristiques du player ----
void DisplayPlayer(Player &player)
{
    std::cout << "------------------" << std::endl;
    std::cout << "Nom : " << player.name << std::endl;
    std::cout << "Santé : " << player.health << std::endl;

    std::cout << "\nMain gauche : ";
    if (player.leftHand != nullptr)
    {
        std::cout << "" << std::endl;
        DisplayItem(*player.leftHand);
    }
    else
    {
        std::cout << "Main vide" << std::endl;
    }

    std::cout << "Main droite : ";
    if (player.rightHand != nullptr)
    {
        std::cout << "" << std::endl;
        DisplayItem(*player.rightHand);
    }
    else
    {
        std::cout << "Main vide" << std::endl;
    }
}

// ---- Fonction permettant au player de prendre un item ----
void Grab(Player &player, Item &item, Hand hand)
{
    if (item.owner == nullptr)
    {
        if (hand == Both)
        {
            if (player.rightHand != nullptr || player.leftHand != nullptr)
            {
                std::cout << "Les mains sont déjà prises" << std::endl;
                return;
            }

            player.rightHand = &item;
            player.leftHand = &item;
            item.owner = &player;
            std::cout << ItemTypeToString(item.type) << " dans les deux mains" << std::endl;
        }
        else if (hand == Right)
        {
            if (player.rightHand != nullptr)
            {
                std::cout << "Main droite déjà prise" << std::endl;
                return;
            }

            player.rightHand = &item;
            item.owner = &player;
            std::cout << ItemTypeToString(item.type) << " dans la main droite" << std::endl;
        }
        else if (hand == Left)
        {
            if (player.leftHand != nullptr)
            {
                std::cout << "Main gauche déjà prise" << std::endl;
                return;
            }

            player.leftHand = &item;
            item.owner = &player;
            std::cout << ItemTypeToString(item.type) << " dans la main gauche" << std::endl;
        }
    }
    else
    std::cout << "Cet item est déjà pris par :" << &player << std::endl;
}

// ---- Fonction permettant au player de lâcher un item ----
void Drop(Player &player, Hand hand)
{
    if (hand == Right)
    {
        if (player.rightHand == nullptr)
        {
            std::cout << "Main droite déjà vide" << std::endl;
            return;
        }

        player.rightHand = nullptr;
        std::cout << "Main droite vide, item lâché" << std::endl;
        return;
    }

    if (hand == Left)
    {
        if (player.leftHand == nullptr)
        {
            std::cout << "Main gauche déjà vide" << std::endl;
            return;
        }

        player.leftHand = nullptr;
        std::cout << "Main gauche vide, item lâché" << std::endl;
        return;
    }

    if (hand == Both)
    {
        if (player.rightHand == nullptr && player.leftHand == nullptr)
        {
            std::cout << "Mains déjà vides" << std::endl;
            return;
        }

        player.rightHand = nullptr;
        player.leftHand = nullptr;
        std::cout << "Mains vides, item(s) lâché(s)" << std::endl;
        return;
    }
}