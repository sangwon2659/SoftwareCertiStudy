#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int R, C, T;
int GridMap[50][50];

int dy[4] = { -1, 0, 1, 0 }; // N, E, S, W
int dx[4] = { 0, 1, 0, -1 };

struct Pos
{
	int r;
	int c;
};

vector<Pos> sterilizer_pos;

void particleSpread()
{
	int TempGridMap[50][50] = { 0 };
	TempGridMap[sterilizer_pos[0].r][sterilizer_pos[0].c] = -1;
	TempGridMap[sterilizer_pos[1].r][sterilizer_pos[1].c] = -1;

	// Compute the conditions and copy to TempGridMap
	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			int cntDir = 0;
			if (GridMap[r][c] > 0)
			{
				for (int dir = 0; dir < 4; dir++)
				{
					int target_r = r + dy[dir];
					int target_c = c + dx[dir];

					if (target_r < 0 || target_r >= R || target_c < 0 || target_c >= C) continue;
					if (target_r == sterilizer_pos[0].r && target_c == sterilizer_pos[0].c) continue;
					if (target_r == sterilizer_pos[1].r && target_c == sterilizer_pos[1].c) continue;
					
					TempGridMap[r + dy[dir]][c + dx[dir]] += GridMap[r][c] / 5;
					cntDir++;
				}

				TempGridMap[r][c] += GridMap[r][c] - (GridMap[r][c] / 5) * cntDir;
			}
		}
	}

	// Copy all TempGridMap to GridMap
	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			GridMap[r][c] = TempGridMap[r][c];
		}
	}
}

void sterilize()
{
	//// Counter-Clock-Wise ////
	int sterilizer_r = sterilizer_pos[0].r;
	int sterilizer_c = sterilizer_pos[0].c;

	// 4th Line
	GridMap[sterilizer_r - 1][0] = 0;
	for (int r = sterilizer_r - 1; r > 0; r--) GridMap[r][0] = GridMap[r - 1][0];

	// 3rd Line
	for (int c = 0; c < C - 1; c++) GridMap[0][c] = GridMap[0][c + 1];

	// 2nd Line
	for (int r = 0; r < sterilizer_r; r++) GridMap[r][C - 1] = GridMap[r + 1][C - 1];

	//1st Line
	for (int c = C - 1; c > 1; c--) GridMap[sterilizer_r][c] = GridMap[sterilizer_r][c - 1];
	GridMap[sterilizer_r][1] = 0;

	//// Clock-Wise ////
	sterilizer_r = sterilizer_pos[1].r;
	sterilizer_c = sterilizer_pos[1].c;

	// 4th Line
	GridMap[sterilizer_r + 1][0] = 0;
	for (int r = sterilizer_r + 1; r < R - 1; r++) GridMap[r][0] = GridMap[r + 1][0];

	// 3rd Line
	for (int c = 0; c < C - 1; c++) GridMap[R - 1][c] = GridMap[R - 1][c + 1];

	// 2nd Line
	for (int r = R - 1; r > sterilizer_r; r--) GridMap[r][C - 1] = GridMap[r - 1][C - 1];

	// 1st Line
	for (int c = C - 1; c > 1; c--) GridMap[sterilizer_r][c] = GridMap[sterilizer_r][c - 1];
	GridMap[sterilizer_r][1] = 0;
}

int main()
{
	/*
	ifstream txt_input("input.txt");
	txt_input >> R >> C >> T;

	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			txt_input >> GridMap[r][c];
			if (GridMap[r][c] == -1) sterilizer_pos.push_back({ r, c });
		}
	}
	*/

	cin >> R >> C >> T;

	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			cin >> GridMap[r][c];
			if (GridMap[r][c] == -1) sterilizer_pos.push_back({ r, c });
		}
	}

	for (int iteration = 0; iteration < T; iteration++)
	{
		particleSpread();
		sterilize();
	}

	int sum = 0;
	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			if (GridMap[r][c] != -1) sum += GridMap[r][c];
		}
	}

	cout << sum;

	return 0;
}