#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

struct Pos
{
    int y;
    int x;
    int size = 2;
};

struct BFSPos
{
    int y;
    int x;
    int depth;
};

int N;
int grid[20][20] = {0};
Pos shark;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, -1, 0, 1};
int sumFishEaten = 0;

bool IsFishAvailable()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (grid[r][c] > 0 && grid[r][c] < shark.size) return true;
        }
    }

    return false;
}

BFSPos FindClosestFish(const int& sharkY, const int& sharkX, const int& sharkSize)
{
    bool bVisited[20][20] = {0};
    queue<BFSPos> q;
    q.push({sharkY, sharkX, 0});
    int findDepth = 100000;
    vector<BFSPos> vectorCandidates;

    while (!q.empty())
    {
        BFSPos v = q.front();
        q.pop();

        if (bVisited[v.y][v.x]) continue;
        if (v.depth > findDepth) break; 

        if (grid[v.y][v.x] > 0 && grid[v.y][v.x] < sharkSize)
        {
            findDepth = v.depth;
            vectorCandidates.push_back(v);
        }

        bVisited[v.y][v.x] = true;

        for (int dir = 0; dir < 4; dir++)
        {
            int targetR = v.y + dy[dir];
            int targetC = v.x + dx[dir];

            if (targetR < 0 || targetR >= N || targetC < 0 || targetC >= N) continue;
            if (bVisited[targetR][targetC] || grid[targetR][targetC] > shark.size) continue;

            q.push({targetR, targetC, v.depth + 1});
        }
    }

    if (vectorCandidates.size() > 1)
    {
        sort(vectorCandidates.begin(), vectorCandidates.end(), [](const BFSPos& P1, const BFSPos& P2)
        {
            return P1.x < P2.x;
        });

        sort(vectorCandidates.begin(), vectorCandidates.end(), [](const BFSPos& P1, const BFSPos& P2)
        {
            return P1.y < P2.y;
        });
    }

    if (vectorCandidates.size() == 0)
    {
        return {-1, -1, 0};
    }

    return vectorCandidates[0];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    //ifstream txt_input("input.txt");

    cin >> N;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            int val;
            cin >> val;

            if (val > 0 && val != 9) grid[r][c] = val;

            if (val == 9)
            {
                shark.y = r;
                shark.x = c;
            }
        }
    }

    int time = 0;

    while(true)
    {
        bool bIsFishAvailable = IsFishAvailable();
        if (!bIsFishAvailable) break;
        BFSPos closestFishLocationInfo = FindClosestFish(shark.y, shark.x, shark.size);

        if (closestFishLocationInfo.x == -1) break;

        shark.y = closestFishLocationInfo.y;
        shark.x = closestFishLocationInfo.x;
        
        grid[closestFishLocationInfo.y][closestFishLocationInfo.x] = 0;
        sumFishEaten++;

        if (sumFishEaten == shark.size)
        {
            shark.size++;
            sumFishEaten = 0;
        }

        time += closestFishLocationInfo.depth;
    }

    cout << time;

    return 0;
}