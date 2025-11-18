#include <iostream>
#include <windows.h>
#include <list>
#include <string>

void AfficherNains(const std::list<std::string> &nains)
{
    std::cout << "Les nains sont : ";
    for (const std::string &nain : nains)
    {
        std::cout << nain << ", ";
    }
    std::cout << std::endl;
}

void AfficherNainsPartie(const std::list<std::string> &nains, const std::string &partie)
{
    std::cout << "Les nains dont le nom se termine par : - " << partie << " sont :" << std::endl;
    for (const std::string &nain : nains)
    {
        if (nain.size() >= partie.size())
        {
            std::string fin = nain.substr(nain.size() - 2, partie.size());

            if (fin == partie)
            {
                std::cout << nain << std::endl;
            }
        }
    }
}

void AfficherPlusLongNom(const std::list<std::string> &nains)
{
    std::string plusLongNom;
    for (const std::string &nain : nains)
    {
        if (nain.length() > plusLongNom.length())
        {
            plusLongNom = nain;
        }
    }
    std::cout << "Le nain avec le plus long nom est : " << plusLongNom << std::endl;
}

int main()
{
    std::list<std::string> nameNain = {
        "Balin", "Bifur", "Bofur", "Bombur", "Dori", "Dwalin", "Fili", "Gloin", "Kili", "Nori", "Oin", "Ori", "Thorin", "Bilbo"};

    nameNain.pop_back();

    //AfficherNains(nameNain);
    AfficherNainsPartie(nameNain, "in");
    AfficherPlusLongNom(nameNain);


    return 0;
}