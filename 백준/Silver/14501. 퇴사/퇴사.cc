#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Work
{
	int iDurtaion;
	int iProfit;
};

int N;
int iMaxProfit = 0;

vector<Work> vWork;

void findProfit(const vector<bool>& Container)
{
	int iProfit = 0;

	int idx = 0;
	while (idx < N)
	{
		if (Container[idx])
		{
			if (idx + vWork[idx].iDurtaion > N) break;

			iProfit += vWork[idx].iProfit;
			idx += vWork[idx].iDurtaion;
		}
		else
		{
			idx++;
		}
	}

	if (iProfit > iMaxProfit) iMaxProfit = iProfit;
}

vector<bool> Container(15);
void Solution(const int& nowPos)
{
	if (nowPos == N)
	{
		findProfit(Container);
		return;
	}

	Container[nowPos] = true;
	Solution(nowPos + 1);

	Container[nowPos] = false;
	Solution(nowPos + 1);
}

int main()
{
	//fstream txt_input("input.txt");
	cin >> N;

	for (int idx = 0; idx < N; idx++)
	{
		int T, P;
		cin >> T >> P;
		vWork.push_back({ T, P });
	}

	Solution(0);

	cout << iMaxProfit;

	return 0;
}