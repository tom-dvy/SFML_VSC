#include "List.h"
#include <iostream>

int main()
{
    List myList;
    List::sListe* liste = myList.CreateList();

    std::cout << "Liste créée avec " << liste->count << " éléments" << std::endl;
}