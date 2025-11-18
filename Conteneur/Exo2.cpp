#include <iostream>
#include <map>
#include <string>

int main()
{
    std::map<std::string, int> AnimalsNames = {
        {"Chat", 4},
        {"Humain", 2},
        {"Araignée", 8},
        {"Chien", 4},
        {"Dodo", 2},
        {"Mouton", 4},
        {"Serpent", 0}};

    std::map<std::string, int>::iterator found1 = AnimalsNames.find("Humain");
    std::map<std::string, int>::iterator found2 = AnimalsNames.find("Licorne");

    std::cout << "Nom : " << (found1 == AnimalsNames.end() ? "Non trouvé" : (*found1).first) << std::endl;
    std::cout << "Pattes : " << (found1 == AnimalsNames.end() ? 0 : (*found1).second) << std::endl;

    std::cout << "Nom : " << (found2 == AnimalsNames.end() ? "Non trouvé" : (*found2).first) << std::endl;
    std::cout << "Pattes : " << (found2 == AnimalsNames.end() ? 0 : (*found2).second) << std::endl;

    AnimalsNames.erase("Dodo");

    // Ajoute une patte au mouton
    std::map<std::string, int>::iterator found = AnimalsNames.find("Mouton");
    (*found).second++;
    std::cout << "Nom : " << (*found).first << std::endl;
    std::cout << "Pattes : " << (*found).second << std::endl;

    return 0;
}