/*
[1시간 30분]
문제를 자꾸 이해 못 해서 다르게 구현하는 바람에 좀 해맴...
주사위의 이동방향만 바꿔서 그대로 굴리면 되는 건데, 처음에 굳이 그 자리에서 실제로 회전을 하게끔 만들어서 좀 고생함
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Status
{
    int y;
    int x;
    int dir;
};
ifstream txt_input("input.txt");
int N, M;
int movementNum;
Status Dice;
int numDice[6] = {1, 2, 3, 4, 5, 6};
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int grid[20][20] = {0};
bool bVisited[20][20] = {0};
int totalScore = 0;

void RollDice(const int& dir)
{
    int tempNumDice[6] = {0};

    switch (dir)
    {
        // North
        case 0:
            tempNumDice[0] = numDice[4];
            tempNumDice[1] = numDice[0];
            tempNumDice[2] = numDice[2];
            tempNumDice[3] = numDice[3];
            tempNumDice[4] = numDice[5];
            tempNumDice[5] = numDice[1];
            break;
        // East
        case 1:
            tempNumDice[0] = numDice[3];
            tempNumDice[1] = numDice[1];
            tempNumDice[2] = numDice[0];
            tempNumDice[3] = numDice[5];
            tempNumDice[4] = numDice[4];
            tempNumDice[5] = numDice[2];
            break;
        // South
        case 2:
            tempNumDice[0] = numDice[1];
            tempNumDice[1] = numDice[5];
            tempNumDice[2] = numDice[2];
            tempNumDice[3] = numDice[3];
            tempNumDice[4] = numDice[0];
            tempNumDice[5] = numDice[4];
            break;
        // West
        case 3:
            tempNumDice[0] = numDice[2];
            tempNumDice[1] = numDice[1];
            tempNumDice[2] = numDice[5];
            tempNumDice[3] = numDice[0];
            tempNumDice[4] = numDice[4];
            tempNumDice[5] = numDice[3];
            break;
    }

    memcpy(numDice, tempNumDice, 6 * sizeof(int));
}

void SumScore(const int& initNum, const int& nowR, const int& nowC)
{
    if (grid[nowR][nowC] == initNum)
    {
        bVisited[nowR][nowC] = true;
        totalScore += initNum;
    }

    for (int dir = 0; dir < 4; dir++)
    {
        int targetR = nowR + dy[dir];
        int targetC = nowC + dx[dir];

        if (targetR < 0 || targetR >= N || targetC < 0 || targetC >= M || bVisited[targetR][targetC])
        {
            continue;
        }

        if (grid[targetR][targetC] == initNum)
        {
            SumScore(initNum, targetR, targetC);
        }
    }
}

void InitVisited()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            bVisited[r][c] = false;
        }
    }
}

int main()
{
    txt_input >> N >> M >> movementNum;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            txt_input >> grid[r][c];
        }
    }

    Dice.y = 0;
    Dice.x = 0;
    Dice.dir = 40001;

    for (int iter = 0; iter < movementNum; iter++)
    {
        int targetR = Dice.y + dy[Dice.dir % 4];
        int targetC = Dice.x + dx[Dice.dir % 4];

        if (targetR < 0 || targetR >= N || targetC < 0 || targetC >= M)
        {
            Dice.dir += 2;

            Dice.y += dy[Dice.dir % 4];
            Dice.x += dx[Dice.dir % 4];
            RollDice(Dice.dir % 4);

            InitVisited();
            SumScore(grid[Dice.y][Dice.x], Dice.y, Dice.x);
        }
        else
        {
            Dice.y = targetR;
            Dice.x = targetC;
            RollDice(Dice.dir % 4);

            InitVisited();
            SumScore(grid[Dice.y][Dice.x], Dice.y, Dice.x);
        }

        if (numDice[5] > grid[Dice.y][Dice.x])
        {
            Dice.dir++;
        }
        else if (numDice[5] < grid[Dice.y][Dice.x])
        {
            Dice.dir--;
        }
    }

    cout << totalScore;

    return 0;
}
