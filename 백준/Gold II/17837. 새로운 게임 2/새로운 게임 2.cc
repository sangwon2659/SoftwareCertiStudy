/*
[1시간 40분]
어떻게 말을 매번 순서대로 자유롭게 이렇게 붙였다 저렇게 붙였다 할지 고민해보고 시작하는 게 매우 중요했음
Grid에는 Stack을 사용하고 잠깐 뺏다가 다시 넣는 Temp Container 용도로는 Deque를 사용하는 게 좋은 아이디어였음
Turn이 끝날 때마다 보는 게 아니라 말을 움직일 때마다 4개 이상인 경우가 있는지를 보는 게 핵심이었음 <- 이것 때문에 디버깅 오래 걸림...
디버깅할 때 Grid의 크기를 6으로 줄여놨다가 제출을 해서 Error가 남... 이런 부분 조심해야할 듯
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <deque>

using namespace std;

struct PlayerPos
{
    int y;
    int x;
};

struct PlayerInfo
{
    int iPlayerID;
    int iDir;
};

struct GridInfo
{
    string color;
    stack<PlayerInfo> stkPlayers;
};

int N, K;
vector<PlayerPos> vPlayers;
GridInfo Grid[12][12];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

bool isAnyWithFourPlayers()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (Grid[r][c].stkPlayers.size() >= 4) return true;
        }
    }

    return false;
}

bool movePlayers()
{
    for (int iPlayerIdx = 0; iPlayerIdx < K; iPlayerIdx++)
    {
        int iPlayerY = vPlayers[iPlayerIdx].y;
        int iPlayerX = vPlayers[iPlayerIdx].x;
        deque<PlayerInfo> dTemp;

        while (Grid[iPlayerY][iPlayerX].stkPlayers.top().iPlayerID != iPlayerIdx)
        {
            dTemp.push_back(Grid[iPlayerY][iPlayerX].stkPlayers.top());
            Grid[iPlayerY][iPlayerX].stkPlayers.pop();
        }

        dTemp.push_back(Grid[iPlayerY][iPlayerX].stkPlayers.top());
        Grid[iPlayerY][iPlayerX].stkPlayers.pop();

        int iPlayerDir = dTemp.back().iDir;
        int iTargetY = iPlayerY + dy[iPlayerDir % 4];
        int iTargetX = iPlayerX + dx[iPlayerDir % 4];

        if (iTargetY < 0 || iTargetY >= N || iTargetX < 0 || iTargetX >= N || Grid[iTargetY][iTargetX].color == "Blue")
        {
            iPlayerDir += 2;
            dTemp.back().iDir += 2;

            iTargetY = iPlayerY + dy[iPlayerDir % 4];
            iTargetX = iPlayerX + dx[iPlayerDir % 4];
        }

        if (iTargetY < 0 || iTargetY >= N || iTargetX < 0 || iTargetX >= N)
        {
            while (!dTemp.empty())
            {
                Grid[iPlayerY][iPlayerX].stkPlayers.push(dTemp.back());
                dTemp.pop_back();
            }

            continue;
        }

        string strBlockColor = Grid[iTargetY][iTargetX].color;

        if (strBlockColor == "Blue")
        {
            while (!dTemp.empty())
            {
                Grid[iPlayerY][iPlayerX].stkPlayers.push(dTemp.back());
                dTemp.pop_back();
            }
        }
        else if (strBlockColor == "White")
        {
            while (!dTemp.empty())
            {
                Grid[iTargetY][iTargetX].stkPlayers.push(dTemp.back());
                vPlayers[dTemp.back().iPlayerID].y = iTargetY;
                vPlayers[dTemp.back().iPlayerID].x = iTargetX;
                dTemp.pop_back();
            }
        }
        else
        {
            while (!dTemp.empty())
            {
                Grid[iTargetY][iTargetX].stkPlayers.push(dTemp.front());
                vPlayers[dTemp.front().iPlayerID].y = iTargetY;
                vPlayers[dTemp.front().iPlayerID].x = iTargetX;
                dTemp.pop_front();
            }
        }

        if (isAnyWithFourPlayers())
        {
            return true;
        }
    }

    return false;
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N >> K;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            int iColor;
            cin >> iColor;
            if (iColor == 0) Grid[r][c].color = "White";
            else if (iColor == 1) Grid[r][c].color = "Red";
            else Grid[r][c].color = "Blue";
        }
    }
    for (int iPlayerIdx = 0; iPlayerIdx < K; iPlayerIdx++)
    {
        int y, x, iDir;
        cin >> y >> x >> iDir;

        vPlayers.push_back({(y - 1), (x - 1)});

        if (iDir == 1) iDir = 40001;
        else if (iDir == 2) iDir = 40003;
        else if (iDir == 3) iDir = 40000;
        else iDir = 40002;

        Grid[y - 1][x - 1].stkPlayers.push({iPlayerIdx, iDir});
    }

    int iTurn = 1;
    while (iTurn <= 1000)
    {
        if (movePlayers())
        {
            cout << iTurn;
            return  0;
        }

        iTurn++;
    }

    cout << -1;

    return 0;
}
