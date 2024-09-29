/*
[4시간]
BFS의 개념에 대해 다시 생각해보게 됨...
그냥 외워서 쓰지 말고 진짜 이해를 하려고 노력해보자
*/

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int N, K;
int iSteps, iCount;

struct Info
{
    int iNowLocation;
    int iDepth;
};

int moveLocation(const int& iNowLocation, const int& iMovement)
{
    if (iMovement == 0)
    {
        return iNowLocation + 1;
    }
    else if (iMovement == 1)
    {
        return iNowLocation - 1;
    }
    else
    {
        return iNowLocation * 2;
    }
}

void BFS()
{
    bool bIsVisited[100001] = {0};
    queue<Info> q;
    q.push({N, 0});
    bIsVisited[N] = true;

    while (!q.empty())
    {
        Info v = q.front();
        q.pop();

        if (v.iNowLocation == K)
        {
            int iMinDepth = v.iDepth;
            iSteps = iMinDepth;
            iCount++;

            while (!q.empty())
            {
                Info p = q.front();
                q.pop();

                if (p.iDepth > iMinDepth) break;
                if (p.iNowLocation == K) iCount++;
            }

            return;
        }

	// 여기에 if(bIsVisited[v.iNowLocation]) continue;를 안넣는 것 매우 중요
        // 5 -> 10 -> 11(K)
        // 9 -> 10 -> 11(K)
	// 위의 2 경우다 iCount에 포함시켜야 하기 때문
        bIsVisited[v.iNowLocation] = true;

        for (int iMovementIDX = 0; iMovementIDX < 3; iMovementIDX++)
        {
            int result = moveLocation(v.iNowLocation, iMovementIDX);
            
            if (result < 0 || result > 100000) continue;
            if (bIsVisited[result]) continue;
            
            q.push({result, v.iDepth + 1});
        }
    }
}

int main()
{
    //fstream txt_input("input.txt");
    cin >> N >> K;

    BFS();
    cout << iSteps << endl;
    cout << iCount << endl;

    return 0;
}
