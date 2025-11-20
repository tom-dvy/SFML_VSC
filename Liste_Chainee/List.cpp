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

List::Element* List::GetElementAt(sListe* liste, int position)
{
    if (position < 0 || position >= liste->count)
    {
        std::cout << "Position invalide : " << position << std::endl;
        return nullptr;
    }

    Element* current = liste->first;

    for (int i = 0; i < position; i++)
    {
        current = current->next;
    }

    std::cout << "Element trouvé à " << position << " : " << current->value << std::endl;
    return current;
}

void List::AddElement(sListe* liste, char value)
{
    Element* elementAdded = new Element;
    elementAdded->value = value;
    elementAdded->next = nullptr;

    if (liste->count == 0)
    {
        elementAdded->previous = nullptr;
        liste->first = elementAdded;
    }
    else
    {
        Element* lastElement = GetElementAt(liste, liste->count - 1);

        lastElement->next = elementAdded;
        elementAdded->previous = lastElement;
    }

    liste->count++;
}

void List::RemoveElementAt(sListe* liste, int removePosition)
{
    Element* removeElement = GetElementAt(liste, removePosition);
    if (removeElement == nullptr)
    {
        return;
    }

    Element* previous = removeElement->previous;
    Element* next = removeElement->next;

    if (previous == nullptr)
    {
        liste->first = next;
    }
    else
    {
        previous->next = next;
    }
    
    if (next != nullptr)
    {
        next->previous = previous;
    }    
    delete removeElement;

    liste->count--;
}

void List::DestroyList(sListe* liste)
{
    Element* current = liste->first;
    
    while (current != nullptr)
    {
        Element* next = current->next;
        delete current;
        current = next;
    }

    delete liste;
}