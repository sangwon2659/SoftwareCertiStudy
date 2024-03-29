/*
[24년 이전에 푼 거]
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

struct Map_Coor
{
	int shark_num;
	int odor_cnt;
	int occupancy;
};

struct Shark
{
	bool isAlive;
	int pos_y;
	int pos_x;
	int dir;
};

int MAP_SIZE, SHARK_NUM, K;
int num_shark_left, seconds = 0;

vector<int> dy = { -10, -1, 1, 0, 0 };
vector<int> dx = { -10, 0, 0, -1, 1 };

Map_Coor base_map[21][21];
Shark vec_shark[401];
int vec_shark_pref[401][5][5];

void acquireData_cin()
{
	cin >> MAP_SIZE >> SHARK_NUM >> K;
	num_shark_left = SHARK_NUM;

	int base_map_input;
	for (int r = 1; r <= MAP_SIZE; r++)
		for (int c = 1; c <= MAP_SIZE; c++)
		{
			cin >> base_map_input;
			if (base_map_input != 0)
			{
				vec_shark[base_map_input] = { 1, r, c, 0 };
				base_map[r][c] = { base_map_input, K, 1 };
			}
		}

	for (int i = 1; i <= SHARK_NUM; i++)
		cin >> vec_shark[i].dir;

	for (int i = 1; i <= SHARK_NUM; i++)
	{
		for (int r = 1; r <= 4; r++)
			for (int c = 1; c <= 4; c++)
				cin >> vec_shark_pref[i][r][c];
	}
}

void computeSharkMovement(const int& shark_idx, const int& target_pos_y, const int& target_pos_x, const int& direction, const bool& isEmptySpot)
{
	base_map[vec_shark[shark_idx].pos_y][vec_shark[shark_idx].pos_x].occupancy = 0;

	if (base_map[target_pos_y][target_pos_x].occupancy == 1)
	{
		vec_shark[shark_idx].isAlive = false;
		num_shark_left--;
		return;
	}

	vec_shark[shark_idx].pos_y = target_pos_y;
	vec_shark[shark_idx].pos_x = target_pos_x;
	vec_shark[shark_idx].dir = direction;
	base_map[target_pos_y][target_pos_x].occupancy = 1;

	if (isEmptySpot)
	{
		base_map[target_pos_y][target_pos_x].shark_num = shark_idx;
		base_map[target_pos_y][target_pos_x].odor_cnt = K + 1;
	}
	else
	{
		base_map[target_pos_y][target_pos_x].odor_cnt = -1;
	}
}

void searchAndMoveShark(const int& shark_idx)
{
	int isEmptySpot = true;

	while (true)
	{
		for (int search_direction = 1; search_direction <= 4; search_direction++)
		{
			int direction = vec_shark_pref[shark_idx][vec_shark[shark_idx].dir][search_direction];
			int target_pos_y = vec_shark[shark_idx].pos_y + dy[direction];
			int target_pos_x = vec_shark[shark_idx].pos_x + dx[direction];
			if (target_pos_x < 1 || target_pos_x > MAP_SIZE || target_pos_y < 1 || target_pos_y > MAP_SIZE) continue;

			if (isEmptySpot == true && base_map[target_pos_y][target_pos_x].odor_cnt == 0 || base_map[target_pos_y][target_pos_x].odor_cnt == K + 1)
			{
				computeSharkMovement(shark_idx, target_pos_y, target_pos_x, direction, isEmptySpot);
				return;
			}

			else if (isEmptySpot == false && base_map[target_pos_y][target_pos_x].shark_num == shark_idx)
			{
				computeSharkMovement(shark_idx, target_pos_y, target_pos_x, direction, isEmptySpot);
				return;
			}
		}

		isEmptySpot = false;
	}
}

void refreshMap()
{
	for (int r = 1; r <= MAP_SIZE; r++)
		for (int c = 1; c <= MAP_SIZE; c++)
		{
			if (base_map[r][c].odor_cnt > 0) base_map[r][c].odor_cnt--;
			if (base_map[r][c].odor_cnt == 0) base_map[r][c].shark_num = 0;
			if (base_map[r][c].odor_cnt == -1) base_map[r][c].odor_cnt = K;
		}
}

int main()
{
	acquireData_cin();

	while (num_shark_left != 1)
	{
		for (int shark_idx = 1; shark_idx <= SHARK_NUM; shark_idx++)
			if (vec_shark[shark_idx].isAlive == true) searchAndMoveShark(shark_idx);
		refreshMap();

		seconds++;
		if (seconds == 1001)
		{
			cout << -1;
			return 0;
		}
	}

	cout << seconds;
	return 0;
}
