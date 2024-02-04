/*
Combination & Permutation 공부하고 새로 풀었음
전형적인 유형이라 복습 필수
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <cstring>

using namespace std;

struct Pos
{
    int y;
    int x;
};

ifstream txt_input("input.txt");
int N, M;
int grid[8][8] = {0};
int tempGrid[8][8] = {0};
vector<Pos> virusVector;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int maxCount = 0;

void SpreadVirus()
{
    memcpy(tempGrid, grid, 8*8*sizeof(int));

    for (auto nowVirus : virusVector)
    {    
        bool bVisited[8][8] = {0};
        queue<Pos> q;
        q.push({nowVirus.y, nowVirus.x});
        
        while (!q.empty())
        {
            Pos nowPos = q.front();
            q.pop();

            if (bVisited[nowPos.y][nowPos.x])
            {
                continue;
            }

            tempGrid[nowPos.y][nowPos.x] = 2;
            bVisited[nowPos.y][nowPos.x] = true;

            for (int dir = 0; dir < 4; dir++)
            {
                int targetR = nowPos.y + dy[dir];
                int targetC = nowPos.x + dx[dir];

                if (targetR < 0 || targetR >= N || targetC < 0 || targetC >= M)
                {
                    continue;
                }

                if (tempGrid[targetR][targetC] == 0)
                {
                    q.push({targetR, targetC});
                }
            }
        }
    }
}

int CountSafe()
{
    int sumSafe = 0;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            if (tempGrid[r][c] == 0)
            {
                sumSafe++;
            }
        }
    }

    return sumSafe;
}

void MakeWall(const int& count)
{
    if (count == 3)
    {
        SpreadVirus();

        int countSafe = CountSafe();
        if (countSafe > maxCount)
        {
            maxCount = countSafe; 
        }

        return;
    }

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            if (grid[r][c] == 0)
            {
                grid[r][c] = 1;
                MakeWall(count + 1);
                grid[r][c] = 0;
            }
        }
    }
}

int main()
{
    txt_input >> N >> M;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            txt_input >> grid[r][c];

            if (grid[r][c] == 2)
            {
                virusVector.push_back({r, c});
            }
        }
    }

    MakeWall(0);
    cout << maxCount;

    return 0;
}
