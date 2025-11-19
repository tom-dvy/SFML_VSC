#include "List.h"
#include <iostream>

int main()
{
    List myList;
    List::sListe* liste = myList.CreateList();

    std::cout << "Liste créée" << std::endl;

    myList.AddElement(liste, 'A');
    myList.AddElement(liste, 'B');
    myList.AddElement(liste, 'C');

    myList.GetElementAt(liste, 0);
    myList.GetElementAt(liste, 1);
    myList.GetElementAt(liste, 2);

    myList.RemoveElementAt(liste,2);

    myList.DestroyList(liste);

    return 0;
}