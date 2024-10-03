#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, L;
vector<vector<int>> Grid;
int iNumPaths = 0;

struct Pos
{
    int y;
    int x;
};

bool isPossible2Cross(const int& y, const int& x, const int& iMode)
{
    Pos pLocation = {y, x};
    vector<bool> isRamp(N);
    // Right
    if (iMode == 0)
    {
        while (pLocation.x < N - 1)
        {
            int iNextVal = Grid[pLocation.y][pLocation.x + 1];
            int iCurrentVal = Grid[pLocation.y][pLocation.x];

            if (iNextVal == iCurrentVal) pLocation.x++;
            else if (iNextVal - iCurrentVal == 1)
            {
                for (int iStep = 0; iStep < L; iStep++)
                {
                    int iTargetX = pLocation.x - iStep;
                    if (iTargetX < 0) return false;
                    if (Grid[pLocation.y][iTargetX] != iCurrentVal || isRamp[iTargetX]) return false;
                }

                for (int iStep = 0; iStep < L; iStep++)
                {
                    isRamp[pLocation.x - iStep] = true;
                }

                pLocation.x++;
            }
            else if (iNextVal - iCurrentVal == -1)
            {
                for (int iStep = 1; iStep <= L; iStep++)
                {
                    int iTargetX = pLocation.x + iStep;
                    if (iTargetX >= N) return false;
                    if (Grid[pLocation.y][iTargetX] != iNextVal || isRamp[iTargetX]) return false;
                }

                for (int iStep = 1; iStep <= L; iStep++)
                {
                    isRamp[pLocation.x + iStep] = true;
                }

                pLocation.x += L;
            }
            else return false;
        }
    }
    // Left
    else if (iMode == 1)
    {
        while (pLocation.x > 0)
        {
            int iNextVal = Grid[pLocation.y][pLocation.x - 1];
            int iCurrentVal = Grid[pLocation.y][pLocation.x];

            if (iNextVal == iCurrentVal) pLocation.x--;
            else if (iNextVal - iCurrentVal == 1)
            {
                for (int iStep = 0; iStep < L; iStep++)
                {
                    int iTargetX = pLocation.x + iStep;
                    if (iTargetX >= N) return false;
                    if (Grid[pLocation.y][iTargetX] != iCurrentVal || isRamp[iTargetX]) return false;
                }

                for (int iStep = 0; iStep < L; iStep++)
                {
                    isRamp[pLocation.x + iStep] = true;
                }

                pLocation.x--;
            }
            else if (iNextVal - iCurrentVal == -1)
            {
                for (int iStep = 1; iStep <= L; iStep++)
                {
                    int iTargetX = pLocation.x - iStep;
                    if (iTargetX < 0) return false;
                    if (Grid[pLocation.y][iTargetX] != iNextVal || isRamp[iTargetX]) return false;
                }

                for (int iStep = 1; iStep <= L; iStep++)
                {
                    isRamp[pLocation.x - iStep] = true;
                }

                pLocation.x -= L;
            }
            else return false;
        }
    }
    //Down
    else if (iMode == 2)
    {
        while (pLocation.y < N - 1)
        {
            int iNextVal = Grid[pLocation.y + 1][pLocation.x];
            int iCurrentVal = Grid[pLocation.y][pLocation.x];

            if (iNextVal == iCurrentVal) pLocation.y++;
            else if (iNextVal - iCurrentVal == 1)
            {
                for (int iStep = 0; iStep < L; iStep++)
                {
                    int iTargetY = pLocation.y - iStep;
                    if (iTargetY < 0) return false;
                    if (Grid[iTargetY][pLocation.x] != iCurrentVal || isRamp[iTargetY]) return false;
                }

                for (int iStep = 0; iStep < L; iStep++)
                {
                    isRamp[pLocation.y - iStep] = true;
                }

                pLocation.y++;
            }
            else if (iNextVal - iCurrentVal == -1)
            {
                for (int iStep = 1; iStep <= L; iStep++)
                {
                    int iTargetY = pLocation.y + iStep;
                    if (iTargetY >= N) return false;
                    if (Grid[iTargetY][pLocation.x] != iNextVal || isRamp[iTargetY]) return false;
                }

                for (int iStep = 1; iStep <= L; iStep++)
                {
                    isRamp[pLocation.y + iStep] = true;
                }

                pLocation.y += L;
            }
            else return false;
        }
    }
    // Up
    else if (iMode == 3)
    {
        while (pLocation.y > 0)
        {
            int iNextVal = Grid[pLocation.y - 1][pLocation.x];
            int iCurrentVal = Grid[pLocation.y][pLocation.x];

            if (iNextVal == iCurrentVal) pLocation.y--;
            else if (iNextVal - iCurrentVal == 1)
            {
                for (int iStep = 0; iStep < L; iStep++)
                {
                    int iTargetY = pLocation.y + iStep;
                    if (iTargetY >= N) return false;
                    if (Grid[iTargetY][pLocation.x] != iCurrentVal || isRamp[iTargetY]) return false;
                }

                for (int iStep = 0; iStep < L; iStep++)
                {
                    isRamp[pLocation.y + iStep] = true;
                }

                pLocation.y--;
            }
            else if (iNextVal - iCurrentVal == -1)
            {
                for (int iStep = 1; iStep <= L; iStep++)
                {
                    int iTargetY = pLocation.y - iStep;
                    if (iTargetY < 0) return false;
                    if (Grid[iTargetY][pLocation.x] != iNextVal || isRamp[iTargetY]) return false;
                }

                for (int iStep = 1; iStep <= L; iStep++)
                {
                    isRamp[pLocation.y - iStep] = true;
                }

                pLocation.y -= L;
            }
            else return false;
        }
    }

    return true;
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N >> L;
    Grid = vector<vector<int>>(N, vector<int>(N));

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            cin >> Grid[r][c];
        }
    }

    for (int r = 0; r < N; r++)
    {
        if (isPossible2Cross(r, 0, 0))
        {
            if (isPossible2Cross(r, 0, 1))
            {
                iNumPaths++;
            }
        }
    }

    for (int c = 0; c < N; c++)
    {
        if (isPossible2Cross(0, c, 2))
        {
            if (isPossible2Cross(0, c, 3))
            {
                iNumPaths++;
            }
        }
    }

    cout << iNumPaths;

    return 0;
}
