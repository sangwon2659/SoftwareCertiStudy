/*
[45분]
TempGrid[r + rBase][c + cBase] = Grid[Size - c - 1 + rBase][r + cBase]만 생각하면 매우 쉬운 문제.
다만 IceChunk의 크기를 계산할 때 InitPos의 Ice가 0일 때는 Count를 하지 않도록,
그리고 TempGrid[r][c] > 0인 경우에만 TempGrid[r][c]--;를 하는 등의 Detail이 필요했음
*/

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;
int N, Q;
int iGridSize;
vector<vector<int>> Grid;
vector<vector<int>> TempGrid;
vector<vector<bool>> bVisited;
vector<int> iLContainer;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

struct Pos
{
    int y;
    int x;
};

int calcSize(const int& input)
{
    int ret = 1;
    for (int i = 0; i < input; i++)
    {
        ret *= 2;
    }

    return ret;
}

int calcAllIce()
{
    int sum = 0;

    for (int r = 0; r < iGridSize; r++)
    {
        for (int c = 0; c < iGridSize; c++)
        {
            sum += Grid[r][c];
        }
    }

    return sum;
}

void adjIce()
{
    TempGrid = Grid;

    for (int r = 0; r < iGridSize; r++)
    {
        for (int c = 0; c < iGridSize; c++)
        {
            int sumPos = 0;
            int iTargetR;
            int iTargetC;

            for (int dir = 0; dir < 4; dir++)
            {
                iTargetR = r + dy[dir];
                iTargetC = c + dx[dir];

                if (iTargetR < 0 || iTargetR >= iGridSize) continue;
                if (iTargetC < 0 || iTargetC >= iGridSize) continue;

                if (Grid[iTargetR][iTargetC] > 0) sumPos++;
            }

            if (sumPos < 3)
            {
                if (TempGrid[r][c] > 0) TempGrid[r][c]--;
            }
        }
    }

    Grid = TempGrid;
}

void rotateGrid(const int& L)
{
    TempGrid = vector<vector<int>>(iGridSize, vector<int>(iGridSize));
    int iSubGridSize = calcSize(L);

    for (int iRBase = 0; iRBase < iGridSize; iRBase += iSubGridSize)
    {
        for (int iCBase = 0; iCBase < iGridSize; iCBase += iSubGridSize)
        {
            for (int r = 0; r < iSubGridSize; r++)
            {
                for (int c = 0; c < iSubGridSize; c++)
                {
                    TempGrid[r + iRBase][c + iCBase] = Grid[iSubGridSize - c - 1 + iRBase][r + iCBase];
                }
            }
        }
    }

    Grid = TempGrid;
}

int calcIceChunk(const Pos& pInitPos)
{
    queue<Pos> q;
    q.push({pInitPos.y, pInitPos.x});
    int iSumIce = 0;
    
    while (!q.empty())
    {
        Pos v = q.front();
        q.pop();

        if (bVisited[v.y][v.x]) continue;
        bVisited[v.y][v.x] = true;
        iSumIce++;

        for (int dir = 0; dir < 4; dir++)
        {
            int iTargetR = v.y + dy[dir];
            int iTargetC = v.x + dx[dir];

            if (iTargetR < 0 || iTargetR >= iGridSize) continue;
            if (iTargetC < 0 || iTargetC >= iGridSize) continue;

            if (Grid[iTargetR][iTargetC] == 0) continue;
            if (bVisited[iTargetR][iTargetC]) continue;

            q.push({iTargetR, iTargetC});
        }
    }

    return iSumIce;
}

int findLargestIceChunk()
{
    bVisited = vector<vector<bool>>(iGridSize, vector<bool>(iGridSize));
    int iLargestIceSum = 0;

    for (int r = 0; r < iGridSize; r++)
    {
        for (int c = 0; c < iGridSize; c++)
        {
            if (bVisited[r][c]) continue;
            if (Grid[r][c] == 0) continue;

            int iSumIceChunk = calcIceChunk({r, c});
            if (iSumIceChunk > iLargestIceSum) iLargestIceSum = iSumIceChunk;
        }
    }

    return iLargestIceSum;
}

void printGrid()
{
    cout << "==========" << endl;

    for (int r = 0; r < iGridSize; r++)
    {
        for (int c = 0; c < iGridSize; c++)
        {
            cout << Grid[r][c] << " ";
        }

        cout << endl;
    }

    cout << "==========" << endl;
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N >> Q;

    iGridSize = calcSize(N);

    Grid = vector<vector<int>>(iGridSize, vector<int>(iGridSize));
    TempGrid = vector<vector<int>>(iGridSize, vector<int>(iGridSize));
    for (int r = 0; r < iGridSize; r++)
    {
        for (int c = 0; c < iGridSize; c++)
        {
            cin >> Grid[r][c];
        }
    }

    //printGrid();

    iLContainer = vector<int>(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> iLContainer[i];
    }

    for (int iter = 0; iter < Q; iter++)
    {
        rotateGrid(iLContainer[iter]);
        //printGrid();
        adjIce();
        //printGrid();
    }

    cout << calcAllIce() << endl;
    cout << findLargestIceChunk() << endl;

    return 0;
}
