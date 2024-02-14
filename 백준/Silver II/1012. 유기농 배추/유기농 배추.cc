#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

int T, M, N, K;
int Grid[50][50];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

struct Pos
{
	int r;
	int c;
};

void dfs(const Pos input)
{
	if (Grid[input.r][input.c] == 2) return;
	
	Grid[input.r][input.c] = 2;

	for (int dir = 0; dir < 4; dir++)
	{
		int target_r = input.r + dy[dir];
		int target_c = input.c + dx[dir];
		if (target_r < 0 || target_r >= N || target_c < 0 || target_c >= M) continue;
		if (Grid[target_r][target_c] != 1) continue;
		dfs({ target_r, target_c });
	}
}

int main()
{
	//ifstream txt_input("input.txt");
	cin >> T;
	for (int testcase = 0; testcase < T; testcase++)
	{
		int cnt = 0;
		for (int r = 0; r < 50; r++)
		{
			for (int c = 0; c < 50; c++)
			{
				Grid[r][c] = 0;
			}
		}

		cin >> M >> N >> K;
		for (int i = 0; i < K; i++)
		{
			int r, c;
			cin >> c >> r;
			Grid[r][c] = 1;
		}

		for (int r = 0; r < N; r++)
		{
			for (int c = 0; c < M; c++)
			{
				if (Grid[r][c] == 1)
				{
					Pos input = { r, c };
					dfs(input);
					cnt++;
				}
			}
		}

		cout << cnt << endl;
	}


	return 0;
}