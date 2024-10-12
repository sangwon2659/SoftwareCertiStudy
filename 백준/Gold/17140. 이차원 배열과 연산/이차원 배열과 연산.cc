#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
int r, c, k;
const int GRID_SIZE = 100;

vector<vector<int>> Grid(GRID_SIZE, vector<int>(GRID_SIZE));

int iRSize = 0;
int iCSize = 0;

struct Info
{
    int iNum;
    int iFreq;
};

void printGrid(const int& iMode)
{
    // iMode == 0: 전에 operationR
    // iMode == 1: 전에 operationC

    if (iMode == 0)
    {
        for (int r = 0; r < iRSize; r++)
        {
            for (int c = 0; c < iCSize; c++)
            {
                if (Grid[r][c] >= 10) cout << Grid[r][c] << " ";
                else cout << Grid[r][c] << "  ";
            }

            cout << endl;
        }
        cout << "===============" << endl;
    }
    else
    {
        for (int r = 0; r < iRSize; r++)
        {
            for (int c = 0; c < iCSize; c++)
            {
                
                if (Grid[r][c] >= 10) cout << Grid[r][c] << " ";
                else cout << Grid[r][c] << "  ";
            }

            cout << endl;
        }
        cout << "===============" << endl;
    }    
}

bool isRLarger(const int& iMode)
{
    // iMode == 0: 전에 operationR
    // iMode == 1: 전에 operationC

    iRSize = 0;
    iCSize = 0;

    if (iMode == 0)
    {
        for (int r = 0; r < GRID_SIZE; r++)
        {
            if (Grid[r][0] == 0)
            {
                iRSize = r;
                break;
            }

            for (int c = 0; c < GRID_SIZE; c++)
            {
                if (Grid[r][c] == 0)
                {
                    if (c > iCSize) iCSize = c;
                    break;
                }
            }
        }
    }
    else
    {
        for (int c = 0; c < GRID_SIZE; c++)
        {
            if (Grid[0][c] == 0)
            {
                iCSize = c;
                break;
            }

            for (int r = 0; r < GRID_SIZE; r++)
            {
                if (Grid[r][c] == 0)
                {
                    if (r > iRSize) iRSize = r;
                    break;
                }
            }
        }
    }

    if (iRSize >= iCSize) return true;
    else return false;
}

void operationR()
{
    for (int r = 0; r < iRSize; r++)
    {
        vector<Info> v;
        for (int c = 0; c < iCSize; c++)
        {
            if (Grid[r][c] == 0) continue;

            bool isExist = false;
            for (int idx = 0; idx < v.size(); idx++)
            {
                if (v[idx].iNum == Grid[r][c])
                {
                    v[idx].iFreq++;
                    isExist = true;
                    break;
                }
            }
            if (!isExist) v.push_back({Grid[r][c], 1});

            Grid[r][c] = 0;
            if (v.size() > 50 ) break;
        }

        sort(v.begin(), v.end(), [](const Info& P1, const Info& P2)
        {
            if (P1.iFreq != P2.iFreq) return P1.iFreq < P2.iFreq;
            else return P1.iNum < P2.iNum;
        });

        int idx = 0;
        for (auto element : v)
        {
            Grid[r][idx++] = element.iNum;
            Grid[r][idx++] = element.iFreq;
        }
    }
}

void operationC()
{
    for (int c = 0; c < iCSize; c++)
    {
        vector<Info> v;
        for (int r = 0; r < iRSize; r++)
        {
            if (Grid[r][c] == 0) continue;

            bool isExist = false;
            for (int idx = 0; idx < v.size(); idx++)
            {
                if (v[idx].iNum == Grid[r][c])
                {
                    v[idx].iFreq++;
                    isExist = true;
                    break;
                }
            }
            if (!isExist) v.push_back({Grid[r][c], 1});

            Grid[r][c] = 0;
            if (v.size() > 50) break;
        }

        sort(v.begin(), v.end(), [](const Info& P1, const Info& P2)
        {
            if (P1.iFreq != P2.iFreq) return P1.iFreq < P2.iFreq;
            else return P1.iNum < P2.iNum;
        });

        int idx = 0;
        for (auto element : v)
        {
            Grid[idx++][c] = element.iNum;
            Grid[idx++][c] = element.iFreq;
        }
    }
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> r >> c >> k;

    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            cin >> Grid[r][c];
        }
    }

    int iResult = -1;
    int iTime = 0;
    bool isROperation = true;

    while (iTime <= 100)
    {
        if (Grid[r - 1][c - 1] == k)
        {
            iResult = iTime;
            break;
        }

        bool bIsRLarger;
        if (isROperation)
        {
            bIsRLarger = isRLarger(0);
            //printGrid(0);
        }
        else
        {
            bIsRLarger = isRLarger(1);
            //printGrid(1);
        }

        if (bIsRLarger)
        {
            operationR();
            isROperation = true;
        }
        else
        {
            operationC();
            isROperation = false;
        }

        iTime++;
    }

    cout << iResult;

    return 0;
}