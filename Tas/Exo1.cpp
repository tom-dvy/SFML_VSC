#include <iostream>

int a = 5;
int *pa = &a;
int b = 10;
int *pb = &b;
int *pc = nullptr;

int main()
{
    std::cout << "a : " << a << std::endl;
    std::cout << "pa : " << pa << std::endl;
    std::cout << "b : " << b << std::endl;
    std::cout << "pb : " << pb << std::endl;

    std::cout << "*pa : " << *pa << std::endl;
    std::cout << "*pb : " << *pb << std::endl;

    // Échange des pointeurs
    pc = pa;
    pa = pb;
    pb = pc;
    std::cout << "-----------------" << std::endl;
    std::cout << "*pa après échange : " << *pa << std::endl;
    std::cout << "*pb après échange : " << *pb << std::endl;
    std::cout << "-----------------" << std::endl;

    std::cout << "a : " << a << std::endl;
    std::cout << "pa : " << pa << std::endl;
    std::cout << "b : " << b << std::endl;
    std::cout << "pb : " << pb << std::endl;

    std::cout << "*pa : " << *pa << std::endl;
    std::cout << "*pb : " << *pb << std::endl;
}