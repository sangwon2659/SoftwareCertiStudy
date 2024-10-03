#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N, M;
int iMaxScore = 0;
vector<vector<int>> Grid;
vector<vector<int>> TempGrid;

struct Pos
{
    int y;
    int x;
};

vector<vector<Pos>> vTetromino =
{
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {2, 0}, {2, 1}},
    {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
    {{0, 0}, {0, 1}, {0, 2}, {1, 1}},
    // Blue Rotation
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
    // Orange Rotation
    {{1, 0}, {1, 1}, {1, 2}, {0, 2}},
    {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
    {{0, 0}, {0, 1}, {0, 2}, {1, 0}},
    // Green Rotation
    {{1, 0}, {1, 1}, {0, 1}, {0, 2}},
    // Pink Rotation
    {{0, 0}, {1, 0}, {2, 0}, {1, 1}},
    {{0, 1}, {1, 0}, {1, 1}, {1, 2}},
    {{1, 0}, {0, 1}, {1, 1}, {2, 1}},
    // Orange Flip & Rotation
    {{0, 1}, {1, 1}, {2, 1}, {2, 0}},
    {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
    {{0 ,0}, {0, 1}, {1, 0}, {2, 0}},
    {{0, 0}, {1, 0}, {1, 1}, {1, 2}},
    // Green Flip & Rotation
    {{0, 1}, {1, 1}, {1, 0}, {2, 0}},
    {{0, 0}, {0, 1}, {1, 1}, {1, 2}}
};

void printGrid(const vector<vector<int>>& input)
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            cout << input[r][c] << " ";
        }

        cout << endl;
    }

    cout << "==============" << endl;
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N >> M;

    Grid = vector<vector<int>>(N, vector<int>(M));

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            cin >> Grid[r][c];
        }
    }

    for (auto Tetromino : vTetromino)
    {
        for (int r = 0; r < N; r++)
        {
            bool ret_r = true;
            for (int c = 0; c < M; c++)
            {
                int iScore = 0;
                bool ret_c = true;
                //TempGrid = vector<vector<int>>(N, vector<int>(M));

                for (auto point : Tetromino)
                {
                    int iTargetR = r + point.y;
                    int iTargetC = c + point.x;

                    if (iTargetR >= N)
                    {
                        ret_r = false;
                        break;
                    }
                    if (iTargetC >= M)
                    {
                        ret_c = false;
                        break;
                    }

                    iScore += Grid[iTargetR][iTargetC];
                    //TempGrid[iTargetR][iTargetC] = 1;
                }

                if (!ret_c || !ret_r) break;
                if (iScore > iMaxScore) iMaxScore = iScore;
                //printGrid(TempGrid);
            }

            if (!ret_r) break;
        }
    }

    cout << iMaxScore;

    return 0;
}