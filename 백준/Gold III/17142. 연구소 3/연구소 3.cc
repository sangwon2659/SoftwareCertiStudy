/*
[12시간]
집중을 안하고 풀어서 계속 뭐가 꼬였다.
막판에 memcpy로 string을 복사하는 것 때문에 invalid pointer 에러가 계속 났는데
이것 때문에 엄청 고생했다...;;
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <cstring>

using namespace std;

struct Pos
{
    int y;
    int x;
    int depth = 0;
};

string grid[50][50];
string tempgrid[50][50];

int N, M;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
Pos VirusContainer[10];
Pos CombinationContainer[10];
int iCount = 0;

int minTime = 100000;

void printMap()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            cout << tempgrid[r][c] << " ";
        }

        cout << endl;
    }

    cout << "================" << endl;
}

bool checkAllSpread()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (tempgrid[r][c] == "0") return false;
        }
    }

    return true;
}

void copyGrid()
{
    for (int r = 0 ; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            tempgrid[r][c] = grid[r][c];
        }
    }
}

int spreadVirus()
{
    copyGrid();
    queue<Pos> q;
    for (int idx = 0; idx < M; idx++)
    {
        tempgrid[CombinationContainer[idx].y][CombinationContainer[idx].x] = "*";
        q.push(CombinationContainer[idx]);
    }
    int maxDepth = 0;
    bool ret = true;

    while(!q.empty())
    {
        Pos v = q.front();
        q.pop();

        if (tempgrid[v.y][v.x] != "0" && tempgrid[v.y][v.x] != "V" && tempgrid[v.y][v.x] != "*") continue;

        if (v.depth > maxDepth && tempgrid[v.y][v.x] != "V")
        {
            //printMap();
            maxDepth = v.depth;
        }

        if (tempgrid[v.y][v.x] != "*")
        {
            tempgrid[v.y][v.x] = to_string(v.depth);
        }

        if (v.depth > minTime)
        {
            ret = false;
            break;
        }

        for (int dir = 0; dir < 4; dir++)
        {
            int targetY = v.y + dy[dir];
            int targetX = v.x + dx[dir];

            if (targetY < 0 || targetY >= N) continue;
            if (targetX < 0 || targetX >= N) continue;

            if ((tempgrid[targetY][targetX] != "0" && tempgrid[targetY][targetX] != "V") ||
            tempgrid[targetY][targetX] == "X") continue;

            q.push({targetY, targetX, v.depth + 1});
        }
    }

    //if (ret) printMap();
    if (!checkAllSpread()) return -1;

    return maxDepth;
}

void Solution(const int& nowPos, const int& nowVal)
{
    if (nowPos == M)
    {
        int result = spreadVirus();
        //cout << "Result: " << result << endl;

        if (result < minTime && result != -1) minTime = result;
        return;
    }

    for (int idx = nowVal; idx < iCount; idx++)
    {
        CombinationContainer[nowPos] = VirusContainer[idx];
        Solution(nowPos + 1, idx + 1);
    }
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N >> M;
    int a;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            cin >> a;
            if (a == 0) grid[r][c] = "0";
            else if (a == 1) grid[r][c] = "X";
            else
            {
                grid[r][c] = "V";
                VirusContainer[iCount] = {r, c, 0};
                iCount++;
            }
        }
    }

    Solution(0, 0);

    if (minTime != 100000) cout << minTime;
    else cout << -1;

    return 0;
}
