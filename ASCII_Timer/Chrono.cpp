#include <iostream>
#include <time.h>
#include <windows.h>
#include <cmath>

struct Chrono
{
    int duration;
    float elapsedTime;
    bool isFinished;
};

char tab[11][11] = {};

int AskDuration()
{
    int duration;
    std::cout << "Saisis la durée du chrono (en secondes) : ";
    std::cin >> duration;
    if (duration <= 0)
    {
        std::cout << "Durée invalide, saisir un nombre positif " << std::endl;
        return AskDuration();
    }
    else
    {
        return duration;
    }
}

float GetTime()
{
    float timeInSeconds = clock() / (float)CLOCKS_PER_SEC;
    return timeInSeconds;
}

void UpdateChrono(Chrono &chrono, float deltaTime)
{

    chrono.elapsedTime += deltaTime;

    if (chrono.elapsedTime >= chrono.duration)
        chrono.isFinished = true;
}

void InitializeOutput()
{
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            tab[i][j] = '-';
            if (tab[5][5])
            {
                tab[5][5] = 'X';
            }
            if (j == 5 && i < 5 && i > 0)
            {
                tab[i][j] = '|';
            }
        }
    }
}

void DisplayOutput()
{
    std::string caracteres = "Bonjour !";
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            std::cout << tab[i][j];
        }
        std::cout << std::endl;
    }
}

void ResetDisplay()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hConsole, pos);
}

void WriteSecond(Chrono &chrono)
{

    int posX = ((int)(chrono.elapsedTime * 11)) % 11;

    for (int x = 0; x < 11; x++)
        tab[x][0] = ' ';

    tab[posX][0] = '0';
}

void WriteTimeLeft(Chrono &chrono)
{
    double PI = 3.14159265358979323846;

    for (int y = 0; y < 11; y++)
        for (int x = 0; x < 11; x++)
            tab[x][y] = ' ';

    int posX = (int)((cos(chrono.elapsedTime * 2 * PI / chrono.duration - PI / 2) * 3) + 5.5f);
    int posY = (int)((sin(chrono.elapsedTime * 2 * PI / chrono.duration - PI / 2) * 3) + 5.5f);

    tab[posX][posY] = '*';
}

void WriteChrono(Chrono &chrono)
{
    WriteSecond(chrono);
    WriteTimeLeft(chrono);
}

int main()
{
    std::cout << "Chrono running..." << std::endl;

    std::cout << "-------------------------" << std::endl;
    int duration = AskDuration();
    std::cout << "Durée du chrono : " << duration << " secondes" << std::endl;

    std::cout << "-------------------------" << std::endl;
    float currentTime = GetTime();

    Chrono chrono;
    chrono.duration = duration;
    chrono.elapsedTime = 0.0f;
    chrono.isFinished = false;

    InitializeOutput();
    DisplayOutput();

    system("cls");

    while (chrono.isFinished == false)
    {
        float newTime = GetTime();
        float deltaTime = newTime - currentTime;
        currentTime = newTime;

        UpdateChrono(chrono, deltaTime);

        ResetDisplay();

        WriteChrono(chrono);
        DisplayOutput();
    }
    std::cout << "Fin du chrono ! /[^_^]/" << std::endl;

    return 0;
}