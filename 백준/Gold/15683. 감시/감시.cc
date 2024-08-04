#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Info
{
    int ID;
    int y;
    int x;
};

int N, M;
string grid[8][8];
string tempgrid[8][8];
vector<Info> vCCTV;
int Combination[8];
int iMaxSeen = 0;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void printGrid()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            std::cout << tempgrid[r][c] << " ";
        }

        std::cout << endl;
    }

    std::cout << "============" << endl;
}

void copyGrid()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            tempgrid[r][c] = grid[r][c];
        }
    }
}

int projectCCTV(int y, int x, int dir)
{
    int iStep = 1;
    int iCountSeen = 0;

    while (true)
    {
        int targetY = y + (dy[dir % 4] * iStep);
        int targetX = x + (dx[dir % 4] * iStep);

        if (targetY < 0 || targetY >= N) break;
        if (targetX < 0 || targetX >= M) break;
        if (tempgrid[targetY][targetX] == "X") break;

        if (tempgrid[targetY][targetX] == "0")
        {
            tempgrid[targetY][targetX] = "#";
            iCountSeen++;
        }

        iStep++;
    }

    return iCountSeen;
}

int getMaxSeen()
{
    int iMaxSeen = 0;
    copyGrid();

    for (int idx = 0; idx < vCCTV.size(); idx++)
    {
        if (vCCTV[idx].ID == 1)
        {
            iMaxSeen += projectCCTV(vCCTV[idx].y, vCCTV[idx].x, Combination[idx]);
        }
        else if (vCCTV[idx].ID == 2)
        {
            iMaxSeen += projectCCTV(vCCTV[idx].y, vCCTV[idx].x, Combination[idx] - 1);
            iMaxSeen += projectCCTV(vCCTV[idx].y, vCCTV[idx].x, Combination[idx] + 1);
        }
        else if (vCCTV[idx].ID == 3)
        {
            iMaxSeen += projectCCTV(vCCTV[idx].y, vCCTV[idx].x, Combination[idx]);
            iMaxSeen += projectCCTV(vCCTV[idx].y, vCCTV[idx].x, Combination[idx] + 1);
        }
        else if (vCCTV[idx].ID == 4)
        {
            iMaxSeen += projectCCTV(vCCTV[idx].y, vCCTV[idx].x, Combination[idx] - 1);
            iMaxSeen += projectCCTV(vCCTV[idx].y, vCCTV[idx].x, Combination[idx]);
            iMaxSeen += projectCCTV(vCCTV[idx].y, vCCTV[idx].x, Combination[idx] + 1);
        }
        else
        {
            iMaxSeen += projectCCTV(vCCTV[idx].y, vCCTV[idx].x, Combination[idx] - 1);
            iMaxSeen += projectCCTV(vCCTV[idx].y, vCCTV[idx].x, Combination[idx]);
            iMaxSeen += projectCCTV(vCCTV[idx].y, vCCTV[idx].x, Combination[idx] + 1);
            iMaxSeen += projectCCTV(vCCTV[idx].y, vCCTV[idx].x, Combination[idx] + 2);
        }

        //printGrid();
    }

    //std::cout << "MaxSeen: " << iMaxSeen << endl;

    return iMaxSeen;
}

void Solution(const int& nowPos, const int& nowVal)
{
    if (nowPos == vCCTV.size())
    {
        int result = getMaxSeen();
        if (result > iMaxSeen) iMaxSeen = result;

        return ;
    }

    for (int dir = 40000; dir < 40004; dir++)
    {
        Combination[nowPos] = dir;
        Solution(nowPos + 1, dir + 1);
    }
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N >> M;
    int iMaxSpace = 0;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            int a;
            cin >> a;
            if (a == 0)
            {
                grid[r][c] = "0";
                iMaxSpace++;
            }
            else if (a == 6) grid[r][c] = "X";
            else
            {
                grid[r][c] = to_string(a);
                vCCTV.push_back({a, r, c});
            }
        }
    }

    Solution(0, 40000);
    std::cout << iMaxSpace - iMaxSeen;

    return 0;
}