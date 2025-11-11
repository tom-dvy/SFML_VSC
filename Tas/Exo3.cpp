#include <iostream>

int main()
{
    for (int i = 1; i <= 5; i++)
    {
        // allouer dynamiquement un tableau de taille i
        int * tab = new int[i];

        // remplir chaque case avec sa valeur d'index
        for (int j = 0; j < i; ++j)
        {
            tab[j] = j;
        }

        // afficher le contenu du tableau
        std::cout << "Taille = " << i << std::endl;
        for (int j = 0; j < i; ++j)
        {
            std::cout << tab[j] << std::endl;
        }

        // désallouer
        delete[] tab;
    }
    
}