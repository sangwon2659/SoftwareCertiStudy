#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct Pos
{
	int r;
	int c;
};

int M, N;
int Grid[1000][1000];
queue<Pos> q;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

void bfs()
{
	while (!q.empty())
	{
		Pos v = q.front();
		q.pop();
		
		for (int dir = 0; dir < 4; dir++)
		{
			int target_r = v.r + dy[dir];
			int target_c = v.c + dx[dir];

			if (target_r < 0 || target_r >= N || target_c < 0 || target_c >= M) continue;
			if (Grid[target_r][target_c] != 0) continue;

			Grid[target_r][target_c] = Grid[v.r][v.c] + 1;
			q.push({ target_r, target_c });
		}
	}
}

bool isAllMature()
{
	bool ret = true;

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			if (Grid[r][c] == 0) ret = false;
		}
	}

	return ret;
}

int findMax()
{
	int max = 0;

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			if (Grid[r][c] > max) max = Grid[r][c];
		}
	}

	return max;
}

int main()
{
	//ifstream txt_input("input.txt");
	cin >> M >> N;

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			int input;
			cin >> input;
			Grid[r][c] = input;
			if (input == 1) q.push({ r, c });
		}
	}

	if (isAllMature())
	{
		cout << 0;
		return 0;
	}

	bfs();

	if (!isAllMature())
	{
		cout << -1;
		return 0;
	}

	cout << findMax() - 1;
	return 0;
}