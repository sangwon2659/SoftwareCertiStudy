/*
[8시간]
빡구현 문제인데 어디가 틀렸는지 끝까지 몰라서 그냥 처음부터 다시 했더니 풀림...
어떻게 구현하는 게 좋을지 충분히 생각해보고 문제를 푸는 게 중요하다는 것을 다시 한 번 느낌
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Pos
{
    int y;
    int x;
};

struct RotateRect
{
    int startR;
    int startC;
    int size;
};

int N, M, K;
int grid[10][10];
vector<Pos> vectorPlayers;
Pos Exit;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
int totalDist = 0;

int FindClosestDist(const int& y, const int& x)
{
    return abs(Exit.y - y) + abs(Exit.x - x);
}

void MovePlayers()
{
    for (int idx = 0; idx < vectorPlayers.size(); idx++)
    {
        int curr = FindClosestDist(vectorPlayers[idx].y, vectorPlayers[idx].x);

        for (int dir = 0; dir < 4; dir++)
        {
            int targetR = vectorPlayers[idx].y + dy[dir];
            int targetC = vectorPlayers[idx].x + dx[dir];

            if (targetR < 0 || targetR >= N || targetC < 0 || targetC >= N || grid[targetR][targetC] > 0) continue;

            if (targetR == Exit.y && targetC == Exit.x)
            {
                totalDist++;
                vectorPlayers.erase(vectorPlayers.begin() + idx);
                idx--;
                break;
            }

            else if (curr > FindClosestDist(targetR, targetC))
            {
                totalDist++;
                vectorPlayers[idx].y = targetR;
                vectorPlayers[idx].x = targetC;
                break;
            }
        }
    }
}

RotateRect FindSmallestRect()
{
    int nowSize = 1;
    bool tempGrid[10][10] = {0};
    
    for (auto player : vectorPlayers)
    {
        tempGrid[player.y][player.x] = true;
    }

    while (true)
    {
        for (int startR = Exit.y - nowSize; startR <= Exit.y; startR++)
        {
            for (int startC = Exit.x - nowSize; startC <= Exit.x; startC++)
            {
                if (startR < 0 || startR + nowSize >= N || startC < 0 || startC + nowSize >= N) continue;

                for (int searchR = startR; searchR <= startR + nowSize; searchR++)
                {
                    for (int searchC = startC; searchC <= startC + nowSize; searchC++)
                    {
                        if (tempGrid[searchR][searchC])
                        {
                            RotateRect result = {startR, startC, nowSize};
                            return result;
                        }
                    }
                }
            }
        }

        nowSize++;
    }
}

void Rotate()
{
    RotateRect smallestRect = FindSmallestRect();
    int tempGrid[10][10] = {0};
    bool bIsExitMoved = false;

    for (int r = 0; r <= smallestRect.size; r++)
    {
        for (int c = 0; c <= smallestRect.size; c++)
        {
            if (smallestRect.size - c + smallestRect.startR == Exit.y && r + smallestRect.startC == Exit.x && !bIsExitMoved)
            {
                bIsExitMoved = true;
                Exit.y = r + smallestRect.startR;
                Exit.x = c + smallestRect.startC;
            }
            else
            {
                tempGrid[r + smallestRect.startR][c + smallestRect.startC] = grid[smallestRect.size - c + smallestRect.startR][r + smallestRect.startC];
                if (tempGrid[r + smallestRect.startR][c + smallestRect.startC] > 0) tempGrid[r + smallestRect.startR][c + smallestRect.startC]--;
            }
        }
    }

    for (int r = smallestRect.startR; r <= smallestRect.startR + smallestRect.size; r++)
    {
        for (int c = smallestRect.startC; c <= smallestRect.startC + smallestRect.size; c++)
        {
            grid[r][c] = tempGrid[r][c];
        }
    }

    for (int idx = 0; idx < vectorPlayers.size(); idx++)
    {
        if (vectorPlayers[idx].y >= smallestRect.startR && vectorPlayers[idx].y <= smallestRect.startR + smallestRect.size
        && vectorPlayers[idx].x >= smallestRect.startC && vectorPlayers[idx].x <= smallestRect.startC + smallestRect.size)
        {
            int r = vectorPlayers[idx].x - smallestRect.startC;
            int c = smallestRect.size + smallestRect.startR - vectorPlayers[idx].y;
            vectorPlayers[idx].y = r + smallestRect.startR;
            vectorPlayers[idx].x = c + smallestRect.startC;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    //ifstream txt_input("input.txt");
    cin >> N >> M >> K;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            int num;
            cin >> num;
            if (num > 0) grid[r][c] = num;
        }
    }

    for (int idx = 0; idx < M; idx++)
    {
        int y, x;
        cin >> y >> x;
        vectorPlayers.push_back({y - 1, x - 1});
    }

    int y, x;
    cin >> y >> x;
    Exit.y = y - 1;
    Exit.x = x - 1;

    for (int time = 0; time < K; time++)
    {
        MovePlayers();
        if (vectorPlayers.size() == 0) break;
        Rotate();
    }

    cout << totalDist << endl;
    cout << (Exit.y + 1) << " " << (Exit.x + 1);

    return 0;
}
