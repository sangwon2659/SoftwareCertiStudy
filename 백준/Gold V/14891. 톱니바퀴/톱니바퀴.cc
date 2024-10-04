#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <fstream>

using namespace std;

vector<vector<int>> vGear(4, vector<int>(8));
int K;

struct Info
{
	int idx;
	int iMode;
};

vector<int> rotateGear(const int& idx, int iMode)
{
	vector<int> result;

	if (iMode == 1)
	{
		result.push_back(vGear[idx][7]);
		for (int idx_ = 0; idx_ < 7; idx_++)
		{
			result.push_back(vGear[idx][idx_]);
		}
	}
	else if (iMode == -1)
	{
		for (int idx_ = 1; idx_ < 8; idx_++)
		{
			result.push_back(vGear[idx][idx_]);
		}
		result.push_back(vGear[idx][0]);
	}

	return result;
}

void printGear()
{
	vector<vector<string>> result(5, vector<string>(20));

	for (int r = 0; r < 4; r++)
	{
		if (vGear[r][0]) result[0][2 + (r * 5)] = "S";
		else result[0][2 + (r * 5)] = "N";

		if (vGear[r][1]) result[1][3 + (r * 5)] = "S";
		else result[1][3 + (r * 5)] = "N";

		if (vGear[r][2]) result[2][4 + (r * 5)] = "S";
		else result[2][4 + (r * 5)] = "N";

		if (vGear[r][3]) result[3][3 + (r * 5)] = "S";
		else result[3][3 + (r * 5)] = "N";

		if (vGear[r][4]) result[4][2 + (r * 5)] = "S";
		else result[4][2 + (r * 5)] = "N";

		if (vGear[r][5]) result[3][1 + (r * 5)] = "S";
		else result[3][1 + (r * 5)] = "N";

		if (vGear[r][6]) result[2][0 + (r * 5)] = "S";
		else result[2][0 + (r * 5)] = "N";

		if (vGear[r][7]) result[1][1 + (r * 5)] = "S";
		else result[1][1 + (r * 5)] = "N";
	}

	for (int r = 0; r < 5; r++)
	{
		for (int c = 0; c < 20; c++)
		{
			if (result[r][c] == "") cout << " ";
			else cout << result[r][c];
		}

		cout << endl;
	}
	cout << endl;
}

void BFS(const Info& init)
{
	bool bVisited[4] = { 0 };
	queue<Info> q;
	q.push(init);
	bVisited[init.idx] = true;

	while (!q.empty())
	{
		Info v = q.front();
		q.pop();

		if (v.iMode == 0) continue;
		vector<int> result = rotateGear(v.idx, v.iMode);

		if (v.idx + 1 <= 3)
		{
			if (!bVisited[v.idx + 1])
			{
				int iMode = 0;
				if (vGear[v.idx][2] != vGear[v.idx + 1][6]) iMode = v.iMode * -1;
				q.push({ v.idx + 1, iMode });
				bVisited[v.idx + 1] = true;
			}
		}

		if (v.idx - 1 >= 0)
		{
			if (!bVisited[v.idx - 1])
			{
				int iMode = 0;
				if (vGear[v.idx][6] != vGear[v.idx - 1][2]) iMode = v.iMode * -1;
				q.push({ v.idx - 1, iMode });
				bVisited[v.idx - 1] = true;
			}
		}

		vGear[v.idx] = result;
	}
}

int countScore()
{
	int iScore = 0;

	if (vGear[0][0] == 1) iScore += 1;
	if (vGear[1][0] == 1) iScore += 2;
	if (vGear[2][0] == 1) iScore += 4;
	if (vGear[3][0] == 1) iScore += 8;

	return iScore;
}

int main()
{
	//fstream txt_input("input.txt");
	for (int r = 0; r < 4; r++)
	{
		string input;
		cin >> input;

		for (int c = 0; c < 8; c++)
		{
			vGear[r][c] = input[c] - '0';
		}
	}

	cin >> K;

	for (int iter = 0; iter < K; iter++)
	{
		int idx, iMode;
		cin >> idx >> iMode;

		//printGear();
		BFS({ idx - 1, iMode });
	}

	cout << countScore();

	return 0;
}
