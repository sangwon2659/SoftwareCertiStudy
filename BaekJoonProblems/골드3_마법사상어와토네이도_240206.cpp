/*
Mac OS에서 cpp 돌리는 거 환경 편하게 만드는 것 때문에 한참 고생함
문제는 무난하게 풀림
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;

struct Status
{
    int y;
    int x;
    int dir;
};

ifstream txt_input("input.txt");
int N;
int grid[500][500];
int dy[4] = {0, 1, 0, -1};
int dx[4] = {-1, 0, 1, 0};
float ratioMapWest[5][5] =
{
    {0, 0, 0.02, 0, 0},
    {0, 0.1, 0.07, 0.01},
    {0.05, 0, 0, 0, 0},
    {0, 0.1, 0.07, 0.01, 0},
    {0, 0, 0.02, 0, 0}
};
float ratioMap[4][5][5] = {0};
int totalSandOut = 0;
Status tornadoStatus;

void CreateRotateRatioMap()
{
    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            ratioMap[0][r][c] = ratioMapWest[r][c];
            ratioMap[1][r][c] = ratioMapWest[c][5 - r - 1];
            ratioMap[3][r][c] = ratioMapWest[5 - c - 1][r];
        }
    }

    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            ratioMap[2][r][c] = ratioMap[1][c][5 - r - 1];
        }
    }
}

void SpreadWind(const Status& tornadoStatus)
{
    int nowSandOut = 0;
    int sandLeft = grid[tornadoStatus.y][tornadoStatus.x];
    int dir = tornadoStatus.dir % 4;

    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            int sandOnTarget = grid[tornadoStatus.y][tornadoStatus.x] * ratioMap[dir][r][c];

            if (tornadoStatus.y + r - 2 < 0 || tornadoStatus.y + r - 2 >= N ||
            tornadoStatus.x + c - 2 < 0 || tornadoStatus.x + c - 2 >= N)
            {
                nowSandOut += sandOnTarget;
            }
            else
            {
                grid[tornadoStatus.y + r - 2][tornadoStatus.x + c - 2] += sandOnTarget;
            }

            sandLeft -= sandOnTarget;
        }
    }

    if (tornadoStatus.y + dy[dir] < 0 || tornadoStatus.y + dy[dir] >= N ||
    tornadoStatus.x + dx[dir] < 0 || tornadoStatus.x + dx[dir] >= N)
    {
        nowSandOut += sandLeft;
    }
    else
    {
        grid[tornadoStatus.y + dy[dir]][tornadoStatus.x + dx[dir]] += sandLeft;
    }
    
    grid[tornadoStatus.y][tornadoStatus.x] = 0;
    totalSandOut += nowSandOut;
}

int main()
{
    txt_input >> N;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            txt_input >> grid[r][c];
        }
    }
    tornadoStatus.y = (int)(N / 2);
    tornadoStatus.x = (int)(N / 2);
    tornadoStatus.dir = 40000;

    CreateRotateRatioMap();

    int stepSize = 1;
    bool cont = true;
    while (cont)
    {
        for (int iter = 0; iter < 2; iter++)
        {
            for (int step = 0; step < stepSize; step++)
            {
                int dir = tornadoStatus.dir % 4;

                tornadoStatus.y += dy[dir];
                tornadoStatus.x += dx[dir];

                if (tornadoStatus.y < 0 || tornadoStatus.x < 0)
                {
                    cont = false;
                    break;
                }
                SpreadWind(tornadoStatus);
            }

            tornadoStatus.dir++;
        }

        stepSize++;
    }

    cout << totalSandOut;

    return 0;
}
