/*
[2시간]
이상하게 집중이 잘 안돼서 오래 걸렸다.
Combination으로 풀면 금방 풀리는 문제였다.
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N;
int iSmallestDiff = 1000000000;
vector<int> Container(20);
vector<vector<int>> Grid;

int findPerformanceDiff(const vector<int>& input)
{
	int resultDiff;
	int resultA = 0;
	int resultB = 0;
	vector<bool> isUsed(20);

	for (int i = 0; i < N / 2; i++)
	{
		isUsed[input[i]] = true;
		for (int j = 0; j < N / 2; j++)
		{
			resultA += Grid[input[i]][input[j]];
		}
	}

	for (int i = 0; i < N; i++)
	{
		if (isUsed[i]) continue;
		for (int j = 0; j < N; j++)
		{
			if (isUsed[j]) continue;
			resultB += Grid[i][j];
		}
	}

	resultDiff = abs(resultA - resultB);
	return resultDiff;
}

void Solution(const int& nowPos, const int& nowVal)
{
	if (nowPos == N / 2)
	{
		int result = findPerformanceDiff(Container);
		if (result < iSmallestDiff) iSmallestDiff = result;

		/*
		cout << "Result: " << result << endl;
		for (int idx = 0; idx < N / 2; idx++)
		{
			cout << Container[idx] << " ";
		}
		cout << endl;
		cout << "=======================" << endl;
		*/
	}

	for (int idx = nowVal; idx < N; idx++)
	{
		Container[nowPos] = idx;
		Solution(nowPos + 1, idx + 1);
	}
}

int main()
{
	//fstream txt_input("input.txt");
	cin >> N;
	Grid = vector<vector<int>>(N, vector<int>(N));
	
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			int input;
			cin >> input;
			Grid[r][c] = input;
		}
	}

	Solution(0, 0);
	cout << iSmallestDiff;

	return 0;
}
