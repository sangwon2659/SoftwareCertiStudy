/*
[24년 이전에 푼 거]
*/

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int N, K;
bool visited[100001];
int steps;
int cnt = 1;

struct Info
{
	int Pos;
	int Depth;
};

int computation(int input, int mode)
{
	switch(mode)
	{
		case 0:
			return input - 1;
		case 1:
			return input + 1;
		case 2:
			return input * 2;
	}
}

void bfs()
{
	queue<Info> q;
	q.push({ N, 0 });
	visited[N] = true;

	while (!q.empty())
	{
		Info v = q.front();
		q.pop();

		if (v.Pos == K)
		{
			steps = v.Depth;
			int Depth = v.Depth;
			if (!q.empty()) q.pop();
			while (!q.empty())
			{
				Info z = q.front();
				q.pop();

				if (z.Pos == K && z.Depth == Depth) cnt++;
			}
			return;
		}

		visited[v.Pos] = true;

		for (int i = 0; i < 3; i++)
		{
			int result;
			result = computation(v.Pos, i);
			if (result < 0 || result > 100000) continue;
			if (visited[result] && result != K) continue;
			q.push({ result, v.Depth + 1 });
		}
	}
}

int main()
{
	//ifstream txt_input("input.txt");
	cin >> N >> K;

	bfs();
	cout << steps << endl;
	cout << cnt << endl;

	return 0;
}
