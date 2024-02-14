#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct Pos
{
	int r;
	int c;
};

int TestCaseNum, Length;
Pos GivenPos, TargetPos;
int Grid[300][300];
queue<Pos> q;

int dy[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

void bfs()
{
	while (!q.empty())
	{
		Pos v = q.front();
		q.pop();

		if (v.r == TargetPos.r && v.c == TargetPos.c)
		{
			cout << Grid[v.r][v.c] << endl;
			return;
		}

		for (int dir = 0; dir < 8; dir++)
		{
			int target_r = v.r + dy[dir];
			int target_c = v.c + dx[dir];

			if (target_c < 0 || target_c >= Length || target_r < 0 || target_r >= Length) continue;
			if (Grid[target_r][target_c] == 0)
			{
				q.push({ target_r, target_c });
				Grid[target_r][target_c] = Grid[v.r][v.c] + 1;
			}
		}
	}
}

void eraseGrid()
{
	for (int r = 0; r < Length; r++)
	{
		for (int c = 0; c < Length; c++)
		{
			Grid[r][c] = 0;
		}
	}
}

int main()
{
	//ifstream txt_input("input.txt");
	cin >> TestCaseNum;
	for (int TestCase = 0; TestCase < TestCaseNum; TestCase++)
	{
		cin >> Length;

		int a, b;
		cin >> a >> b;
		GivenPos = { a, b };
		cin >> a >> b;
		TargetPos = { a, b };
		q.push(GivenPos);
		if (GivenPos.r == TargetPos.r && GivenPos.c == TargetPos.c)
		{
			cout << 0 << endl;
			continue;
		}
		bfs();
		eraseGrid();
		while (!q.empty()) q.pop();
	}

	return 0;
}