/*
[5시간]
원판을 Grid형태로 이해하고, X방향으로는 % M을 써서 인접할 수 있도록 하는 것이 핵심이었음
DFS를 하면서 -1로 바꿔주는 로직 또한 핵심이었음
double avg = (double)sum / (double)cnt를 해줘야 avg가 double 형태로 나오면서 제대로 비교가 되는데
double avg = (int)sum / (int)cnt를 해서 한참 동안 엄청난 카오스였음...
*/

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
int N, M, T;
vector<int> grid[50];
int x, d, k;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

bool bIsDeleted = false;

void rotatePanel(const int& panelIdx, const int& rotationDir, const int& rotationNum)
{
    for (int rotationIter = 0; rotationIter < rotationNum; rotationIter++)
    {
        //clock-wise
        if (rotationDir == 0)
        {
            grid[panelIdx].insert(grid[panelIdx].begin(), grid[panelIdx][M - 1]);
            grid[panelIdx].erase(grid[panelIdx].end() - 1);
        }
        //Anti-Clock-wise
        else if (rotationDir == 1)
        {
            grid[panelIdx].push_back(grid[panelIdx][0]);
            grid[panelIdx].erase(grid[panelIdx].begin());
        }
    }
}

bool isAnyNumberLeft()
{
    bool ret = false;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            if (grid[r][c] > -1) ret = true;
        }
    }

    return ret;
}

void DeleteDFS(const int& r, const int& c, const int nowNum, const int& depth)
{
    if (r < 0 || r >= N || grid[r][c % M] == -1)
    {
        return;
    }

    if (depth > 0)
    {
        grid[r][c % M] = -1;
    }

    for (int dir = 0; dir < 4; dir++)
    {
        int targetR = r + dy[dir];
        int targetC = c + dx[dir];

        if (targetR < 0 || targetR >= N || grid[targetR][targetC % M] == -1)
        {
            continue;
        }

        if (grid[targetR][targetC % M] == nowNum)
        {
            if (depth == 0) grid[r][c % M] = -1;

            bIsDeleted = true;
            DeleteDFS(targetR, targetC, nowNum, depth + 1);
        }
    }
}

void DeleteAdjacents()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            if (grid[r][c] > -1)
            {
                DeleteDFS(r, c + (M * 100000), grid[r][c], 0);
            }
        }
    }
}

void ComputeNumbers()
{
    double sum = 0;
    double cnt = 0;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            if (grid[r][c] > -1)
            {
                sum += grid[r][c];
                cnt++;
            }
        }
    }
    double avg = sum / cnt;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            if (grid[r][c] > -1)
            {
                if ((double)grid[r][c] > avg)
                {
                    grid[r][c]--;
                }
                else if ((double)grid[r][c] < avg)
                {
                    grid[r][c]++;
                }
            }
        }
    }
}

int CountSum()
{
    int sum = 0;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            if (grid[r][c] > -1)
            {
                sum += grid[r][c];
            }
        }
    }

    return sum;
}

int main()
{
    //ifstream txt_input("input.txt");

    cin >> N >> M >> T;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            int num;
            cin >> num;
            grid[r].push_back(num);
        }
    }

    for (int iter = 0; iter < T; iter++)
    {
        cin >> x >> d >> k;
        for (int panelIdx = x - 1; panelIdx < N; panelIdx += x)
        {
            rotatePanel(panelIdx, d, k);
        }

        if (isAnyNumberLeft())
        {
            bIsDeleted = false;
            DeleteAdjacents();

            if (!bIsDeleted)
            {
                ComputeNumbers();
            }
        }
    }

    cout << CountSum();

    return 0;
}
