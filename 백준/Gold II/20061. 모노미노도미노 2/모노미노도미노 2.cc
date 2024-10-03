/*
[3시간]
완전 빡구현 문제....
숫자를 조심하는 게 최선
Rotation을 할 때 특정 좌표의 Grid가 어떻게 바뀔지가 아니라 특정 좌표를 넣었을 때
Rotation되어서 좌표가 돌아오도록 하는 게 포인트였음
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int N;
const int HEIGHT = 10;
const int WIDTH = 4;
vector<vector<int>> Grid_1(HEIGHT, vector<int>(WIDTH));
vector<vector<int>> Grid_2(HEIGHT, vector<int>(WIDTH));
int iScore = 0;

struct Pos
{
    int type;
    int y;
    int x;
};

vector<Pos> makeBlock(const int& t, const int& y, const int& x)
{
    vector<Pos> result;

    if (t == 1)
    {
        result.push_back({1, y, x});
    }
    else if (t == 2)
    {
        result.push_back({2, y, x});
        result.push_back({2, y, x + 1});
    }
    else if (t == 3)
    {
        result.push_back({3, y, x});
        result.push_back({3, y + 1, x});
    }

    return result;
}

vector<Pos> rotateClockwise90(const vector<Pos>& input)
{
    vector<Pos> result;
    const int SIZE = 4;

    for (auto element : input)
    {
        int type = element.type;
        if (element.type == 2) type = 3;
        else if (element.type == 3) type = 2;
        result.push_back({type, element.x, SIZE - element.y - 1});
    }

    return result;
}

void placeBlock(vector<vector<int>>& Grid, const vector<Pos>& vBlock)
{
    int iTargetR = 5;
    bool ret = true;
    while (true)
    {
        for (auto element : vBlock)
        {
            if (!(Grid[iTargetR + 1][element.x] == 0 && iTargetR <= 8))
            {
                ret = false;
            }
        }

        if (!ret) break;

        iTargetR++;
        if (iTargetR == 9) break;
    }

    if (vBlock[0].type == 1)
    {
        Grid[iTargetR][vBlock[0].x] = 1;
    }
    else if (vBlock[0].type == 2)
    {
        Grid[iTargetR][vBlock[0].x] = 1;
        Grid[iTargetR][vBlock[1].x] = 1;
    }
    else
    {
        Grid[iTargetR - 1][vBlock[0].x] = 1;
        Grid[iTargetR][vBlock[1].x] = 1;
    }
}

void removeFullRow(vector<vector<int>>& Grid)
{
    queue<vector<int>> q;

    for (int r = 9; r > 3; r--)
    {
        if (Grid[r][0] && Grid[r][1] && Grid[r][2] && Grid[r][3])
        {
            Grid[r] = vector<int>(WIDTH);
            iScore++;
        }
        else
        {
            q.push(Grid[r]);
        }
    }

    int iTargetR = 9;
    while (!q.empty())
    {
        vector<int> v = q.front();
        q.pop();

        Grid[iTargetR] = v;
        iTargetR--;
    }
}

void removeGreyArea(vector<vector<int>>& Grid)
{
    int iCountGrey = 0;
    stack<vector<int>> stk;
    for (int r = 4; r < 6; r++)
    {
        if (Grid[r][0] || Grid[r][1] || Grid[r][2] || Grid[r][3])
        {
            stk.push(Grid[r]);
            Grid[r] = vector<int>(WIDTH);
            iCountGrey++;
        }
    }

    for (int r = 6; r < 10 - iCountGrey; r++)
    {
        stk.push(Grid[r]);
    }

    for (int r = 9; r > 5; r--)
    {
        if (stk.empty()) break;
        Grid[r] = stk.top();
        stk.pop();
    }
}

int countTiles()
{
    int iNumTiles = 0;

    for (int r = 0; r < HEIGHT; r++)
    {
        for (int c = 0; c < WIDTH; c++)
        {
            if (Grid_1[r][c] != 0) iNumTiles++;
            if (Grid_2[r][c] != 0) iNumTiles++;
        }
    }

    return iNumTiles;
}

void printGrid(const vector<vector<int>>& Grid)
{
    cout << "===================" << endl;

    for (int r = 0; r < HEIGHT; r++)
    {
        for (int c = 0; c < WIDTH; c++)
        {
            cout << Grid[r][c] << " ";
        }
        cout << endl;
    }

    cout << "===================" << endl;
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N;

    for (int iBlockIDX = 0; iBlockIDX < N; iBlockIDX++)
    {
        int t, y, x;
        cin >> t >> y >> x;
        vector<Pos> vBlock = makeBlock(t, y, x);

        placeBlock(Grid_1, vBlock);
        removeFullRow(Grid_1);
        removeGreyArea(Grid_1);

        placeBlock(Grid_2, rotateClockwise90(vBlock));
        removeFullRow(Grid_2);
        removeGreyArea(Grid_2);

        //printGrid(Grid_1);
        //printGrid(Grid_2);
    }

    cout << iScore << endl;
    cout << countTiles() << endl;

    return 0;
}
