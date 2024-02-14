/*
[24년 이전에 푼 거]
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

struct FireBall
{
	int r;
	int c;
	int mass;
	int speed;
	int dir;
};

int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

queue<FireBall> GridMap[50][50];
stack<FireBall> Container;

int main()
{
	// Receive Data
	int N, M, K;
	cin >> N >> M >> K;

	int r, c, m, s, d;
	for (int i = 0; i < M; i++)
	{
		cin >> r >> c >> m >> s >> d;
		FireBall input = { r, c, m, s, d };
		GridMap[r - 1][c - 1].push(input);
	}
	
	/*
	ifstream txt_input("input.txt");
	int N, M, K;
	txt_input >> N >> M >> K;

	int r, c, m, s, d;
	for (int i = 0; i < M; i++)
	{
		txt_input >> r >> c >> m >> s >> d;
		FireBall input = { r, c, m, s, d };
		GridMap[r - 1][c - 1].push(input);
	}
	*/

	for (int iteration = 0; iteration < K; iteration++)
	{
		// Move FireBalls
		for (int r = 0; r < 50; r++)
		{
			for (int c = 0; c < 50; c++)
			{
				while (!GridMap[r][c].empty())
				{
					FireBall cur_FireBall = GridMap[r][c].front();
					GridMap[r][c].pop();

					int new_r = (N * 1000 + r + dy[cur_FireBall.dir] * cur_FireBall.speed) % N;
					int new_c = (N * 1000 + c + dx[cur_FireBall.dir] * cur_FireBall.speed) % N;
					cur_FireBall.r = new_r;
					cur_FireBall.c = new_c;
					Container.push(cur_FireBall);
				}
			}
		}

		while (!Container.empty())
		{
			FireBall cur_FireBall = Container.top();
			Container.pop();
			GridMap[cur_FireBall.r][cur_FireBall.c].push(cur_FireBall);
		}

		// Split FireBalls
		for (int r = 0; r < 50; r++)
		{
			for (int c = 0; c < 50; c++)
			{
				if (GridMap[r][c].size() > 1)
				{
					int sum_mass = 0;
					int sum_speed = 0;
					int cnt_even = 0;
					int cnt_odd = 0;
					int size = GridMap[r][c].size();

					while (!GridMap[r][c].empty())
					{
						FireBall cur_FireBall = GridMap[r][c].front();
						GridMap[r][c].pop();

						sum_mass += cur_FireBall.mass;
						sum_speed += cur_FireBall.speed;
						if (cur_FireBall.dir % 2 == 0) cnt_even++;
						else cnt_odd++;
					}

					int newMass = sum_mass / 5;
					int newSpeed = sum_speed / size;

					if (newMass == 0) continue;

					if (cnt_even == size || cnt_odd == size)
					{
						for (int i = 0; i <= 6; i += 2)
						{
							FireBall input = { r, c, newMass, newSpeed, i };
							GridMap[r][c].push(input);
						}
					}
					else
					{
						for (int i = 1; i <= 7; i += 2)
						{
							FireBall input = { r, c, newMass, newSpeed, i };
							GridMap[r][c].push(input);
						}
					}
				}
			}
		}
	}

	int tot_mass = 0;
	for (int r = 0; r < 50; r++)
	{
		for (int c = 0; c < 50; c++)
		{
			while (!GridMap[r][c].empty())
			{
				tot_mass += GridMap[r][c].front().mass;
				GridMap[r][c].pop();
			}
		}
	}

	cout << tot_mass;

	return 0;
}
