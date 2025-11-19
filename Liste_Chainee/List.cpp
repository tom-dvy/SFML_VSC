#include "List.h"
#include <iostream>

List::List() 
{
    std::cout << "Constructeur appelé" << std::endl;
}

List::sListe* List::CreateList() 
{
    sListe* liste = new sListe;
    liste->first = nullptr;
    liste->count = 0;
    return liste;
}