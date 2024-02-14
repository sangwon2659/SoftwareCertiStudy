/*
[1시간 10분]
기준 점을 잡고 회전을 하는 것 + 매번 시작점을 선분의 끝점으로 잡는 게 핵심인 문제였음
[y] = [0 -1] * [y]
[x] = [1 0]    [x]
이렇게 회전을 시킴
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct DragonCurveInfo
{
    int y;
    int x;
    int dir;
    int gen;
};

struct Pos
{
    int y;
    int x;
};

//ifstream txt_input("input.txt");
int N;
bool grid[101][101];
int dy[4] = {0, -1, 0, 1};
int dx[4] = {1, 0, -1, 0};
vector<DragonCurveInfo> vectorDragonCurveInput;

void GenerateDragonCurve()
{
    for (auto DragonCurveInput : vectorDragonCurveInput)
    {
        vector<Pos> tempContainer;
        tempContainer.push_back({DragonCurveInput.y, DragonCurveInput.x});
        tempContainer.push_back({DragonCurveInput.y + dy[DragonCurveInput.dir], DragonCurveInput.x + dx[DragonCurveInput.dir]});

        for (int iter = 0; iter < DragonCurveInput.gen; iter++)
        {
            int pivotPointIdx = tempContainer.size() - 1;
            for (int idx = pivotPointIdx - 1; idx >= 0; idx--)
            {
                int newY = tempContainer[pivotPointIdx].y - (-(-tempContainer[pivotPointIdx].x + tempContainer[idx].x));
                int newX = (-tempContainer[idx].y + tempContainer[pivotPointIdx].y) + tempContainer[pivotPointIdx].x;
                tempContainer.push_back({newY, newX});
            }
        }

        for (auto nowPoint : tempContainer)
        {
            grid[nowPoint.y][nowPoint.x] = true;
        }
    }
}

int CountSquare()
{
    int sumSquare = 0;

    for (int r = 0; r < 100; r++)
    {
        for (int c = 0; c < 100; c++)
        {
            if (grid[r][c] == 1 && grid[r + 1][c] == 1 && grid[r][c + 1] == 1 && grid[r + 1][c + 1] == 1)
            {
                sumSquare++;
            }
        }
    }

    return sumSquare;
}

int main()
{
    cin >> N;
    for (int iter = 0; iter < N; iter++)
    {
        int x, y, dir, gen;
        cin >> x >> y >> dir >> gen;
        vectorDragonCurveInput.push_back({y, x, dir, gen});
    }

    GenerateDragonCurve();
    cout << CountSquare();

    return 0;
}
