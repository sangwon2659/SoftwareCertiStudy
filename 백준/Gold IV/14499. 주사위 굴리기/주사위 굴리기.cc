#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;

struct Pos
{
    int y;
    int x;
};

//ifstream txt_input("input.txt");
int N, M;
int numRolls;
int grid[20][20];
Pos Dice;
int diceNum[6] = {0};

int dy[5] = {-10, 0, 0, -1, 1};
int dx[5] = {-10, 1, -1, 0, 0};

void RollDice(const int& dir)
{
    int tempDiceNum[6] = {0};

    switch(dir)
    {
        case 1:
            tempDiceNum[0] = diceNum[3];
            tempDiceNum[1] = diceNum[1];
            tempDiceNum[2] = diceNum[0];
            tempDiceNum[3] = diceNum[5];
            tempDiceNum[4] = diceNum[4];
            tempDiceNum[5] = diceNum[2];
            break;
        case 2:
            tempDiceNum[0] = diceNum[2];
            tempDiceNum[1] = diceNum[1];
            tempDiceNum[2] = diceNum[5];
            tempDiceNum[3] = diceNum[0];
            tempDiceNum[4] = diceNum[4];
            tempDiceNum[5] = diceNum[3];
            break;
        case 3:
            tempDiceNum[0] = diceNum[4];
            tempDiceNum[1] = diceNum[0];
            tempDiceNum[2] = diceNum[2];
            tempDiceNum[3] = diceNum[3];
            tempDiceNum[4] = diceNum[5];
            tempDiceNum[5] = diceNum[1];
            break;
        case 4:
            tempDiceNum[0] = diceNum[1];
            tempDiceNum[1] = diceNum[5];
            tempDiceNum[2] = diceNum[2];
            tempDiceNum[3] = diceNum[3];
            tempDiceNum[4] = diceNum[0];
            tempDiceNum[5] = diceNum[4];
            break;
    }

    memcpy(diceNum, tempDiceNum, 6 * sizeof(int));
}

void CompareDiceAndMap(const Pos& Dice)
{
    if (grid[Dice.y][Dice.x] == 0)
    {
        grid[Dice.y][Dice.x] = diceNum[5];
    }
    else
    {
        diceNum[5] = grid[Dice.y][Dice.x];
        grid[Dice.y][Dice.x] = 0;
    }
}

int main()
{
    cin >> N >> M;
    cin >> Dice.y >> Dice.x;
    cin >> numRolls;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            cin >> grid[r][c];
        }
    }

    int rollDir;
    for (int iter = 0; iter < numRolls; iter++)
    {
        cin >> rollDir;

        int targetR = Dice.y + dy[rollDir];
        int targetC = Dice.x + dx[rollDir];

        if (targetR < 0 || targetR >= N || targetC < 0 || targetC >= M)
        {
            continue;
        }
        else
        {
            Dice.y = targetR;
            Dice.x = targetC;
        }

        RollDice(rollDir);
        cout << diceNum[0] << endl;

        CompareDiceAndMap(Dice);
    }

    return 0;
}