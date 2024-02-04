// Things to Remember

// Grid 복사하는 법
#include <cstring>
int grid[8][8] = {0};
int tempGrid[8][8] = {0};
memcpy(tempGrid, grid, 8*8*sizeof(int));

// Printing Map
for (int r = 0; r < map.size(); r++)
{
	for (int c = 0; c< map[0].size(); c++)
	{
		cout << map[r][c] << " ";
	}
}

// Lambda Function
auto Square = [](int a)
{
	return a * a;
};

// Sort Algorithm for Struct
sort(v.begin(), v.end(), [](const Person& P1, const Person& P2)
{
	return P1.age < P2.age;
};

// Using Template
template<typename T1, typename T2>
void PrintNumbers(const T1& t1, const T2& t2)
{
	cout << t1 << " " << t2 << endl;
}

// Organizing Set (Single)
set<int, greater<>> set; <- Organizes set in 내림차순
//(OR set<string, greater<string>> set;)
//[Pair 등에 기반한 SET은 Indexing이 first/second로 된다] <- Struct 기반으로 했으면 설정한 이름으로

// Organizing Set (Pair)
struct Comp
{
	bool operator() (const pair<string, int>& P1, const pair<string, int>& P2) const
	{
		return P1.second < P2.second;
	}
};
set<pair<string,int>, Comp> s;

// Set & Map
set.erase({"Mike", 16});
map["Apple"]++;

// Search
if (binary_search(v.begin(), v.end(), 5) == true)
{
	cout << "5 is in v";
}
if (set.find(5) != set.end())
{
	cout << "5 is in the set";
}

// Divide String
#include <string>
str.substr(1) // <- str에 있는 두번째 element부터 마지막까지 반환

// Rotation
// mode = 0 Clock-wise
// mode = 1 Anti-Clock-wise
void RotateGrid(vector<vector<int>>& input, const int& mode)
{
    const int SIZE = input.size();
    vector<vector<int>> temp(SIZE, vector<int>(SIZE));

    for (int r = 0; r < SIZE; r++)
    {
        for (int c = 0; c < SIZE; c++)
        {
            if (mode == 0)
            {
                temp[r][c] = input[SIZE - c - 1][r];
            }
            else
            {
                temp[r][c] = input[r][SIZE - c - 1];
            }
        }
    }

    input = temp;
    return;
}

// Combination & Permutation
int arr[4] = {1, 2, 3, 4};
int n = 4;
int r = 3;
int order[3] = {0};
void PrintCombination(int nowPos, int nowVal)
{
	if (nowPos == r)
	{
		for (int idx = 0; idx < r; idx++)
		{
			cout << order[idx] << " ";
		}

		cout << endl;
		return;
	}

	for (int idx = nowVal; idx < n; idx++)
	{
		order[nowPos] = idx;
		PrintCombination(nowPos + 1, idx + 1);
	}
}

bool bInUse[4] = {0};
void PrintPermutation(int nowPos)
{
	if (nowPos == r)
	{
		for (int idx = 0; idx < r; idx++)
		{
			cout << order[idx] << " ";
		}

		cout << endl;
		return;
	}

	for (int idx = 0; idx < n; idx++)
	{
		if (bInUse[idx])
		{
			continue;
		}

		bInUse[idx] = true;
		order[nowPos] = idx;
		PrintPermutation(nowPos + 1);
		bInUse[idx] = false;
	}
}
     
// DFS & BFS
const int N = 6;
bool bVisited[N];
void DfsRecursion(const vector<vector<int>>& adj_list, const int& s)
{
	if (bVisited[s] == true)
	{
		return;
	}

	bVisited[s] = true;
	cout << s << " ";

	for (int i : adj_list[s])
	{
		dfs_recursion(adj_list, i);
	}
}
     
vector<int> Dfs(const vector<vector<int>>& adj_list, int s)
{
	vector<bool> visited(adj_list.size(), false);
	vector<int> visit_order;
	stack<int> stk;
	stk.push(s);

	while (!stk.empty())
	{
		int v = stk.top();
		stk.pop();

		if (visited[v])
		{
			continue;
		}

		visited[v] = true;
		visit_order.push_back(v);

		for (int a : adj_list[v])
		{
			if (!visited[a])
			{
				stk.push(a);
			}
		}
	}

	return visit_order;
}

vector<int> Bfs(const vector<vector<int>>& adj_list, int s)
{
	vector<bool> visited(adj_list.size(), false);
	vector<int> visit_order;
	queue<int> q;
	q.push(s);

	while (!q.empty())
	{
		int v = q.front();
		q.pop();

		if (visited[v])
		{
			continue;
		}

		visited[v] = true;
		visit_order.push_back(v);

		for (int a : adj_list[v])
		{
			if (!visited[a])
			{
				q.push(a);
			}
		}
	}
	
	return visit_order;
}

// Read .txt
#include <fstream>	
ifstream txt_input("input.txt");
txt_input >> ...

// Read from Platform
cin >> ...

