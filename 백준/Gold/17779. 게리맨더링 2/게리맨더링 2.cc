#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

int N;
const int SIZE_REGION = 5;
vector<vector<int>> Population;
vector<vector<int>> Grid;
vector<vector<bool>> bVisited;
vector<int> iSumRegion(SIZE_REGION);

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int iMinDiff = 100000000;

struct Pos
{
    int y;
    int x;
};

void printGrid()
{
    cout << "==========" << endl;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            cout << Grid[r][c] << " ";
        }
        
        cout << endl;
    }

    cout << "==========" << endl;
}

void dedicateRegion(const int& x, const int& y, const int& d1, const int& d2)
{
    Grid = vector<vector<int>>(N, vector<int>(N));

    for (int d = 0; d <= d1; d++)
    {
        Grid[x + d][y - d] = 5;
    }

    for (int d = 0; d <= d2; d++)
    {
        Grid[x + d][y + d] = 5;
    }

    for (int d = 0; d <= d2; d++)
    {
        Grid[x + d1 + d][y - d1 + d] = 5;
    }

    for (int d = 0; d <= d1; d++)
    {
        Grid[x + d2 + d][y + d2 - d] = 5;
    }

    vector<vector<bool>> bVisited_(N, vector<bool>(N));
    queue<Pos> q;
    q.push({x + 1, y});

    while (!q.empty())
    {
        Pos v = q.front();
        q.pop();

        if (bVisited_[v.y][v.x]) continue;

        Grid[v.y][v.x] = 5;
        bVisited_[v.y][v.x] = true;

        for (int dir = 0; dir < 4; dir++)
        {
            int iTargetR = v.y + dy[dir];
            int iTargetC = v.x + dx[dir];

            if (Grid[iTargetR][iTargetC] == 5) continue;

            q.push({iTargetR, iTargetC});
        }
    }

    for (int r = y - d1 + 1; r < y + d2; r++)
    {
        for (int c = x + 1; c < x + d1 + d2; c++)
        {
            bool ret = true;

            for (int dir = 0; dir < 4; dir++)
            {
                if (Grid[r + dy[dir]][c + dx[dir]] != 5) ret = false;
            }

            if (ret) Grid[r][c] = 5;
        }
    }

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (Grid[r][c] == 5) continue;

            if ((r < x + d1) && (c <= y)) Grid[r][c] = 1;
            else if ((r <= x + d2) && (y < c)) Grid[r][c] = 2;
            else if ((x + d1 <= r) && (c < y - d1 + d2)) Grid[r][c] = 3;
            else if ((x + d2 < r) && (y - d1 + d2 <= c)) Grid[r][c] = 4;
        }
    }
}

void countRegion(const Pos& pInitPos)
{
    queue<Pos> q;
    q.push({pInitPos.y, pInitPos.x});
    int iRegion = Grid[pInitPos.y][pInitPos.x];

    while (!q.empty())
    {
        Pos v = q.front();
        q.pop();

        if (bVisited[v.y][v.x]) continue;
        bVisited[v.y][v.x] = true;

        iSumRegion[iRegion - 1] += Population[v.y][v.x];

        for (int dir = 0; dir < 4; dir++)
        {
            int iTargetR = v.y + dy[dir];
            int iTargetC = v.x + dx[dir];

            if (iTargetR < 0 || iTargetR >= N) continue;
            if (iTargetC < 0 || iTargetC >= N) continue;

            if (Grid[iTargetR][iTargetC] != iRegion) continue;
            if (bVisited[iTargetR][iTargetC]) continue;

            q.push({iTargetR, iTargetC});
        }
    }
}

int calcMinMaxDifference()
{
    bVisited = vector<vector<bool>>(N, vector<bool>(N));
    iSumRegion = vector<int>(SIZE_REGION);

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (bVisited[r][c] == 0) countRegion({r, c});
        }
    }

    sort(iSumRegion.begin(), iSumRegion.end(), greater<>());
    return iSumRegion[0] - iSumRegion[4];
}

void Solve(const int& nowD1, const int& nowD2, const int& nowX, const int& nowY, const int& nowPos)
{
    if (nowPos == 4)
    {
        dedicateRegion(nowX, nowY, nowD1, nowD2);
        //cout << "X: " << nowX << " Y: " << nowY << " D1: " << nowD1 << " D2: " << nowD2 << endl;
        int ret = calcMinMaxDifference();
        //cout << "Count: " << ret << endl;
        //printGrid();
        if (ret < iMinDiff) iMinDiff = ret;
    }

    if (nowPos == 0)
    {
        for (int i = 1; i < N - 2; i++)
        {
            Solve(i, nowD2, nowX, nowY, nowPos + 1);
        }
    }
    else if (nowPos == 1)
    {
        for (int i = 1; i < N - 2; i++)
        {
            if (nowD1 + i >= N) break;
            Solve(nowD1, i, nowX, nowY, nowPos + 1);
        }
    }
    else if (nowPos == 2)
    {
        for (int i = 0; i < N - 3; i++)
        {
            if (i + nowD1 + nowD2 >= N) break;
            Solve(nowD1, nowD2, i, nowY, nowPos + 1);
        }
    }
    else if (nowPos == 3)
    {
        for (int i = 0; i < N - 2; i++)
        {
            if (i - nowD1 < 0) continue;
            if (i + nowD2 >= N) continue;

            Solve(nowD1, nowD2, nowX, i, nowPos + 1);
        }
    }
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N;

    Population = vector<vector<int>>(N, vector<int>(N));

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            cin >> Population[r][c];
        }
    }

    Solve(1, 1, 0, 0, 0);
    cout << iMinDiff;

    return 0;
}