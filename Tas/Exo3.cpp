#include <iostream>

int main()
{
    for (int i = 1; i <= 5; i++)
    {
        int * tab = new int[i];

        for (int j = 0; j < i; ++j)
        {
            tab[j] = j;
        }

        std::cout << "Taille = " << i << std::endl;
        for (int j = 0; j < i; ++j)
        {
            std::cout << tab[j] << std::endl;
        }

        delete[] tab;
    }
    
}