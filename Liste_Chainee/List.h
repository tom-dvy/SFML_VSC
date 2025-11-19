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
};

#endif // LIST_H
