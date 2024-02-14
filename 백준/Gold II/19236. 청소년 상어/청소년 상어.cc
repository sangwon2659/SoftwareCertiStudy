/*
[3시간 30분]
DFS를 돌릴 때 매번 grid를 원래 상태로 돌려놓으면서 돌려야 하는 부분을 생각하지 않고 짜서 좀 고생했다
문제를 처음 보고 어떻게 설계를 할지 제대로 생각을 한 후 코드 작성을 시작하자
+ DFS를 돌릴 때 상어가 격자를 벗어나는 경우 때 continue가 아닌 break를 해서 모두의 경우의 수를 탐색하지 못 하는 버그가 있었다
  (이걸 통해 초기 설계의 중요성을 더욱 느낌)
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Info
{
    int y;
    int x;
    int dir;
    bool isAlive = true;
};

const int GRID_SIZE = 4;
const int NUM_FISH = 16;

int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int totalFishID = 0;
int grid[GRID_SIZE][GRID_SIZE];
Info shark;
vector<Info> vectorFish(NUM_FISH + 1);

int initShark()
{
    shark.y = 0;
    shark.x = 0;
    shark.dir = vectorFish[grid[0][0]].dir;

    int initID = grid[0][0];
    vectorFish[grid[0][0]].isAlive = false;
    grid[0][0] = 0;

    return initID;
}

void SwitchFishPosition(const int& fishAIdx, const int& fishBIdx)
{
    swap(grid[vectorFish[fishAIdx].y][vectorFish[fishAIdx].x], grid[vectorFish[fishBIdx].y][vectorFish[fishBIdx].x]);
    
    int tempY, tempX, tempDir;
    tempY = vectorFish[fishAIdx].y;
    tempX = vectorFish[fishAIdx].x;

    vectorFish[fishAIdx].y = vectorFish[fishBIdx].y;
    vectorFish[fishAIdx].x = vectorFish[fishBIdx].x;

    vectorFish[fishBIdx].y = tempY;
    vectorFish[fishBIdx].x = tempX;
}

void MoveFish()
{
    for (int fishIdx = 1; fishIdx < NUM_FISH + 1; fishIdx++)
    {
        if (vectorFish[fishIdx].isAlive)
        {
            int targetR = vectorFish[fishIdx].y + dy[vectorFish[fishIdx].dir % 8];
            int targetC = vectorFish[fishIdx].x + dx[vectorFish[fishIdx].dir % 8];

            int cnt = 0;
            while (targetR < 0 || targetR >= GRID_SIZE || targetC < 0 || targetC >= GRID_SIZE || (targetR == shark.y  && targetC == shark.x))
            {
                vectorFish[fishIdx].dir++;
                targetR = vectorFish[fishIdx].y + dy[vectorFish[fishIdx].dir % 8];
                targetC = vectorFish[fishIdx].x + dx[vectorFish[fishIdx].dir % 8];
                cnt++;

                if (cnt == 8) break;
            }

            if (cnt == 8) continue;

            int targetFishIdx = grid[targetR][targetC];
            if (targetFishIdx > 0)
            {
                SwitchFishPosition(fishIdx, targetFishIdx);
            }
            else
            {
                grid[vectorFish[fishIdx].y][vectorFish[fishIdx].x] = 0;
                grid[targetR][targetC] = fishIdx;

                vectorFish[fishIdx].y = targetR;
                vectorFish[fishIdx].x = targetC;
            }
        }
    }
}

void DFS(const int& nowSumFishID)
{
    if (nowSumFishID > totalFishID)
    {
        totalFishID = nowSumFishID;
    }

    MoveFish();

    Info nowShark = shark;
    vector<Info> nowVectorFish = vectorFish;
    int nowGrid[GRID_SIZE][GRID_SIZE];

    for (int r = 0; r < GRID_SIZE; r++)
    {
        for (int c = 0; c < GRID_SIZE; c++)
        {
            nowGrid[r][c] = grid[r][c];
        }
    }

    for (int mul = 1; mul < 4; mul++)
    {
        int targetR = shark.y + mul * dy[shark.dir % 8];
        int targetC = shark.x + mul * dx[shark.dir % 8];

        if (targetR < 0 || targetR >= GRID_SIZE || targetC < 0 || targetC >= GRID_SIZE || grid[targetR][targetC] == 0)
        {
            continue;
        }

        shark.y = targetR;
        shark.x = targetC;
        shark.dir = vectorFish[grid[targetR][targetC]].dir;

        int nowFishID = grid[targetR][targetC];
        vectorFish[nowFishID].isAlive = false;
        grid[targetR][targetC] = 0;

        DFS(nowSumFishID + nowFishID);

        shark = nowShark;
        vectorFish = nowVectorFish;
        for (int r = 0; r < GRID_SIZE; r++)
        {
            for (int c = 0; c < GRID_SIZE; c++)
            {
                grid[r][c] = nowGrid[r][c];
            }
        }
    }
}

int main()
{
    int fishID, fishDir;
    const int GRID_SIZE = 4;
    //ifstream txt_input("input.txt");
    for (int r = 0; r < GRID_SIZE; r++)
    {
        for (int c = 0; c < GRID_SIZE; c++)
        {
            cin >> fishID >> fishDir;

            grid[r][c] = fishID;
            
            vectorFish[fishID].y = r;
            vectorFish[fishID].x = c;
            vectorFish[fishID].dir = fishDir + 79999;
        }
    }

    int initID = initShark();
    DFS(initID);

    cout << totalFishID;

    return 0;
}
