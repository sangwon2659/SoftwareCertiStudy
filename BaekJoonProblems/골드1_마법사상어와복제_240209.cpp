/*
[3시간 30분]
4 x 4 grid라서 for문 신경 안쓰고 막 돌림
tempGrid를 잘 사용해서 Fish를 옮기는 게 중요했음
Shark가 움직이는 경우의 수를 볼 때 bVisited의 경우 제외하는 Fish의 수를 합산하지 않는 게 가장 핵심이었고,
맨 처음에 Shark가 시작하는 지점을 bVisited = true로 잡지 않는 것 또한 핵심이었음
경우의 수가 겹치는 경우 그걸 Int로 바꿔서 가장 작은 숫자를 return하는 경우의 수를 선택하는 부분도 있었음
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

struct SharkPos
{
    int y;
    int x;
};

struct GridPos
{
    vector<int> vectorFish;
    int fishSmell; 
};

ifstream txt_input("input.txt");
int M, S;
const int GRID_SIZE = 4;
GridPos grid[GRID_SIZE][GRID_SIZE];
vector<int> tempCopyGrid[GRID_SIZE][GRID_SIZE];
SharkPos shark;
int maxSumFish = 0;
vector<vector<int>> vectorPathCandidate;
bool bSharkMovePossible;
bool bVisited[GRID_SIZE][GRID_SIZE] = {0};

int dy_fish[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dx_fish[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

int dy_shark[4] = {-1, 0, 1, 0};
int dx_shark[4] = {0, -1, 0, 1};

void InitTempGrid()
{
    for (int r = 0; r < GRID_SIZE; r++)
    {
        for (int c = 0 ; c < GRID_SIZE; c++)
        {
            tempCopyGrid[r][c].clear();
        }
    }
}

void CopyFish()
{
    for (int r = 0; r < GRID_SIZE; r++)
    {
        for (int c = 0; c < GRID_SIZE; c++)
        {
            if (grid[r][c].vectorFish.size() > 0)
            {
                for (auto nowFish : grid[r][c].vectorFish)
                {
                    tempCopyGrid[r][c].push_back(nowFish);
                }
            }
        }
    }
}

void MoveFish()
{
    GridPos tempGrid[GRID_SIZE][GRID_SIZE];

    for (int r = 0; r < GRID_SIZE; r++)
    {
        for (int c = 0; c < GRID_SIZE; c++)
        {
            if (grid[r][c].vectorFish.size() > 0)
            {
                bool bNoOption = true;
                for (int idx = 0; idx < grid[r][c].vectorFish.size(); idx++)
                {
                    int nowFishDir = grid[r][c].vectorFish[idx];

                    for (int iter = 0; iter < 8; iter++)
                    {
                        int targetR = r + dy_fish[nowFishDir % 8];
                        int targetC = c + dx_fish[nowFishDir % 8];

                        if (targetR < 0 || targetR >= GRID_SIZE || targetC < 0 || targetC >= GRID_SIZE || 
                        (targetR == shark.y && targetC == shark.x) || grid[targetR][targetC].fishSmell > 0)
                        {
                            nowFishDir--;
                        }
                        else
                        {
                            tempGrid[targetR][targetC].vectorFish.push_back(nowFishDir);
                            bNoOption = false;
                            break;
                        }
                    }

                    if (bNoOption)
                    {
                        tempGrid[r][c].vectorFish.push_back(nowFishDir);
                    }
                }
            }
        }
    }

    for (int r = 0; r < GRID_SIZE; r++)
    {
        for (int c = 0; c < GRID_SIZE; c++)
        {
            grid[r][c].vectorFish.clear();
            if (tempGrid[r][c].vectorFish.size() > 0)
            {
                grid[r][c].vectorFish = tempGrid[r][c].vectorFish;
            }
        }
    }
}

void ReturnDictionaryResult()
{
    vector<pair<int, int>> vectorIntPathCandidate;

    for (int idx = 0; idx < vectorPathCandidate.size(); idx++)
    {
        vectorIntPathCandidate.push_back({idx, vectorPathCandidate[idx][0] * 100 + vectorPathCandidate[idx][1] * 10 + vectorPathCandidate[idx][2]});
    }

    sort(vectorIntPathCandidate.begin(), vectorIntPathCandidate.end(), [](const pair<int, int>& P1, const pair<int, int>& P2)
    {
        return P1.second < P2.second;
    });
    
    vector<int> vectorSelected = vectorPathCandidate[vectorIntPathCandidate[0].first];
    vectorPathCandidate.clear();
    vectorPathCandidate.push_back(vectorSelected);
}

void ReturnOptimalSharkMovement(const int& r, const int& c, vector<int> vectorDir, int sumFish, const int& count)
{
    if (count == 3)
    {
        if (sumFish > maxSumFish)
        {
            maxSumFish = sumFish;
            vectorPathCandidate.clear();
            vectorPathCandidate.push_back(vectorDir);
        }
        else if (sumFish == maxSumFish)
        {
            vectorPathCandidate.push_back(vectorDir);
        }

        bSharkMovePossible = true;
        return;
    }

    for (int dir = 0; dir < 4; dir++)
    {
        int targetR = r + dy_shark[dir];
        int targetC = c + dx_shark[dir];

        if (targetR < 0 || targetR >= GRID_SIZE || targetC < 0 || targetC >= GRID_SIZE)
        {
            continue;
        }

        if (count != 0) bVisited[r][c] = true;
        vectorDir.push_back(dir);

        if (bVisited[targetR][targetC])
        {
            ReturnOptimalSharkMovement(targetR, targetC, vectorDir, sumFish, count + 1);
        }
        else
        {
            ReturnOptimalSharkMovement(targetR, targetC, vectorDir, sumFish + grid[targetR][targetC].vectorFish.size(), count + 1);
        }
        bVisited[r][c] = false;
        vectorDir.erase(vectorDir.end() - 1);
    }
}

void MoveShark()
{
    vectorPathCandidate.clear();
    maxSumFish = 0;
    for (int r = 0; r < GRID_SIZE; r++)
    {
        for (int c = 0; c < GRID_SIZE; c++)
        {
            bVisited[r][c] = false;
        }
    }
    
    vector<int> vectorDir;
    bSharkMovePossible = false;
    ReturnOptimalSharkMovement(shark.y, shark.x, vectorDir, 0, 0);

    if (!bSharkMovePossible) return;

    if (vectorPathCandidate.size() > 1)
    {
        ReturnDictionaryResult();
    }

    for (int step = 0; step < 3; step++)
    {
        shark.y += dy_shark[vectorPathCandidate[0][step]];
        shark.x += dx_shark[vectorPathCandidate[0][step]];

        if (grid[shark.y][shark.x].vectorFish.size() > 0)
        {
            grid[shark.y][shark.x].vectorFish.clear();
            grid[shark.y][shark.x].fishSmell = 3;
        }
    }
}

void FadeFishSmell()
{
    for (int r = 0; r < GRID_SIZE; r++)
    {
        for (int c = 0; c < GRID_SIZE; c++)
        {
            if (grid[r][c].fishSmell > 0)
            {
                grid[r][c].fishSmell--;
            }
        }
    }
}

void PasteFish()
{
    for (int r = 0; r < GRID_SIZE; r++)
    {
        for (int c = 0; c < GRID_SIZE; c++)
        {
            for (auto nowFish : tempCopyGrid[r][c])
            {
                grid[r][c].vectorFish.push_back(nowFish);
            }
        }
    }
}

int CountFish()
{
    int sumFish = 0;

    for (int r = 0; r < GRID_SIZE; r++)
    {
        for (int c = 0; c < GRID_SIZE; c++)
        {
            sumFish += grid[r][c].vectorFish.size();
        }
    }

    return sumFish;
}

int main()
{
    txt_input >> M >> S;
    int y, x, dir;
    for (int fish = 0; fish < M; fish++)
    {
        txt_input >> y >> x >> dir;
        grid[y - 1][x - 1].vectorFish.push_back(dir + 79999);
    }

    txt_input >> y >> x;
    shark.y = y - 1;
    shark.x = x - 1;

    for (int iter = 0; iter < S; iter++)
    {
        InitTempGrid();
        CopyFish();
        
        MoveFish();
        MoveShark();

        FadeFishSmell();
        PasteFish();
    }

    cout << CountFish();

    return 0;
}
