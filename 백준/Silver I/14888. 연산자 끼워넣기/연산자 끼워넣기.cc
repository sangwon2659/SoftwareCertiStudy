/*
[2시간]
iMaxResult, iMinResult를 10억1이 아닌 1억1로 해놔서 한참 고생함...
그리고 코드를 좀 간결하게 짜면 디버깅 하기 쉬울 듯...
참고:
int의 범위 -2,147,483,648 ~ 2,147,483,647
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N;
int iMaxResult = -1000000001;
int iMinResult = 1000000001;

vector<int> vA;
vector<int> vNumArith;
vector<int> Container(10);

void Solution(const int& iNowPos)
{
	if (iNowPos == N - 1)
	{
		int result = vA[0];

		for (int idx = 0; idx < N - 1; idx++)
		{
			if (Container[idx] == 0) result += vA[idx + 1];
			else if (Container[idx] == 1) result -= vA[idx + 1];
			else if (Container[idx] == 2) result *= vA[idx + 1];
			else if (Container[idx] == 3)
			{
				if (result > 0)
				{
					result = (int)(result / vA[idx + 1]);
				}
				else
				{
					result *= -1;
					result = (int)(result / vA[idx + 1]);
					result *= -1;
				}
			}
		}

		if (result > iMaxResult) iMaxResult = result;
		if (result < iMinResult) iMinResult = result;
	}

	for (int idx = 0; idx < 4; idx++)
	{
		if (vNumArith[idx] <= 0) continue;

		vNumArith[idx]--;
		Container[iNowPos] = idx;
		Solution(iNowPos + 1);
		vNumArith[idx]++;
	}
}

int main()
{
	//fstream txt_input("input.txt");
	cin >> N;

	for (int idx = 0; idx < N; idx++)
	{
		int A;
		cin >> A;
		vA.push_back(A);
	}

	for (int idx = 0; idx < 4; idx++)
	{
		int iNumArith;
		cin >> iNumArith;
		vNumArith.push_back(iNumArith);
	}

	Solution(0);

	cout << iMaxResult << endl;
	cout << iMinResult << endl;

	return 0;
}
