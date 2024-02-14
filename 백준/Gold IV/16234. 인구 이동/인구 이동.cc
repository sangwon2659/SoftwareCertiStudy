/*
[24년 이전에 푼 거]
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

struct Map_Coor
{
	int population;
	bool isOpen[5];
	bool isVisited;
};

struct Position
{
	int pos_y;
	int pos_x;
};

int N, L, R;
int dy[5] = { -10, 0, 0, -1, 1 };
int dx[5] = { -10, -1, 1, 0, 0, };
int open_sum = 0;
int open_cnt = 0;
int cnt = 0;
vector<Position> vec_open_positions;

void dfs(vector<vector<Map_Coor>>& base_map, const int& search_point_y, const int& search_point_x)
{
	if (base_map[search_point_y][search_point_x].isVisited == true) return;

	base_map[search_point_y][search_point_x].isVisited = true;
	vec_open_positions.push_back({ search_point_y, search_point_x });
	open_sum += base_map[search_point_y][search_point_x].population;
	open_cnt++;
	for (int dir = 1; dir <= 4; dir++)
		if (base_map[search_point_y][search_point_x].isOpen[dir] == true)
			dfs(base_map, search_point_y + dy[dir], search_point_x + dx[dir]);
}

int main()
{
	cin >> N >> L >> R;
	vector<vector<Map_Coor>> base_map(N + 1, vector<Map_Coor>(N + 1));

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			cin >> base_map[r][c].population;

	while (true)
	{
		bool continueLoop = false;

		for (int r = 1; r <= N; r++)
			for (int c = 1; c <= N; c++)
				for (int dir = 1; dir <= 4; dir++)
				{
					if (r + dy[dir] < 1 || r + dy[dir] > N || c + dx[dir] < 1 || c + dx[dir] > N) continue;
					int diff = abs(base_map[r][c].population - base_map[r + dy[dir]][c + dx[dir]].population);
					if (diff >= L && diff <= R)
					{
						base_map[r][c].isOpen[dir] = true;
						continueLoop = true;
					}
				}

		if (continueLoop == false) break;

		for (int r = 1; r <= N; r++)
			for (int c = 1; c <= N; c++)
				if (base_map[r][c].isVisited == false)
				{
					vec_open_positions.clear();
					open_sum = 0;
					open_cnt = 0;
					dfs(base_map, r, c);

					if (vec_open_positions.size() > 1)
						for (auto i : vec_open_positions)
							base_map[i.pos_y][i.pos_x].population = (int)(open_sum / open_cnt);
				}

		for (int r = 1; r <= N; r++)
			for (int c = 1; c <= N; c++)
			{
				for (int i = 1; i <= 4; i++) base_map[r][c].isOpen[i] = false;
				base_map[r][c].isVisited = false;
			}
	
		cnt++;
	}

	cout << cnt;

	return 0;
}
