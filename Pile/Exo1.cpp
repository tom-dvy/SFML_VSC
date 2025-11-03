#include <iostream>

void StartTurn_A(int &remainingTurn, int &playerId);
void SwitchPlayer_B(int &remainingTurn, int &playerId);
void TurnLeft_C(int &remainingTurn, int &playerId);

int main()
{
    int remainingTurn = 100;
    int playerId = 0;

    while (remainingTurn > 0)
    {
        StartTurn_A(remainingTurn, playerId);
        SwitchPlayer_B(remainingTurn, playerId);
        TurnLeft_C(remainingTurn, playerId);
    }
    return 0;
}

void StartTurn_A(int &remainingTurn, int &playerId)
{
    std::cout << "Starting turn for player : " << playerId << "." << std::endl;
}

void SwitchPlayer_B(int &remainingTurn, int &playerId)
{
    std::cout << "Player " << playerId << " has played. Switching player." << std::endl;
    playerId = (playerId + 1) % 2;
}

void TurnLeft_C(int &remainingTurn, int &playerId)
{
    --remainingTurn;
    std::cout << "End of turn. " << remainingTurn << " turns left." << std::endl;
}
