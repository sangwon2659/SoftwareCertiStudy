#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Info
{
    int iNutrient = 5;
    vector<int> vTree;
};

struct Info_
{
    int y;
    int x;
    int age;
};

int N, M, K;
Info grid[10][10];
int NutrientGrid[10][10];

vector<Info_> vDeadTree;

int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int countTree()
{
    int iCountTree = 0;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            iCountTree += grid[r][c].vTree.size();
        }
    }

    return iCountTree;
}

void Spring()
{
    vDeadTree.clear();

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (grid[r][c].vTree.size() > 0)
            {
                // 가장 작은 놈부터 먹도록 Sorting
                if (grid[r][c].vTree.size() > 1)
                {
                    sort(grid[r][c].vTree.begin(), grid[r][c].vTree.end());
                }

                for (int idx = 0; idx < grid[r][c].vTree.size(); idx++)
                {
                    // 먹을 수 있다
                    if (grid[r][c].iNutrient - grid[r][c].vTree[idx] >= 0)
                    {
                        grid[r][c].iNutrient -= grid[r][c].vTree[idx];
                        grid[r][c].vTree[idx]++;
                    }
                    else
                    {
                        for (int idx_ = grid[r][c].vTree.size() - 1; idx_ >= idx; idx_--)
                        {
                            vDeadTree.push_back({r, c, grid[r][c].vTree[idx_]});
                            grid[r][c].vTree.erase(grid[r][c].vTree.begin() + idx_);
                        }
                    }
                }
            }
        }
    }
}

void Summer()
{
    for (auto DeadTree : vDeadTree)
    {
        grid[DeadTree.y][DeadTree.x].iNutrient += (int)(DeadTree.age / 2);
    }
}

void Autumn()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (grid[r][c].vTree.size() > 0)
            {
                for (auto Tree : grid[r][c].vTree)
                {
                    if (Tree % 5 == 0)
                    {
                        for (int dir = 0; dir < 8; dir++)
                        {
                            int targetY = r + dy[dir];
                            int targetX = c + dx[dir];

                            if (targetY < 0 || targetY >= N) continue;
                            if (targetX < 0 || targetX >= N) continue;

                            // 나이가 1인 애들 추가
                            grid[targetY][targetX].vTree.push_back(1);
                        }
                    }
                }
            }
        }
    }
}

void Winter()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            grid[r][c].iNutrient += NutrientGrid[r][c];
        }
    }
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N >> M >> K;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            cin >> NutrientGrid[r][c];
        }
    }

    for (int idx = 0; idx < M; idx++)
    {
        int x, y, age;
        cin >> y >> x >> age;
        grid[y - 1][x - 1].vTree.push_back(age);
    }

    for (int iYear = 0; iYear < K; iYear++)
    {
        Spring();
        Summer();
        Autumn();
        Winter();
    }

    cout << countTree();

    return 0;
}