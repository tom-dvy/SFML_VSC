#include <iostream>

struct Coordinate
{
    int i;
    int j;
};

Coordinate FindHighestAdjacent(int tab[5][5], int size, int i, int j);
Coordinate PathFinder_recursive(int tab[5][5], int size, int i, int j, int moveLeft);

int main()
{
    Coordinate middle = {2, 2};
    std::cout << "Position centrale : (" << middle.i << ", " << middle.j << ")" << std::endl;

    int tab[5][5] = {{0, 8, 7, 1, 5}, {3, 5, 2, 8, 9}, {0, 4, 0, 1, 0}, {2, 4, 3, 6, 1}, {1, 4, 3, 1, 0}};
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            std::cout << tab[i][j] << " ";
        }
        std::cout << std::endl;
    }

    Coordinate coord = FindHighestAdjacent(tab, 5, middle.i, middle.j);
    
    std::cout << "Direction de la plus grande case : (" << coord.i << ", " << coord.j << ")" << std::endl;
    std::cout << "Différence entre les cases : (" << coord.i - middle.i << ", " << coord.j - middle.j << ")" << std::endl;

    Coordinate finalPos = PathFinder_recursive(tab, 5, middle.i, middle.j, 5);
    std::cout << "Position finale après déplacement : (" << finalPos.i << ", " << finalPos.j << ")" << std::endl;
}

Coordinate FindHighestAdjacent(int tab[5][5], int size, int i, int j) 
{
    int maxValue = tab[i][j];
    Coordinate result {i, j};

    // Case Bas
    if (tab[i][j+1] > tab[i][j] && j + 1 < size) 
    {
        maxValue = tab[i][j+1];
        result = {i, j+1};    
    }

    // Case Haut
    if (tab[i][j-1] > tab[i][j] && j - 1 >= 0) 
    {
        maxValue = tab[i][j-1];
        result = {i, j-1};    
    }

    // Case Droite
    if (tab[i+1][j] > tab[i][j] && i + 1 < size) 
    {
        maxValue = tab[i+1][j];
        result = {i+1, j};    
    }

    // Case Gauche
    if (tab[i-1][j] > tab[i][j] && i - 1 >= 0) 
    {
        maxValue = tab[i-1][j];
        result = {i-1, j};    
    }

    return result;
}

Coordinate PathFinder_recursive(int tab[5][5], int size, int i, int j, int moveLeft)
{
    if (moveLeft <= 0)
        return {i, j};

    tab[i][j] = 0;

    Coordinate next = FindHighestAdjacent(tab, size, i, j);
    std::cout << "Déplacement vers : (" << next.i << ", " << next.j << ")" << std::endl;

    if (next.i == i && next.j == j)
        return {i, j};

    if (tab[next.i][next.j] <= 0)
        return {i, j};

    return PathFinder_recursive(tab, size, next.i, next.j, moveLeft - 1);
}