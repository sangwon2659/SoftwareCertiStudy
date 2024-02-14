/*
[24년 이전에 푼 거]
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Pos
{
	int r;
	int c;
};

int N, M;
vector<vector<int>> Grid(300, vector<int>(300));
vector<Pos> Ice;
bool visited[10000];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

void iceMelt()
{
	int target_r, target_c, cnt;
	vector<Pos> temp_Ice;
	vector<vector<int>> temp_Grid(300, vector<int>(300));

	for (auto IcePos : Ice)
	{
		cnt = 0;
		for (int dir = 0; dir < 4; dir++)
		{
			target_r = IcePos.r + dy[dir];
			target_c = IcePos.c + dx[dir];

			if (Grid[target_r][target_c] == 0) cnt++;
		}

		if (Grid[IcePos.r][IcePos.c] - cnt > 0)
		{
			temp_Ice.push_back({ IcePos.r, IcePos.c });
			temp_Grid[IcePos.r][IcePos.c] = Grid[IcePos.r][IcePos.c] - cnt;
		}
	}

	Ice = temp_Ice;
	Grid = temp_Grid;
}

bool isIceOneChunk()
{
	queue<Pos> q;
	q.push(Ice[0]);
	vector<vector<int>> temp_Grid(300, vector<int>(300));
	temp_Grid = Grid;

	bool ret = true;
	int cnt = 0;

	while (!q.empty())
	{
		Pos v = q.front();
		q.pop();

		if (temp_Grid[v.r][v.c] == -1) continue;
		temp_Grid[v.r][v.c] = -1;
		cnt++;

		for (int dir = 0; dir < 4; dir++)
		{
			int target_r = v.r + dy[dir];
			int target_c = v.c + dx[dir];
			if (temp_Grid[target_r][target_c] > 0)
			{
				q.push({ target_r, target_c });
			}
		}
	}

	if (cnt != Ice.size()) ret = false;

	return ret;
}

int main()
{
	//ifstream txt_input("input.txt");
	cin >> N >> M;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			cin >> Grid[r][c];
			if (Grid[r][c] > 0) Ice.push_back({ r, c });
		}
	}

	int year_cnt = 0;
	while (isIceOneChunk())
	{
		iceMelt();

		if (Ice.size() == 0)
		{
			cout << 0;
			return 0;
		}

		year_cnt++;
	}

	cout << year_cnt;

	return 0;
}
