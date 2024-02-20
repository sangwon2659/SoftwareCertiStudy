#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;

int N;
int grid[20][20] = { 0 };
int largestNum = 0;

void PrintBlock()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            cout << grid[r][c] << " ";
        }
        
        cout << endl;
    }
}

void MoveBlocks(const int& dir)
{
    int location[20];
    bool bIsMerged[20][20] = { 0 };

    switch (dir)
    {
        case 0:
            for (int i = 0; i < N; i++)
            {
                for (int j = 1; j < N; j++)
                {
                    if (grid[j][i] == 0)
                        continue;
                    for (int k = j - 1; k >= 0; k--)
                    {
                        if (grid[k][i] == grid[k + 1][i] && !bIsMerged[k][i])
                        {
                            grid[k][i] *= 2;
                            grid[k + 1][i] = 0;
                            bIsMerged[k][i] = true;
                            break;
                        }
                        else if (grid[k][i] == 0)
                        {
                            grid[k][i] = grid[k + 1][i];
                            grid[k + 1][i] = 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            break;

        case 1:
            for (int i = 0; i < N; i++)
            {
                for (int j = N - 2; j >= 0; j--)
                {
                    if (grid[i][j] == 0)
                        continue;
                    for (int k = j + 1; k < N; k++)
                    {
                        if (grid[i][k] == grid[i][k - 1] && !bIsMerged[i][k])
                        {
                            grid[i][k] *= 2;
                            grid[i][k - 1] = 0;
                            bIsMerged[i][k] = true;
                            break;
                        }
                        else if (grid[i][k] == 0)
                        {
                            grid[i][k] = grid[i][k - 1];
                            grid[i][k - 1] = 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            break;

        case 2:
            for (int i = 0; i < N; i++)
            {
                for (int j = N - 2; j >= 0; j--)
                {
                    if (grid[j][i] == 0)
                        continue;
                    for (int k = j + 1; k < N; k++)
                    {
                        if (grid[k][i] == grid[k - 1][i] && !bIsMerged[k][i])
                        {
                            grid[k][i] *= 2;
                            grid[k - 1][i] = 0;
                            bIsMerged[k][i] = true;
                            break;
                        }
                        else if (grid[k][i] == 0)
                        {
                            grid[k][i] = grid[k - 1][i];
                            grid[k - 1][i] = 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            break;

        case 3:
            for (int i = 0; i < N; i++)
            {
                for (int j = 1; j < N; j++)
                {
                    if (grid[i][j] == 0)
                        continue;
                    for (int k = j - 1; k >= 0; k--)
                    {
                        if (grid[i][k] == grid[i][k + 1] && !bIsMerged[i][k])
                        {
                            grid[i][k] *= 2;
                            grid[i][k + 1] = 0;
                            bIsMerged[i][k] = true;
                            break;
                        }
                        else if (grid[i][k] == 0)
                        {
                            grid[i][k] = grid[i][k + 1];
                            grid[i][k + 1] = 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            break;
    }
}

void FindLargestBlock()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (grid[r][c] > largestNum)
            {
                largestNum = grid[r][c];
            }
        }
    }
}

void DFS(const int& count)
{
    if (count == 5) return;

    int saveGrid[20][20] = { 0 };
    memcpy(saveGrid, grid, 20 * 20 * sizeof(int));

    for (int dir = 0; dir < 4; dir++)
    {
        MoveBlocks(dir);
        FindLargestBlock();
        DFS(count + 1);
        memcpy(grid, saveGrid, 20 * 20 * sizeof(int));
    }
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
            int num;
            cin >> num;

            if (num > 0) grid[r][c] = num;
        }
    }

    DFS(0);
    //MoveBlocks(0);
    //PrintBlock();

    cout << largestNum;

    return 0;
}
