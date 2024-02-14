/*
[24년 이전에 푼 거]
*/

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int N, K;
int visited[100001];

int computation(int input, int mode)
{
	//mode -> [0: -1]  [1: +1]  [2:  *2]
	if (mode == 0) return input - 1;
	else if (mode == 1) return input + 1;
	else if (mode == 2) return 2 * input;
}

void bfs()
{
	queue<int> q;
	q.push(N);
	visited[N] = 0;

	while (!q.empty())
	{
		int v = q.front();
		q.pop();

		if (v == K) break;

		for (int i = 0; i < 3; i++)
		{
			int result;
			result = computation(v, i);
			if (result < 0 || result > 100000) continue;
			if (visited[result] > 0 || result == N) continue;
			visited[result] = visited[v] + 1;
			q.push(result);
		}
	}
}

int main()
{
	//ifstream txt_input("input.txt");
	cin >> N >> K;

	bfs();

	cout << visited[K];

	return 0;
}
