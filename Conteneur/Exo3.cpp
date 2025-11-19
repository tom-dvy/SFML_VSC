#include <iostream>
#include <vector>

int main()
{
int nbJoueurs;

// Demande du nombre de joueurs
std::cout << "Choisissez un nombre de joueurs : " << std::endl;
std::cin >> nbJoueurs;
std::cout << "Nombre de joueurs : " << nbJoueurs << std::endl;
std::cout << "---------------------------" << std::endl;


// Création du vecteur de scores pour chaque joueur
std::vector<int> scores(nbJoueurs, 0);

// Création du vecteur à 2 dimensions pour le plateau de jeu
int taillePlateau = 10 + 2 *nbJoueurs;
std::vector<std::vector<bool>> plateauJeu(taillePlateau, std::vector<bool>(taillePlateau, false));

// Ajout d'un joueur
std::cout << "--- Ajout d'un joueur ---" << std::endl;
nbJoueurs++;
scores.push_back(0);
for (auto &ligne : plateauJeu)
{
    ligne.push_back(false);
}

std::cout << "Nombre de joueurs : " << nbJoueurs << std::endl;

}