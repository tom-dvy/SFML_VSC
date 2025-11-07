#include <iostream>

float * AllocateSquare(float value)
{
    float * square = new float;
    *square = value * value;
    return square;
}

int main()
{
    float param1 = 5.0f;

    float * square1 = AllocateSquare(param1);

    std::cout << "Adresse de square1 : " << square1 <<std::endl;
    std::cout << "Valeur de square1 : " << *square1 << std::endl;

    param1 *= 2.0f;

    square1 = AllocateSquare(param1);

    std::cout << "Valeur de square1 après multiplication/2 : " << *square1 << std::endl;

    delete square1;
}