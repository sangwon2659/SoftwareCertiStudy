/*
[6시간]
MoveShark를 할 때 For문을 돌리면서 방향 바뀌는 걸 확인해야 하기 때문에 제 자리로 돌아오는 패턴을 파악해서 %를 때려주는 게 핵심
grid에는 idx만 놓고 크기 비교를 할 때는 sort + Lambda 함수를 사용할 수도 있다
dir를 40000 이런 식으로 선언해놓고 막상 사용할 때 %를 안쓰는 바람에 디버깅 한 3시간 걸림... 진짜 조심해야 되는 부분
한줄 짜리 if문은 대괄호 안쓰고 하는 게 좋지 않을까...? 코드 길이가 너무 길어지면 가독성 떨어지는 듯
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cstring>
#include <algorithm>

using namespace std;

struct Shark
{
    int y;
    int x;
    int speed;
    int dir;
    int size;
};

ifstream txt_input("input.txt");
int R, C, M;
vector<Shark> vectorShark;
vector<int> grid[100][100];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int sumCapturedSharkSize = 0;

int MapDirection(const int& inputDir)
{
    int output;

    switch (inputDir)
    {
        case 1:
            output = 0;
            break;
        case 2:
            output = 2;
            break;
        case 3:
            output = 1;
            break;
        case 4:
            output = 3;
            break;
    }

    return output;
}

void CaptureShark(const int& column)
{
    for (int r = 0; r < R; r++)
    {
        if (grid[r][column].size() > 0)
        {
            sumCapturedSharkSize += vectorShark[grid[r][column][0]].size;
            vectorShark[grid[r][column][0]].size = 0;
            grid[r][column].clear();

            break;
        }
    }
}

void MoveShark()
{
    for (auto shark : vectorShark)
    {
        if (shark.size == 0)
        {
            continue;
        }

        grid[shark.y][shark.x].clear();
    }

    for (int idx = 0; idx < vectorShark.size(); idx++)
    {
        if (vectorShark[idx].size == 0)
        {
            continue;
        }

        int nowY = vectorShark[idx].y;
        int nowX = vectorShark[idx].x;
        int nowSpeed = vectorShark[idx].speed;
        int nowDir = vectorShark[idx].dir;

        if (nowDir % 4 == 0 || nowDir % 4 == 2)
        {
            int temp = (R - 1) * 2;
            if (nowSpeed >= temp) nowSpeed = nowSpeed % temp;
        }
        else if (nowDir % 4 == 1 || nowDir % 4 == 3)
        {
            int temp = (C - 1) * 2;
            if (nowSpeed >= temp) nowSpeed = nowSpeed % temp;
        }

        for (int iter = 0; iter < nowSpeed; iter++)
        {
            nowY = nowY + dy[nowDir % 4];
            nowX = nowX + dx[nowDir % 4];
            
            if (nowY < 0 || nowY >= R || nowX < 0 || nowX >= C)
            {
                nowDir += 2;
                nowY += 2 * dy[nowDir % 4];
                nowX += 2 * dx[nowDir % 4];
            }
        }

        vectorShark[idx].y = nowY;
        vectorShark[idx].x = nowX;
        vectorShark[idx].dir = nowDir;

        grid[nowY][nowX].push_back(idx);
    }

    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            if (grid[r][c].size() > 1)
            {
                sort(grid[r][c].begin(), grid[r][c].end(), [](const int& P1, const int& P2)
                {
                    return vectorShark[P1].size > vectorShark[P2].size;
                });
                for (int idx = 1; idx < grid[r][c].size(); idx++)
                {
                    vectorShark[grid[r][c][idx]].size = 0;
                }

                int temp = grid[r][c][0];
                grid[r][c].clear();
                grid[r][c].push_back(temp);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    txt_input >> R >> C >> M;
    for (int iter = 0; iter < M; iter++)
    {
        int y, x, speed, dir, size;
        txt_input >> y >> x >> speed >> dir >> size;
        dir = MapDirection(dir) + 40000;
        vectorShark.push_back({y - 1, x - 1, speed, dir, size});
        grid[y - 1][x - 1].push_back(iter);
    }

    for (int time = 1; time <= C; time++)
    {
        CaptureShark(time - 1);
        MoveShark();
    }

    cout << sumCapturedSharkSize;

    return 0;
}
