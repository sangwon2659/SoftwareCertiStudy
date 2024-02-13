/*
[2시간 40분]
문제를 처음에 제대로 이해 못 해서, 같은 Depth에서의 모든 경우의 수 중에서 다시 행과 열을 비교해서 가장 우선순위를 정해야 되는 걸 모르고 구현함
이해한 후 새로 구현했을 때는 꼭 하나 더 깊이 들어가야만 Vector를 비교해서 ClosestCustomer를 Return 하게끔 잘 못 짜서 또 고생 함...
(분명히 Customer가 있는데 -10으로 Return 해버리는 문제가 자꾸 발생함)
이런 예외 Case를 어떻게 해야 잘 생각할 수 있을지 고민이 필요함

BFS를 돌릴 때
Depth를 Tracking하고 싶으면 Queue에 들어가는 자료형에 Int 하나 추가해서 돌리면서
Push를 할 때 +1 이런 식으로 하면 됨
한 Depth가 다 돌았을 때 뭘 하고 싶으면 maxNum을 정해놓고 이 Depth가 이 maxNum 보다 커지면 그때가 사이클의 마지막 루프임
(더 깊은 Depth가 없을 것을 대비해 While문 밖에도 마지막 Depth에 대한 실행문 추가해줘야 함)
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

struct taxiInfo
{
    int y;
    int x;
    int gas;
};

struct GridPos
{
    int customerID = -1;
    bool bIsWall = false;
};

struct PosBFS
{
    int y;
    int x;
    int distance;
};

struct Pos
{
    int y;
    int x;
};

int N, M, gas;
taxiInfo taxi;
vector<Pos> vectorCustomerDestination;
int dy[4] = {-1, 0, 0, 1};
int dx[4] = {0, -1, 1, 0};
GridPos grid[20][20];

PosBFS FindBestClosestCustomer(vector<PosBFS> vectorClosestCustomerCandidate)
{
    if (vectorClosestCustomerCandidate.size() == 1) return vectorClosestCustomerCandidate[0];

    sort(vectorClosestCustomerCandidate.begin(), vectorClosestCustomerCandidate.end(), [](const PosBFS& P1, const PosBFS& P2)
    {
        return P1.x < P2.x;
    });
    sort(vectorClosestCustomerCandidate.begin(), vectorClosestCustomerCandidate.end(), [](const PosBFS& P1, const PosBFS& P2)
    {
        return P1.y < P2.y;
    });

    return vectorClosestCustomerCandidate[0];
}

PosBFS FindClosestCustomerLocation(const int& taxiY, const int& taxiX)
{
    bool bVisited[20][20] = {0};
    queue<PosBFS> q;
    vector<PosBFS> vectorClosestCustomerCandidate;
    int maxDist = 100000;
    q.push({taxiY, taxiX, 0});

    while (!q.empty())
    {
        PosBFS v = q.front();
        q.pop();

        if (bVisited[v.y][v.x]) continue;
        if (v.distance > taxi.gas)
        {
            return {-1, -1, -1};
        }

        if (v.distance > maxDist)
        {
            return FindBestClosestCustomer(vectorClosestCustomerCandidate);
        }

        if (grid[v.y][v.x].customerID > -1)
        {
            vectorClosestCustomerCandidate.push_back(v);
            maxDist = v.distance;
        }

        bVisited[v.y][v.x] = true;

        for (int dir = 0; dir < 4; dir++)
        {
            int targetR = v.y + dy[dir];
            int targetC = v.x + dx[dir];

            if (targetR < 0 || targetR >= N || targetC < 0 || targetC >= N || grid[targetR][targetC].bIsWall || bVisited[targetR][targetC])
            {
                continue;
            }

            q.push({targetR, targetC, v.distance + 1});
        }
    }

    if (vectorClosestCustomerCandidate.size() > 0)
    {
        return FindBestClosestCustomer(vectorClosestCustomerCandidate);
    }

    return {-10, -10, -10};
}

PosBFS BringCustomerToDestination(const int& taxiY, const int& taxiX, const int& destY, const int& destX)
{
    bool bVisited[20][20] = {0};
    queue<PosBFS> q;
    q.push({taxiY, taxiX, 0});

    while (!q.empty())
    {
        PosBFS v = q.front();
        q.pop();

        if (bVisited[v.y][v.x]) continue;
        if (v.distance > taxi.gas)
        {
            return {-1, -1, -1};
        }

        if (v.y == destY && v.x == destX)
        {
            return v;
        }

        bVisited[v.y][v.x] = true;

        for (int dir = 0; dir < 4; dir++)
        {
            int targetR = v.y + dy[dir];
            int targetC = v.x + dx[dir];

            if (targetR < 0 || targetR >= N || targetC < 0 || targetC >= N || grid[targetR][targetC].bIsWall || bVisited[targetR][targetC])
            {
                continue;
            }

            q.push({targetR, targetC, v.distance + 1});
        }
    }

    return {-10, -10, -10};
}

int main()
{
    ifstream txt_input("input.txt");
    txt_input >> N >> M >> gas;
    
    //Grid Input
    int gridNum;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            txt_input >> gridNum;
            if (gridNum)
            {
                grid[r][c].bIsWall = true;
            }
        }
    }
    
    //Taxi Input
    int y, x;
    txt_input >> y >> x;
    taxi.y = y - 1;
    taxi.x = x - 1;
    taxi.gas = gas;

    //Customer Input
    for (int customerID = 0; customerID < M; customerID++)
    {
        txt_input >> y >> x;
        grid[y - 1][x - 1].customerID = customerID;
        txt_input >> y >> x;
        vectorCustomerDestination.push_back({y - 1, x - 1});
    }

    for (int DriveNum = 0; DriveNum < M; DriveNum++)
    {
        PosBFS closestCustomerInfo = FindClosestCustomerLocation(taxi.y, taxi.x);
        if (closestCustomerInfo.x == -1 || closestCustomerInfo.x == -10)
        {
            cout << -1;
            return 0;
        }
        else
        {
            taxi.y = closestCustomerInfo.y;
            taxi.x = closestCustomerInfo.x;
            taxi.gas -= closestCustomerInfo.distance;
        }

        Pos closestCustomerDestination = vectorCustomerDestination[grid[closestCustomerInfo.y][closestCustomerInfo.x].customerID];
        PosBFS customerDestinationInfo = BringCustomerToDestination(taxi.y, taxi.x, closestCustomerDestination.y, closestCustomerDestination.x);
        if (customerDestinationInfo.x == -1 || closestCustomerInfo.x == -10)
        {
            cout << -1;
            return 0;
        }
        else
        {
            taxi.y = customerDestinationInfo.y;
            taxi.x = customerDestinationInfo.x;
            taxi.gas -= customerDestinationInfo.distance;
            taxi.gas += 2 * customerDestinationInfo.distance;
        }

        grid[closestCustomerInfo.y][closestCustomerInfo.x].customerID = -1;
    }

    cout << taxi.gas;

    return 0;
}
