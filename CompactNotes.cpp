// Things to Remember

// Printing Map
for (int r = 0; r < map.size(); r++)
	for (int c = 0; c< map[0].size(); c++)
		cout << map[r][c] << " ";

// Lambda Function
auto square = [](int a){return a * a;};

// Sort Algorithm for Struct
sort(v.begin(), v.end(), [](const Person& P1, const Person& P2)
{
	return P1.age < P2.age;
};

// Using Template
template<typename T1, typename T2>
void printNumbers(const T1& t1, const T2& t2)
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
if (binary_search(v.begin(), v.end(), 5) == true) cout << "5 is in v";
if (set.find(5) != set.end()) cout << "5 is in the set";

// Divide String
#include <string>
str.substr(1) // <- str에 있는 두번째 element부터 마지막까지 반환

// Rotation
void RotateGrid(vector<vector<int>>& input)
{
    const int SIZE = key.size();
    vector<vector<int>> temp(SIZE, vector<int>(SIZE, 0));
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            //temp[i][j] = key[j][SIZE - i - 1]; // Anti Clock-Wise
            temp[i][j] = key[SIZE - j - 1][i]; //Clock-Wise
        }
    }
    input = temp;
    return;
}
     
// DFS & BFS
const int N = 6;
bool bVisited[N];
void dfs_recursion(const vector<vector<int>>& adj_list, const int& s)
{
	if (bVisited[s] == true) return;

	bVisited[s] = true;
	cout << s << " ";

	for (int i : adj_list[s])
		dfs_recursion(adj_list, i);
}
     
vector<int> dfs(const vector<vector<int>>& adj_list, int s)
{
	vector<bool> visited(adj_list.size(), false);
	vector<int> visit_order;
	stack<int> stk;
	stk.push(s);

	while (!stk.empty()) {
		int v = stk.top();
		stk.pop();

		if (visited[v])
			continue;

		visited[v] = true;
		visit_order.push_back(v);

		for (int a : adj_list[v]) {
			if (!visited[a])
				stk.push(a);
		}
	}

	return visit_order;
}

vector<int> bfs(const vector<vector<int>>& adj_list, int s)
{
	vector<bool> visited(adj_list.size(), false);
	vector<int> visit_order;
	queue<int> q;
	q.push(s);

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		if (visited[v])
			continue;

		visited[v] = true;
		visit_order.push_back(v);

		for (int a : adj_list[v]) {
			if (!visited[a])
				q.push(a);
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

