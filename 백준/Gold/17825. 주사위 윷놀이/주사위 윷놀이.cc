#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Status
{
    int y;
    int x;
    int dir;
};

int grid[9][21] = {0};
int diceContainer[10];
int dy[2] = {0, 1};
int dx[2] = {1, 0};
int bestScore = 0;
vector<Status> horseContainer(4);
bool bHorseAlive[4] = {1, 1, 1, 1};
vector<int> track;

Status FindMoveHorseCandidateLocation(const Status& horse, const int& diceIdx)
{
    int targetR, targetC, dir = 0;

    if (horse.x == 5 || horse.x == 10 || horse.x == 15)
    {
        dir = 1;
    }

    targetR = horse.y + (diceContainer[diceIdx] * dy[dir]);
    targetC = horse.x + (diceContainer[diceIdx] * dx[dir]);

    return {targetR, targetC, dir};
}

bool isHorseOnCandidateLocation(const Status& horseMoveCandidate)
{
    for (int idx = 0; idx < 4; idx++)
    {
        if (!bHorseAlive[idx]) continue;

        if ((grid[horseContainer[idx].y][horseContainer[idx].x] == 40 && grid[horseMoveCandidate.y][horseMoveCandidate.x] == 40)
        || (grid[horseContainer[idx].y][horseContainer[idx].x] == 25 && grid[horseMoveCandidate.y][horseMoveCandidate.x] == 25)
        || ((horseContainer[idx].y != 1 && horseMoveCandidate.y != 1) &&
            (grid[horseContainer[idx].y][horseContainer[idx].x] == 30 && grid[horseMoveCandidate.y][horseMoveCandidate.x] == 30))
        || (grid[horseContainer[idx].y][horseContainer[idx].x] == 35 && grid[horseMoveCandidate.y][horseMoveCandidate.x] == 35))
        {
            return true;
        }

        if (horseContainer[idx].y == horseMoveCandidate.y && horseContainer[idx].x == horseMoveCandidate.x) return true;
    }

    return false;
}

void Permutation(const int& score, const int& diceIdx)
{
    if (diceIdx == 10)
    {
        return;
    }

    vector<Status> saveHorseContainer = horseContainer;

    for (int horseIdx = 0; horseIdx < 4; horseIdx++)
    {
        if (!bHorseAlive[horseIdx]) continue;

        Status horseMoveCandidate = FindMoveHorseCandidateLocation(horseContainer[horseIdx], diceIdx);

        if (isHorseOnCandidateLocation(horseMoveCandidate)) continue;

        if (horseMoveCandidate.x == 10 && horseMoveCandidate.y > 7
        || horseMoveCandidate.y > 8 || horseMoveCandidate.x > 20)
        {
            bHorseAlive[horseIdx] = false;
            track.push_back(horseIdx);
            Permutation(score, diceIdx + 1);
        }
        else
        {
            horseContainer[horseIdx].y = horseMoveCandidate.y;
            horseContainer[horseIdx].x = horseMoveCandidate.x;
            horseContainer[horseIdx].dir = horseMoveCandidate.dir;

            track.push_back(horseIdx);

            if (score + grid[horseContainer[horseIdx].y][horseContainer[horseIdx].x] > bestScore)
            {
                bestScore = score + grid[horseContainer[horseIdx].y][horseContainer[horseIdx].x];
                
                /*
                for (int i = 0; i < track.size(); i++)
                {
                    cout << (track[i] + 1) << " ";
                }
                cout << "bestscore: " << bestScore <<endl;
                */
            }

            Permutation(score + grid[horseContainer[horseIdx].y][horseContainer[horseIdx].x], diceIdx + 1);
        }

        track.erase(track.end() - 1);

        bHorseAlive[horseIdx] = true;
        horseContainer = saveHorseContainer;
    }
}

int main()
{
    for (int i = 1; i <= 20; i++)
    {
        grid[1][i] = i * 2;
    }

    grid[2][5] = 13;
    grid[3][5] = 16;
    grid[4][5] = 19;
    grid[5][5] = 25;
    grid[6][5] = 30;
    grid[7][5] = 35;
    grid[8][5] = 40;

    grid[2][10] = 22;
    grid[3][10] = 24;
    grid[4][10] = 25;
    grid[5][10] = 30;
    grid[6][10] = 35;
    grid[7][10] = 40;

    grid[2][15] = 28;
    grid[3][15] = 27;
    grid[4][15] = 26;
    grid[5][15] = 25;
    grid[6][15] = 30;
    grid[7][15] = 35;
    grid[8][15] = 40;

    //ifstream txt_input("input.txt");
    for (int idx = 0; idx < 10; idx++)
    {
        cin >> diceContainer[idx];
    }

    for (int i = 0; i < 4; i++)
    {
        horseContainer[i].y = 1;
    }

    Permutation(0, 0);

    cout << bestScore;

    return 0;
}