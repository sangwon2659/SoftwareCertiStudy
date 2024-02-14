#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <fstream>
#include <cstring>

using namespace std;

int N, M, V;
vector<int> Container[10001];
bool visited[10001];

void dfs(const int& s)
{
	if (visited[s]) return;
	visited[s] = true;
	cout << s << " ";

	for (auto i : Container[s])
	{
		if (!visited[i]) dfs(i);
	}
}

void bfs(const int& s)
{
	queue<int> q;
	q.push(s);

	while (!q.empty())
	{
		int v = q.front();
		q.pop();

		if (visited[v]) continue;
		visited[v] = true;
		cout << v << " ";

		for (auto i : Container[v])
		{
			if (!visited[i]) q.push(i);
		}
	}
}

int main()
{
	//ifstream txt_input("input.txt");
	cin >> N >> M >> V;

	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		Container[a].push_back(b);
		Container[b].push_back(a);
	}

	for (int i = 0; i < M; i++)
	{
		sort(Container[i + 1].begin(), Container[i + 1].end());
	}

	dfs(V);
	cout << endl;

	memset(visited, false, 10001);

	bfs(V);


	return 0;
}