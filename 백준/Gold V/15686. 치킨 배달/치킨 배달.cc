/*
[1시간]
전형적인 Combination 써서 경우의 수 보는 문제
Max값을 1000으로 너무 낮게 줘서 Error 뜸
Min을 찾을 때의 초기 Max 값은 최대한 크게 주자
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Pos
{
    int y;
    int x;
};

//ifstream txt_input("input.txt");
int N, M;
int num;
vector<Pos> vectorHouse;
vector<Pos> vectorChicken;
vector<Pos> vectorChickenCandidate;
int resultTotalDist = 100000;

int sumChickenDist()
{
    int totalDist = 0;
    for (auto house : vectorHouse)
    {
        int nowDist = 100000;
        for (auto chicken : vectorChickenCandidate)
        {
            int dist = abs(house.y - chicken.y) + abs(house.x - chicken.x);
            if (dist < nowDist)
            {
                nowDist = dist;
            }
        }

        totalDist += nowDist;
    }

    return totalDist;
}

void Combination(const int& idx)
{
    if (vectorChickenCandidate.size() == M)
    {
        int nowSumChickenDist = sumChickenDist();
        if (nowSumChickenDist < resultTotalDist)
        {
            resultTotalDist = nowSumChickenDist;
        }
        return;
    }

    for (int i = idx; i < vectorChicken.size(); i++)
    {
        vectorChickenCandidate.push_back(vectorChicken[i]);
        Combination(i + 1);
        vectorChickenCandidate.erase(vectorChickenCandidate.end() - 1);
    }
}

int main()
{
    cin >> N >> M;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            cin >> num;
            if (num == 1)
            {
                vectorHouse.push_back({r, c});
            }
            else if (num == 2)
            {
                vectorChicken.push_back({r, c});
            }
        }
    }

    Combination(0);
    cout << resultTotalDist;

    return 0;
}
