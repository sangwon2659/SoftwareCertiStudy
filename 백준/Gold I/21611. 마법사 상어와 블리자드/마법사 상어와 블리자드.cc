/*
[3시간 15분]
개빡구현 문제
딱히 어려운 부분은 없었음
queue를 써서 채우고 지우고 하는 식으로 구현함

s랑 d를 거꾸로 받아서 디버깅 고생함... 계속 집중력이 딸려서 이런 실수를 하는 듯
문제를 더 천천히 잘 읽어야 한다

코드를 너무 길게 짜다보니 중간에 언제 Break를 걸어줘야 할지 헷갈리는 경우 많았음...
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>

using namespace std;

struct Pos
{
    int y;
    int x;
};

//ifstream txt_input("input.txt");
int N;
int numMagic;
int grid[50][50] = {0};
int tempGrid[50][50] = {0};

int dy[4] = {0, 1, 0, -1};
int dx[4] = {-1, 0, 1, 0};

int sumExplodeMarble1 = 0;
int sumExplodeMarble2 = 0;
int sumExplodeMarble3 = 0;

int ReturnMappedDir(const int& dir)
{
    if (dir == 1)
    {
        return 3;
    }
    else if (dir == 2)
    {
        return 1;
    }
    else if (dir == 3)
    {
        return 0;
    }
    else
    {
        return 2;
    }
}

void ShatterIce(const int& dist, const int& dir)
{
    int sharkPosy = N / 2;
    int sharkPosx = N / 2;

    for (int s = 1; s < dist + 1; s++)
    {
        int targetR = sharkPosy + (s * dy[dir]);
        int targetC = sharkPosx + (s * dx[dir]);

        if (targetR < 0 || targetR >= N || targetC < 0 || targetC >= N)
        {
            continue;
        }

        grid[targetR][targetC] = 0;
    }
}

bool isExistEmptySpot()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; r++)
        {
            if (grid[r][c] == 0)
            {
                return true;
            }
        }
    }

    return false;
}

void RepositionMarble()
{
    Pos nowPos;
    nowPos.y = N / 2;
    nowPos.x = N / 2;
    int stepSize = 1;
    int dir = 40000;
    queue<int> marbleContainer;

    bool cont = true;
    while (cont)
    {
        for (int iter = 0; iter < 2; iter++)
        {
            if (cont)
            {
                for (int step = 0; step < stepSize; step++)
                {
                    nowPos.y += dy[dir % 4];
                    nowPos.x += dx[dir % 4];

                    if (nowPos.x < 0)
                    {
                        cont  = false;
                        break;
                    }

                    if (grid[nowPos.y][nowPos.x] > 0)
                    {
                        marbleContainer.push(grid[nowPos.y][nowPos.x]);
                    }
                }

                dir++;
            }
        }

        stepSize++;
    }

    nowPos.y = N / 2;
    nowPos.x = N / 2;
    stepSize = 1;
    dir = 40000;
    memcpy(grid, tempGrid, 50 * 50 * sizeof(int));

    cont = true;
    while (cont)
    {
        for (int iter = 0; iter < 2; iter++)
        {
            if (cont)
            {
                for (int step = 0; step < stepSize; step++)
                {
                    nowPos.y += dy[dir % 4];
                    nowPos.x += dx[dir % 4];

                    if (marbleContainer.empty())
                    {
                        cont  = false;
                        break;
                    }

                    grid[nowPos.y][nowPos.x] = marbleContainer.front();
                    marbleContainer.pop();
                }

                dir++;
            }
        }

        stepSize++;
    }
}

bool ExplodeMarble()
{
    bool ret = false;
    Pos nowPos;
    nowPos.y = N / 2;
    nowPos.x = N / 2;
    int stepSize = 1;
    int dir = 40000;
    queue<int> marbleContainer;
    queue<int> tempMarbleContainer;

    bool cont = true;
    while (cont)
    {
        for (int iter = 0; iter < 2; iter++)
        {
            if (cont)
            {
                for (int step = 0; step < stepSize; step++)
                {
                    if (!cont)
                    {
                        break;
                    }

                    nowPos.y += dy[dir % 4];
                    nowPos.x += dx[dir % 4];

                    if (nowPos.x < 0 || grid[nowPos.y][nowPos.x] == 0)
                    {
                        cont  = false;
                    }

                    if (tempMarbleContainer.empty())
                    {
                        tempMarbleContainer.push(grid[nowPos.y][nowPos.x]);
                    }
                    else if (tempMarbleContainer.front() == grid[nowPos.y][nowPos.x])
                    {
                        tempMarbleContainer.push(grid[nowPos.y][nowPos.x]);
                    }
                    else if (tempMarbleContainer.front() != grid[nowPos.y][nowPos.x] && tempMarbleContainer.size() < 4)
                    {
                        while(!tempMarbleContainer.empty())
                        {
                            marbleContainer.push(tempMarbleContainer.front());
                            tempMarbleContainer.pop();
                        }

                        tempMarbleContainer.push(grid[nowPos.y][nowPos.x]);
                    }
                    else if (tempMarbleContainer.front() != grid[nowPos.y][nowPos.x] && tempMarbleContainer.size() >= 4)
                    {
                        switch (tempMarbleContainer.front())
                        {
                            case 1:
                                sumExplodeMarble1 += tempMarbleContainer.size();
                                break;
                            case 2:
                                sumExplodeMarble2 += tempMarbleContainer.size();
                                break;
                            case 3:
                                sumExplodeMarble3 += tempMarbleContainer.size();
                                break;
                        }

                        while(!tempMarbleContainer.empty())
                        {
                            tempMarbleContainer.pop();
                        }

                        tempMarbleContainer.push(grid[nowPos.y][nowPos.x]);
                        ret = true;
                    }
                }

                dir++;
            }
        }

        stepSize++;
    }

    nowPos.y = N / 2;
    nowPos.x = N / 2;
    stepSize = 1;
    dir = 40000;
    memcpy(grid, tempGrid, 50 * 50 * sizeof(int));

    cont = true;
    while (cont)
    {
        for (int iter = 0; iter < 2; iter++)
        {
            if (cont)
            {
                for (int step = 0; step < stepSize; step++)
                {
                    nowPos.y += dy[dir % 4];
                    nowPos.x += dx[dir % 4];

                    if (marbleContainer.empty())
                    {
                        cont  = false;
                        break;
                    }

                    grid[nowPos.y][nowPos.x] = marbleContainer.front();
                    marbleContainer.pop();
                }

                dir++;
            }
        }

        stepSize++;
    }

    return ret;
}

void EvolveMarble()
{
    Pos nowPos;
    nowPos.y = N / 2;
    nowPos.x = N / 2;
    int stepSize = 1;
    int dir = 40000;
    queue<int> marbleContainer;
    queue<int> tempMarbleContainer;

    bool cont = true;
    while (cont)
    {
        for (int iter = 0; iter < 2; iter++)
        {
            if (cont)
            {
                for (int step = 0; step < stepSize; step++)
                {
                    if (!cont)
                    {
                        break;
                    }

                    nowPos.y += dy[dir % 4];
                    nowPos.x += dx[dir % 4];

                    if (nowPos.x < 0 || grid[nowPos.y][nowPos.x] == 0)
                    {
                        cont  = false;
                    }

                    if (tempMarbleContainer.empty())
                    {
                        tempMarbleContainer.push(grid[nowPos.y][nowPos.x]);
                    }
                    else if (tempMarbleContainer.front() == grid[nowPos.y][nowPos.x])
                    {
                        tempMarbleContainer.push(grid[nowPos.y][nowPos.x]);
                    }
                    else if (tempMarbleContainer.front() != grid[nowPos.y][nowPos.x])
                    {
                        marbleContainer.push(tempMarbleContainer.size());
                        marbleContainer.push(tempMarbleContainer.front());

                        while(!tempMarbleContainer.empty())
                        {
                            tempMarbleContainer.pop();
                        }

                        tempMarbleContainer.push(grid[nowPos.y][nowPos.x]);
                    }
                }

                dir++;
            }
        }

        stepSize++;
    }

    nowPos.y = N / 2;
    nowPos.x = N / 2;
    stepSize = 1;
    dir = 40000;
    memcpy(grid, tempGrid, 50 * 50 * sizeof(int));

    cont = true;
    while (cont)
    {
        for (int iter = 0; iter < 2; iter++)
        {
            if (cont)
            {
                for (int step = 0; step < stepSize; step++)
                {
                    nowPos.y += dy[dir % 4];
                    nowPos.x += dx[dir % 4];

                    if (marbleContainer.empty() || nowPos.x < 0)
                    {
                        cont  = false;
                        break;
                    }

                    grid[nowPos.y][nowPos.x] = marbleContainer.front();
                    marbleContainer.pop();
                }

                dir++;
            }
        }

        stepSize++;
    }
}

int main()
{
    cin >> N >> numMagic;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            cin >> grid[r][c];
        }
    }

    for (int i = 0; i < numMagic; i++)
    {
        int dist, dir;
        cin >> dir >> dist;
        dir = ReturnMappedDir(dir);
        
        ShatterIce(dist, dir);
        RepositionMarble();
        while (ExplodeMarble())
        {
            continue;
        }

        EvolveMarble();
    }

    cout << sumExplodeMarble1 + (2  * sumExplodeMarble2) + (3 * sumExplodeMarble3);

    return 0;
}
