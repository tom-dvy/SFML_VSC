#include <iostream>

// ---- Exercice 1 ----

/*
a vaut : 3

b vaut : 4.0

c vaut : 0

d vaut : 250

e vaut : false

f vaut : true

g vaut : false

h vaut : -5

tab[2] vaut : 3

std::cout << s; affiche :
abc
def g
*/

// ---- Exercice 2 ----
/* Partie 1
int main()
{
    int tab[10];

    for (int i = 0; i <= 10; i++)
    {
        tab[i] = i;
        std::cout << "Index : " << i << ", Valeur : " << tab[i] << std::endl;
    }
}
*/

/* Partie 2
int main()
{
    int somme = 0;
    int i = 0;

    while (somme < 100)
    {
        i++;
        somme = i + somme;
    }
    std::cout << "Somme : " << somme << std::endl;
}
*/

// ---- Exercice 3 ----

/* Parrie 1
int Abs(int value)
{
    if (value > 0)
    {
        return value;
    }
    else
    {
        return -value;
    }
    
}

int main()
{
    int value1 = -3;
    int value2 = 7;

    Abs(value1);
    Abs(value2);

    std::cout << "Valeur 1 avant Abs : " << value1 << " et après : " << Abs(-3) << ", Valeur 2 avant abs : " << value2 << " et après : " << Abs(7) << std::endl;
}
*/

/* Partie 2
int Abs(int value)
{
    if (value > 0)
    {
        return value;
    }
    else
    {
        return -value;
    }
    
}

int main()
{
    int value1 = -3;
    int value2 = 7;
    
    int resultValue1 = Abs(value1);
    int resultValue2 = Abs(value2);
    
    std::cout << "Valeur 1 avant Abs : " << value1 << " et après : " << resultValue1 << ", Valeur 2 avant abs : " << value2 << " et après : " << resultValue2 << std::endl;
}
*/

/* ---- Exercice 4 ----

int Attack(std::string typeAttaquant, int puissanceAttaquant, std::string typeDefenseur)
{
    int degats = puissanceAttaquant;

    // Définition des faiblesses et résistances et des dégats liés

    // Type Electric
    if (typeAttaquant == "electric" && typeDefenseur == "water")
    {
        degats = puissanceAttaquant * 2;
    }
    else if (typeAttaquant == "electric" && typeDefenseur == "fire")
    {
        degats = puissanceAttaquant;
    }
    else if (typeAttaquant == "electric" && typeDefenseur == "plant")
    {
        degats = puissanceAttaquant;
    }

    // Type water
    else if (typeAttaquant == "water" && typeDefenseur == "fire")
    {
        degats = puissanceAttaquant * 2;
    }
    else if (typeAttaquant == "water" && typeDefenseur == "electric")
    {
        degats = puissanceAttaquant;
    }
    else if (typeAttaquant == "water" && typeDefenseur == "plant")
    {
        degats = puissanceAttaquant / 2;
    }

    // Type Fire
    else if (typeAttaquant == "fire" && typeDefenseur == "electric")
    {
        degats = puissanceAttaquant;
    }
    else if (typeAttaquant == "fire" && typeDefenseur == "water")
    {
        degats = puissanceAttaquant / 2;
    }
    else if (typeAttaquant == "fire" && typeDefenseur == "plant")
    {
        degats = puissanceAttaquant * 2;
    }

    // Type Plant
    else if (typeAttaquant == "plant" && typeDefenseur == "electric")
    {
        degats = puissanceAttaquant;
    }
    else if (typeAttaquant == "plant" && typeDefenseur == "water")
    {
        degats = puissanceAttaquant * 2;
    }
    else if (typeAttaquant == "plant" && typeDefenseur == "fire")
    {
        degats = puissanceAttaquant / 2;
    }

    return degats;
}

int main()
{
    std::string names[4] = {"Pikachu", "Carapuce", "Salameche", "Torterra"};
    std::string types[4] = {"electric", "water", "fire", "plant"};
    int powers[4] = {100, 40, 60, 150};

    int degats = Attack(types[0], powers[0], types[1]);

    std::cout << names[0] << "(" << types[0] << ")" << " attaque " << names[1] << "(" << types[1] << "), et lui inflige " << degats << " dégats" << std::endl;
}
*/