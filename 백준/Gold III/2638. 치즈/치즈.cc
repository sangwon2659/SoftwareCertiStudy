/*
[20분]
(0,0)부터 시작해서 쭉 훑어나가는 방식으로 간단하게 풀었음
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct IceInfo
{
    bool active;
    int Life = 2;
};

int N, M;
vector<vector<IceInfo>> Grid;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

struct Pos
{
    int y;
    int x;
};

bool isGridEmpty()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            if (Grid[r][c].active == 1) return false;
        }
    }

    return true;
}

void Solution()
{
    vector<vector<IceInfo>> TempGrid = Grid;
    vector<vector<bool>> bVisited(N, vector<bool>(M));
    queue<Pos> q;
    q.push({0, 0});
    bVisited[0][0] = true;

    while (!q.empty())
    {
        Pos v = q.front();
        q.pop();

        for (int dir = 0; dir < 4; dir++)
        {
            int iTargetR = v.y + dy[dir];
            int iTargetC = v.x + dx[dir];

            if (iTargetR < 0 || iTargetR >= N || iTargetC < 0 || iTargetC >= M) continue;
            if (bVisited[iTargetR][iTargetC]) continue;
            if (TempGrid[iTargetR][iTargetC].active == 1)
            {
                TempGrid[iTargetR][iTargetC].Life--;
                continue;
            }

            q.push({iTargetR, iTargetC});
            bVisited[iTargetR][iTargetC] = true;
        }
    }

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            if (TempGrid[r][c].active)
            {
                if (TempGrid[r][c].Life <= 0) Grid[r][c].active = false;
            }
        }
    }
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N >> M;
    Grid = vector<vector<IceInfo>>(N, vector<IceInfo>(M));

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            cin >> Grid[r][c].active;
        }
    }

    int iTime = 0;
    while (!isGridEmpty())
    {
        Solution();
        iTime++;
    }

    cout << iTime;

    return 0;
}
