/*
[2시간]
for (int iSize = 5; iSize >= 1; iSize--)
이후에 return을 해서 r과 c에 대한 Loop를 더 안돌게 하는 게 시간 단축에 있어 핵심
+
if (iNowCount >= iResult) return;도 가지치기 핵심
(이런 식으로 어떻게 가지를 칠지 고민하면서 시간을 단축해야 함
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int SIZE = 10;
vector<vector<int>> Grid(SIZE, vector<int>(SIZE));
vector<int> Container = {0, 5, 5, 5, 5, 5};

int iResult = 100;

bool isAllCovered()
{
    for (int r = 0; r < SIZE; r++)
    {
        for (int c = 0; c < SIZE; c++)
        {
            if (Grid[r][c] == 1) return false;
        }
    }

    return true;
}

bool isPossible2Put(const int& inputR, const int& inputC, const int& iSize)
{
    if (inputR + iSize - 1 >= SIZE || inputC + iSize - 1 >= SIZE) return false;

    for (int r = inputR; r < inputR + iSize; r++)
    {
        for (int c = inputC; c < inputC + iSize; c++)
        {
            if (Grid[r][c] == 0) return false;
        }
    }

    return true;
}

void modifyPaper(const int& inputR, const int& inputC, const int& iSize, const int& iVal)
{
    for (int r = inputR; r < inputR + iSize; r++)
    {
        for (int c = inputC; c < inputC + iSize; c++)
        {
            Grid[r][c] = iVal;
        }
    }

    if (iVal == 0) Container[iSize]--;
    else Container[iSize]++;
}

void printGrid()
{
    for (int r = 0; r < SIZE; r++)
    {
        for (int c = 0; c < SIZE; c++)
        {
            cout << Grid[r][c] << " ";
        }
        cout << endl;
    }
    cout << "===================" << endl;
}

void DFS(const int& iNowR, int iNowC, const int& iNowCount)
{
    if (iNowCount >= iResult) return;

    //printGrid();

    if (isAllCovered())
    {
        if (iNowCount < iResult) iResult = iNowCount;
        return;
    }

    for (int r = iNowR; r < SIZE; r++)
    {
        if (r != iNowR) iNowC = 0;
        for (int c = iNowC; c < SIZE; c++)
        {
            if (Grid[r][c] != 1) continue;

            for (int iSize = 5; iSize >= 1; iSize--)
            {
                if (isPossible2Put(r, c, iSize) && Container[iSize] != 0)
                {
                    modifyPaper(r, c, iSize, 0);
                    DFS(r, c + 1, iNowCount + 1);
                    modifyPaper(r, c, iSize, 1);
                } 
            }

            return;
        }
    }
}

int main()
{
    //fstream txt_input("input.txt");
    for (int r = 0; r < SIZE; r++)
    {
        for (int c = 0; c < SIZE; c++)
        {
            cin >> Grid[r][c];
        }
    }

    DFS(0, 0, 0);

    if (iResult != 100) cout << iResult;
    else cout << -1;

    return 0;
}
