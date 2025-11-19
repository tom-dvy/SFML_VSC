#ifndef LIST_H
#define LIST_H

class List
{
public:
    List();

    struct Element {
        Element* previous;
        Element* next;
        char value;
    };

    struct sListe {
        Element* first;
        int count;
    };

    sListe* CreateList();

    Element* GetElementAt(sListe* liste, int position);

    void AddElement(sListe* liste, char value);

    void RemoveElementAt(sListe* liste, int removePosition);
};

#endif // LIST_H
