#include <stdio.h>
#include <cstdint>

typedef struct s
{
    int x, y, z, w;
} S;

void Func1(int a)
{
    printf("Func1 - id: a, value:%d, address:%x, size:%d\n", a, &a, sizeof(a));
}

void Func2(int &a)
{
    printf("Func2 - id: a, value:%d, address:%x, size:%d\n", a, &a, sizeof(a));
}

void Func3(int *tab)
{
    printf("Func3 - id: tab, value:%d, address:%x, size:%d\n", tab[0], &(tab[0]),

           sizeof(tab[0]));
}

void Increment(S *ps)
{
    (*ps).x++;
}

int main()
{
    int a = 0;
    printf("main - id: a, value:%d, address:%p, size:%zu\n", a, (void *)&a, sizeof(a));

    int b = 1;
    int c = 2;
    int d = 3;
    printf("a->b address position difference:%td\n", (intptr_t)&b - (intptr_t)&a);
    printf("b->c address position difference:%td\n", (intptr_t)&c - (intptr_t)&b);
    printf("c->d address position difference:%td\n", (intptr_t)&d - (intptr_t)&c);

    Func1(a);

    int &e = a;
    printf("main - id: e, value:%d, address:%x, size:%d\n", e, &e, sizeof(e));

    Func2(a);

    int tab[2] = {5, 10};
    printf("main - id: tab, value:%x, address:%x, size:%d\n", tab, &(tab), sizeof(tab));

    printf("main - id: tab[0], value:%d, address:%x, size:%d\n", tab[0], &(tab[0]),
           sizeof(tab[0]));
    printf("main - id: *(tab), value:%d, address:%x, size:%d\n", *tab, tab,
           sizeof(*tab));

    printf("main - id: tab[1], value:%d, address:%x, size:%d\n", tab[1], &(tab[1]),
           sizeof(tab[1]));
    printf("main - id: *(tab + 1), value:%d, address:%x, size:%d\n", *(tab + 1), tab + 1,
           sizeof(*(tab + 1)));

    int *ptab = tab;
    printf("main - id: ptab[0], value:%d, address:%x, size:%d\n", ptab[0], &(ptab[0]),
           sizeof(ptab[0]));

    Func3(tab);

    int *tab2 = new int[10];
    printf("main - id: tab2, value:%x, address:%x, size:%d\n", tab2, &tab2,
           sizeof(tab2));
    tab2[0] = 15;
    printf("main - id: tab2[0], value:%d, address:%x, size:%d\n", tab2[0], &(tab2[0]),
           sizeof(tab2[0]));

    int *previous = tab2;
    for (int i = 0; i < 10; ++i)
    {
        tab2 = new int[i];
        printf("previous->tab2 address position difference:%d\n", (intptr_t)tab2 -

                                                                      (intptr_t)previous);

        previous = tab2;
    }

    S *ps = new S;
    printf("main - id: ps, value:%x, address:%x, size:%d\n", ps, &ps, sizeof(ps));
    printf("main - id: (*ps), address:%x, size:%d\n", &(*ps), sizeof(*ps));

    (*ps).x = 20;
    Increment(ps);
    printf("main - id: (*ps).x, value:%d\n", (*ps).x);
}