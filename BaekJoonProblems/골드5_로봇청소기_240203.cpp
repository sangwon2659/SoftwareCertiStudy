/*
1시간 가량 소요됨
방향을 유지한 채로 BackStep을 한다는 걸 제대로 안읽어서 디버깅 함
%를 써서 방향 전환 알고리즘을 비교적 간결하게 짬
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

vector<vector<int>> grid(50, vector<int>(50, -100));    
int N, M;

// North, East, South, West
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

struct RobotStatus
{
    int y;
    int x;
    int dir;
};

bool ExistAdjacentUncleanedRoom(const int& r, const int& c)
{
    bool ret = false;

    for (int dir = 0; dir < 4; dir++)
    {
        int targetR = r + dy[dir];
        int targetC = c + dx[dir];

        if (grid[targetR][targetC] == 0)
        {
            ret = true;
        }
    }

    return ret;
}

int main()
{
    ifstream txt_input("input.txt");
    RobotStatus robot;
    int sumCleaned = 0;

    txt_input >> N >> M;
    txt_input >> robot.y >> robot.x >> robot.dir;
    robot.dir += 4000;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            txt_input >> grid[r][c];
        }
    }

    while (true)
    {
        if (grid[robot.y][robot.x] == 0)
        {
            grid[robot.y][robot.x] = -1;
            sumCleaned++;
        }

        if (ExistAdjacentUncleanedRoom(robot.y, robot.x))
        {
            robot.dir--;
            int targetDir = (robot.dir) % 4;

            if (grid[robot.y + dy[targetDir]][robot.x + dx[targetDir]] == 0)
            {
                robot.y += dy[targetDir];
                robot.x += dx[targetDir];
            }
        }
        else
        {
            int backStepDir = (robot.dir + 2) % 4;

            if (grid[robot.y + dy[backStepDir]][robot.x + dx[backStepDir]] != 1)
            {
                robot.y += dy[backStepDir];
                robot.x += dx[backStepDir];
            }
            else
            {
                break;
            }
        }
    }

    cout << sumCleaned;

    return 0;
}
