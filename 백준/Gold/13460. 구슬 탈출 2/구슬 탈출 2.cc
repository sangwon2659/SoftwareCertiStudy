#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

int N, M;
vector<vector<string>> Grid;
vector<vector<int>> tiltOrder;
int result = -1;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

struct Info
{
    int yRed;
    int xRed;
    int yBlue;
    int xBlue;
    int iTiltMode;
};

struct Pos
{
    int y;
    int x;
};

Pos pO;

void printGrid(const vector<vector<string>>& Grid)
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < M; c++)
        {
            cout << Grid[r][c] << " ";
        }

        cout << endl;
    }

    cout << "====================" << endl;
}

int tiltBoard(vector<vector<string>>& Grid, Info& info)
{
    // 1: 성공 (빨간색 구멍에)
    // 0: 공 둘다 구멍에 X
    // -1: 실패 (파란색이 구멍에 또는 빨간색 파란색 같이 구멍에)

    int outcome = 0;

    Pos pRed = { info.yRed, info.xRed };
    Pos pBlue = { info.yBlue, info.xBlue };
    int iTiltMode = info.iTiltMode;

    while (true)
    {
        Pos pTargetRed = { pRed.y + dy[iTiltMode], pRed.x + dx[iTiltMode] };
        Pos pTargetBlue = { pBlue.y + dy[iTiltMode], pBlue.x + dx[iTiltMode] };

        if (Grid[pRed.y][pRed.x] == "O")
        {
            pTargetRed = pRed;
            outcome = 1;
        }

        if (Grid[pTargetBlue.y][pTargetBlue.x] == "O") return -1;
        
        if (Grid[pTargetRed.y][pTargetRed.x] == "#") pTargetRed = pRed;
        if (Grid[pTargetBlue.y][pTargetBlue.x] == "#") pTargetBlue = pBlue;

        if (pTargetRed.y == pTargetBlue.y && pTargetRed.x == pTargetBlue.x)
        {
            pTargetRed = pRed;
            pTargetBlue = pBlue;
        }

        if (pTargetRed.y == pRed.y && pTargetRed.x == pRed.x && pTargetBlue.y == pBlue.y && pTargetBlue.x == pBlue.x) break;

        pRed = pTargetRed;
        pBlue = pTargetBlue;
    }

    Grid[info.yRed][info.xRed] = ".";
    Grid[info.yBlue][info.xBlue] = ".";
    Grid[pRed.y][pRed.x] = "R";
    Grid[pBlue.y][pBlue.x] = "B";

    info.yRed = pRed.y;
    info.xRed = pRed.x;
    info.yBlue = pBlue.y;
    info.xBlue = pBlue.x;

    return outcome;
}

void solution(vector<vector<string>> Grid, Info info, const int& iIter)
{
    if (result != -1 && result <= iIter) return;
    if (iIter > 10) return;

    if (iIter != 0)
    {
        int outcome = tiltBoard(Grid, info);
        //printGrid(Grid);
        if (outcome == 1)
        {
            result = iIter;
            return;
        }
        else if (outcome == -1)
        {
            return;
        }
    }

    for (int idx = 0; idx < 4; idx++)
    {
        if (iIter + 1 > 10) break;
        Info tempinfo = info;
        tempinfo.iTiltMode = idx;
        solution(Grid, tempinfo, iIter + 1);
    }
}

bool BFS()
{
    vector<vector<bool>> bVisited(N, vector<bool>(M));
    queue<pair<Pos, int>> q;
    q.push({ pO, 0 });
    bVisited[pO.y][pO.x] = true;

    while (!q.empty())
    {
        Pos v = q.front().first;
        int iDepth = q.front().second;
        q.pop();
        
        if (Grid[v.y][v.x] == "R")
        {
            return true;
        }

        for (int dir = 0; dir < 4; dir++)
        {
            int iTargetR = v.y + dy[dir];
            int iTargetC = v.x + dx[dir];

            if (Grid[iTargetR][iTargetC] == "#") continue;
            if (bVisited[iTargetR][iTargetC]) continue;

            bVisited[iTargetR][iTargetC] = true;
            q.push({{ iTargetR, iTargetC }, iDepth + 1});
        }
    }

    return false;
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N >> M;
    Grid = vector<vector<string>>(N, vector<string>(M));
    Info initinfo;

    for (int r = 0; r < N; r++)
    {
        string input;
        cin >> input;

        for (int c = 0; c < M; c++)
        {
            Grid[r][c] = input[c];

            if (Grid[r][c] == "R")
            {
                initinfo.yRed = r;
                initinfo.xRed = c;
            }
            else if (Grid[r][c] == "B")
            {
                initinfo.yBlue = r;
                initinfo.xBlue = c;
            }
            else if (Grid[r][c] == "O")
            {
                pO = {r, c};
            }
        }
    }

    //printGrid(Grid);
    if (!BFS())
    {
        cout << -1;
    }
    else
    {
        solution(Grid, initinfo, 0);
        cout << result;
    }

    return 0;
}