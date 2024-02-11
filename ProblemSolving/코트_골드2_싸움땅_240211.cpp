/*
[2시간 40분]
빡구현 문제
PlayerDropGunAndMove함수에서
  targetR = nowR + dy[vectorPlayers[playerIdx].dir % 4];
  targetC = nowC + dx[vectorPlayers[playerIdx].dir % 4];
부분을 nowR & nowC가 아닌 vectorPlayers[playerIdx].y & vectorPlayers[playerIdx].x로 해서 계속 틀림...
(targetR, targetC로 들어가서 다시 한번 더 targetR, targetC를 찾는 구조인데 그냥 nowR, nowC 이런 식으로 알아볼 수 없게 변수명을 정하니까 헷갈렸던 거)
시간이 좀 들더라도 변수 제대로 설정하는 게 디버깅 하는 데 훨씬 편할 듯
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct PlayerStatus
{
    int ID;
    int y;
    int x;
    int dir;
    int initialAbility;
    int Gun = 0;
    int Point = 0;
};

struct GridStatus
{
    vector<int> vectorGun;
    vector<int> playerID;
};

ifstream txt_input("input.txt");
int n, m, k;
GridStatus grid[20][20];
GridStatus tempGrid[20][20];
vector<PlayerStatus> vectorPlayers;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

void PlayerGetGun(const int& playerIdx, const int& nowR, const int& nowC)
{
    if (grid[nowR][nowC].vectorGun.size() > 0)
    {
        sort(grid[nowR][nowC].vectorGun.begin(), grid[nowR][nowC].vectorGun.end(), greater<>());

        if (vectorPlayers[playerIdx].Gun == 0)
        {
            vectorPlayers[playerIdx].Gun = grid[nowR][nowC].vectorGun[0];
            grid[nowR][nowC].vectorGun.erase(grid[nowR][nowC].vectorGun.begin());
        }
        else
        {
            if (grid[nowR][nowC].vectorGun[0] > vectorPlayers[playerIdx].Gun)
            {
                grid[nowR][nowC].vectorGun.push_back(vectorPlayers[playerIdx].Gun);
                vectorPlayers[playerIdx].Gun = grid[nowR][nowC].vectorGun[0];
                grid[nowR][nowC].vectorGun.erase(grid[nowR][nowC].vectorGun.begin());
            }
        }
    }
}

void PlayerDropGunAndMove(const int& playerIdx, const int& nowR, const int& nowC)
{
    if (vectorPlayers[playerIdx].Gun != 0)
    {
        grid[nowR][nowC].vectorGun.push_back(vectorPlayers[playerIdx].Gun);
        vectorPlayers[playerIdx].Gun = 0;
    }

    int targetR = nowR + dy[vectorPlayers[playerIdx].dir % 4];
    int targetC = nowC + dx[vectorPlayers[playerIdx].dir % 4];

    while (true)
    {
        if (targetR < 0 || targetR >= n || targetC < 0 || targetC >= n || grid[targetR][targetC].playerID.size() != 0)
        {
            vectorPlayers[playerIdx].dir++;
            targetR = nowR + dy[vectorPlayers[playerIdx].dir % 4];
            targetC = nowC + dx[vectorPlayers[playerIdx].dir % 4];
        }
        else
        {
            break;
        }
    }

    vectorPlayers[playerIdx].y = targetR;
    vectorPlayers[playerIdx].x = targetC;
    grid[targetR][targetC].playerID.push_back(playerIdx);

    PlayerGetGun(playerIdx, targetR, targetC);
}

void RunRound()
{
    for (int playerIdx = 0; playerIdx < m; playerIdx++)
    {
        int targetR = vectorPlayers[playerIdx].y + dy[vectorPlayers[playerIdx].dir % 4];
        int targetC = vectorPlayers[playerIdx].x + dx[vectorPlayers[playerIdx].dir % 4];

        if (targetR < 0 || targetR >= n || targetC < 0 || targetC >= n)
        {
            vectorPlayers[playerIdx].dir += 2;
            targetR = vectorPlayers[playerIdx].y + dy[vectorPlayers[playerIdx].dir % 4];
            targetC = vectorPlayers[playerIdx].x + dx[vectorPlayers[playerIdx].dir % 4];
        }

        if (grid[targetR][targetC].playerID.size() == 0)
        {
            grid[vectorPlayers[playerIdx].y][vectorPlayers[playerIdx].x].playerID.clear();

            PlayerGetGun(playerIdx, targetR, targetC);

            vectorPlayers[playerIdx].y = targetR;
            vectorPlayers[playerIdx].x = targetC;

            grid[targetR][targetC].playerID.push_back(playerIdx);
        }
        else
        {
            int winner;
            int loser;

            if (vectorPlayers[playerIdx].initialAbility + vectorPlayers[playerIdx].Gun > 
            vectorPlayers[grid[targetR][targetC].playerID[0]].initialAbility + vectorPlayers[grid[targetR][targetC].playerID[0]].Gun)
            {
                winner = playerIdx;
                loser = grid[targetR][targetC].playerID[0];
            }
            else if (vectorPlayers[playerIdx].initialAbility + vectorPlayers[playerIdx].Gun == 
            vectorPlayers[grid[targetR][targetC].playerID[0]].initialAbility + vectorPlayers[grid[targetR][targetC].playerID[0]].Gun)
            {
                if (vectorPlayers[playerIdx].initialAbility > vectorPlayers[grid[targetR][targetC].playerID[0]].initialAbility)
                {
                    winner = playerIdx;
                    loser = grid[targetR][targetC].playerID[0];
                }
                else
                {
                    winner = grid[targetR][targetC].playerID[0];
                    loser = playerIdx;
                }
            }
            else
            {
                winner = grid[targetR][targetC].playerID[0];
                loser = playerIdx;
            }

            vectorPlayers[winner].Point += 
                abs((vectorPlayers[winner].initialAbility + vectorPlayers[winner].Gun) - 
                (vectorPlayers[loser].initialAbility + vectorPlayers[loser].Gun));

            grid[vectorPlayers[winner].y][vectorPlayers[winner].x].playerID.clear();
            grid[vectorPlayers[loser].y][vectorPlayers[loser].x].playerID.clear();

            PlayerDropGunAndMove(loser, targetR, targetC);
            PlayerGetGun(winner, targetR, targetC);

            vectorPlayers[winner].y = targetR;
            vectorPlayers[winner].x = targetC;

            grid[targetR][targetC].playerID.push_back(winner);
        }
    }
}

int main()
{
    txt_input >> n >> m >> k;
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            int gun;
            txt_input >> gun;
            if (gun > 0) grid[r][c].vectorGun.push_back(gun);
        }
    }
    for (int iter = 0; iter < m; iter++)
    {
        int x, y, d, s;
        txt_input >> y >> x >> d >> s;
        vectorPlayers.push_back({iter, y - 1, x - 1, d + 40000, s});
        grid[y - 1][x - 1].playerID.push_back(iter);
    }

    for (int round = 0; round < k; round++)
    {
        RunRound();
    }

    for (auto player : vectorPlayers)
    {
        cout << player.Point << " ";
    }

    return 0;
}
