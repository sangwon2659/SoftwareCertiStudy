#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int N, M, H;
int dx[2] = {-1, 1};

int iGridWidth;
int iGridHeight;

string Grid[30][19];

void printGrid()
{
    for (int r = 0; r < iGridHeight; r++)
    {
        for (int c = 0; c < iGridWidth; c++)
        {
            cout << Grid[r][c] << " ";
        }

        cout << endl;
    }

    cout << "===================" << endl;;
}

bool isAllEndUpSameVerLine()
{
    for (int iVerLineIdx = 0; iVerLineIdx < iGridWidth; iVerLineIdx += 2)
    {
        int r = 0;
        int c = iVerLineIdx;
        
        /*
        string temp = Grid[r][c];
        Grid[r][c] = "O";
        printGrid(Grid);
        Grid[r][c] = temp;
        */

        while (r < H)
        {
            for (int iDir = 0; iDir < 2; iDir++)
            {
                int iTargetC = c + dx[iDir];

                if (iTargetC < 0 || iTargetC >= iGridWidth) continue;

                if (Grid[r][iTargetC] == "-")
                {
                    c += 2 * dx[iDir];
                    break;
                }
            }

            r++;
            
            /*
            if (r < H)
            {
                temp = Grid[r][c];
                Grid[r][c] = "O";
                printGrid(Grid);
                Grid[r][c] = temp;
            }
            */
        }

        if (c != iVerLineIdx) return false;
    }

    return true;
}

bool bExit = false;
bool combinationGrid(const int& iMaxHorLineNum, const int& iNowHorLineNum, const int& iNowR, int iNowC)
{
    //printGrid();

    if (iNowHorLineNum == iMaxHorLineNum)
    {
        if (isAllEndUpSameVerLine())
        {
            return true;
        }

        return false;
    }

    for (int r = iNowR; r < iGridHeight; r++)
    {
        if (r != iNowR) iNowC = 1;

        for (int c = iNowC; c < iGridWidth - 1; c += 2)
        {
            if (Grid[r][c] != " ") continue;
            if (c - 2 > 0)
            {
                if (Grid[r][c - 2] == "-") continue;
            }
            if (c + 2 < iGridWidth)
            {
                if (Grid[r][c + 2] == "-") continue;
            }

            Grid[r][c] = "-";
            if (combinationGrid(iMaxHorLineNum, iNowHorLineNum + 1, r, c))
            {
                bExit = true;
                break;
            }
            Grid[r][c] = " ";
        }

        if (bExit) break;
    }

    if (bExit) return true;

    return false;
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N >> M >> H;

    iGridWidth = (N * 2) - 1;
    iGridHeight = H;

    for (int c = 0; c < iGridWidth; c++)
    {
        if (c % 2 == 0)
        {
            for (int r = 0; r < iGridHeight; r++)
            {
                Grid[r][c] = "|";
            }
        }
        else
        {
            for (int r = 0; r < iGridHeight; r++)
            {
                Grid[r][c] = " ";
            }
        }
    }

    for (int iHorLineIdx = 0; iHorLineIdx < M; iHorLineIdx++)
    {
        int a, b;
        cin >> a >> b;

        Grid[a - 1][(b * 2) - 1] = "-";
    }

    //printGrid();

    if (isAllEndUpSameVerLine())
    {
        cout << 0;
        return 0;
    }
    
    for (int iVerLineNum = 1; iVerLineNum < 4; iVerLineNum++)
    {
        if (combinationGrid(iVerLineNum, 0, 0, 1))
        {
            cout << iVerLineNum;
            return 0;
        }
    }

    cout << -1;
    return 0;
}
