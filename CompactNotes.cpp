// Things to Remember

// Grid 복사하는 법
#include <cstring>
int grid[8][8] = {0};
int tempGrid[8][8] = {0};
memcpy(tempGrid, grid, 8*8*sizeof(int));

// Struct with operator<
struct Student
{
    string name;
    int age;

    bool operator<(const Student& input) const
    {
        return age < input.age;
    }
};

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
});

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

string reverseString(const string& input)
{
    if (input == "") return "";

    return reverseString(input.substr(1)) + input[0];
}
	
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
                temp[r][c] = input[c][SIZE - r - 1];
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

void combinationMap(const int& iMaxNum, const int& iNowNum, const int& iNowR, const int& iNowC)
{
    if (iNowNum == iMaxNum)
    {
        printGrid();
        return;
    }

    for (int r = iNowR; r < 2; r++)
    {
        for (int c = iNowC; c < 2; c++)
        {
            if (Grid[r][c] == 1) continue;
            Grid[r][c] = 1;
            combinationMap(iMaxNum, iNowNum + 1, r, c);
            Grid[r][c] = 0;
        }
    }
}

void permutationMap(const int& iMaxNum, const int& iNowNum)
{
    if (iNowNum == iMaxNum)
    {
        printGrid();
        return;
    }

    for (int r = 0; r < 2; r++)
    {
        for (int c = 0; c < 2; c++)
        {
            if (Grid[r][c] == 1) continue;
            Grid[r][c] = 1;
            permutationMap(iMaxNum, iNowNum + 1);
            Grid[r][c] = 0;
        }
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

/*
낚시왕
[6시간]
MoveShark를 할 때 For문을 돌리면서 방향 바뀌는 걸 확인해야 하기 때문에 제 자리로 돌아오는 패턴을 파악해서 %를 때려주는 게 핵심
grid에는 idx만 놓고 크기 비교를 할 때는 sort + Lambda 함수를 사용할 수도 있다
dir를 40000 이런 식으로 선언해놓고 막상 사용할 때 %를 안쓰는 바람에 디버깅 한 3시간 걸림... 진짜 조심해야 되는 부분
한줄 짜리 if문은 대괄호 안쓰고 하는 게 좋지 않을까...? 코드 길이 너무 길어지면 가독성 떨어짐

마법사 상어와 블리자드
[3시간 15분]
개빡구현 문제
딱히 어려운 부분은 없었음
queue를 써서 채우고 지우고 하는 식으로 구현함
s랑 d를 거꾸로 받아서 디버깅 고생함... 계속 집중력이 딸려서 이런 실수를 하는 듯
문제를 더 천천히 잘 읽어야 한다
코드를 너무 길게 짜다보니 중간에 언제 Break를 걸어줘야 할지 헷갈리는 경우 많았음...

마법사 상어와 복제
[3시간 30분]
4 x 4 grid라서 for문 신경 안쓰고 막 돌림
tempGrid를 잘 사용해서 Fish를 옮기는 게 중요했음
Shark가 움직이는 경우의 수를 볼 때 bVisited의 경우 제외하는 Fish의 수를 합산하지 않는 게 가장 핵심이었고,
맨 처음에 Shark가 시작하는 지점을 bVisited = true로 잡지 않는 것 또한 핵심이었음
경우의 수가 겹치는 경우 그걸 Int로 바꿔서 가장 작은 숫자를 return하는 경우의 수를 선택하는 부분도 있었음

원판 돌리기
[5시간]
원판을 Grid형태로 이해하고, X방향으로는 % M을 써서 인접할 수 있도록 하는 것이 핵심이었음
DFS를 하면서 -1로 바꿔주는 로직 또한 핵심이었음
double avg = (double)sum / (double)cnt를 해줘야 avg가 double 형태로 나오면서 제대로 비교가 되는데
double avg = (int)sum / (int)cnt를 해서 한참 동안 엄청난 카오스였음...

청소년 상어
[3시간 30분]
DFS를 돌릴 때 매번 grid를 원래 상태로 돌려놓으면서 돌려야 하는 부분을 생각하지 않고 짜서 좀 고생했다
문제를 처음 보고 어떻게 설계를 할지 제대로 생각을 한 후 코드 작성을 시작하자
+ DFS를 돌릴 때 상어가 격자를 벗어나는 경우 때 continue가 아닌 break를 해서 모두의 경우의 수를 탐색하지 못 하는 버그가 있었다
(이걸 통해 초기 설계의 중요성을 더욱 느낌)

싸움땅
[2시간 40분]
빡구현 문제
PlayerDropGunAndMove함수에서
 targetR = nowR + dy[vectorPlayers[playerIdx].dir % 4];
 targetC = nowC + dx[vectorPlayers[playerIdx].dir % 4];
부분을 nowR & nowC가 아닌 vectorPlayers[playerIdx].y & vectorPlayers[playerIdx].x로 해서 틀림...
(targetR, targetC로 들어가서 다시 한번 더 targetR, targetC를 찾는 구조인데 그냥 nowR, nowC 이런 식으로 알아볼 수 없게 변수명을 정하니까 헷갈렸던 거)
시간이 좀 들더라도 변수 제대로 설정하는 게 디버깅 하는 데 훨씬 편할 듯

스타트 택시
[2시간 40분]
문제를 처음에 제대로 이해 못 해서, 같은 Depth에서의 모든 경우의 수 중에서 다시 행과 열을 비교해서 가장 우선순위를 정해야 되는 걸 모르고 구현함
이해한 후 새로 구현했을 때는 꼭 하나 더 깊이 들어가야만 Vector를 비교해서 ClosestCustomer를 Return 하게끔 잘 못 짜서 또 고생 함...
(분명히 Customer가 있는데 -10으로 Return 해버리는 문제가 자꾸 발생함)
이런 예외 Case를 어떻게 해야 잘 생각할 수 있을지 고민이 필요함

BFS를 돌릴 때
Depth를 Tracking하고 싶으면 Queue에 들어가는 자료형에 Int 하나 추가해서 돌리면서
Push를 할 때 +1 이런 식으로 하면 됨
한 Depth가 다 돌았을 때 뭘 하고 싶으면 maxNum을 정해놓고 이 Depth가 이 maxNum 보다 커지면 그때가 사이클의 마지막 루프임
(더 깊은 Depth가 없을 것을 대비해 While문 밖에도 마지막 Depth에 대한 실행문 추가해줘야 함)

드래곤 커브
[1시간 10분]
기준 점을 잡고 회전을 하는 것 + 매번 시작점을 선분의 끝점으로 잡는 게 핵심인 문제였음
[y] = [0 -1] * [y]
[x] = [1 0]    [x]
이렇게 회전을 시킴

아기 상어
[1시간 10분]
단순히 grid[r][c] < shark.size 조건만 만족하는 게 아니라
grid[r][c] > shark.size로 인해 아예 아무 데로도 갈 수 없는 경우를 고려하지 않아서
런타임 에러가 몇 번 났었다...
이건 TestCase에 이것 저것 넣어보면서 깨달은 건데
확실히 예외 케이스를 잘 생각하는 게 중요하다

주사위 윷놀이
[6시간]
엄청 오래 걸림...
Permutation 응용 능력이 떨어져서 구현하는 데 어려움 많았음
문제의 핵심:
1. 그래프를 Grid형태로 구현하는 것
2. 25, 30, 35, 40에서 겹치는 거 잘 처리하는 것
3. horseContainer는 horseContainer대로 수정했다가 복원하고
   말은 또 따로 죽였다가 다시 살리고 하는 것

주사위 굴리기 2
[1시간 30분]
문제를 자꾸 이해 못 해서 다르게 구현하는 바람에 좀 해맴...
- 주사위의 이동방향만 바꿔서 그대로 굴리면 되는 건데, 처음에 굳이 그 자리에서 실제로 회전을 하게끔 만들어서 좀 고생함
- DFS를 돌릴 때 지나온 길은 다시 가면 안되는데 그걸 고려하지 않고 구현했었음
- 없는 칸으로 주사위가 가려고 할 때 방향 바꿔주고 반대 방향으로 실제로 전개를 해야되는데 방향만 바꿔주고 끝냄...

메이즈 러너
[8시간]
빡구현 문제인데 어디가 틀렸는지 끝까지 몰라서 그냥 처음부터 다시 했더니 풀림...
어떻게 구현하는 게 좋을지 충분히 생각해보고 문제를 푸는 게 중요하다는 것을 다시 한 번 느낌

주사위 굴리기
[1시간 40분]
문제에 x랑 y를 바꿔서 써놔서 실수를 함...
+ if (targetR < 0 || targetR >= N || targetC < 0 || targetC >= M)를
둘 다 N으로 해놔서 한참 고생함...
집중해서 천천히 짜자

연구소
[2시간]
Combination & Permutation 공부하고 새로 풀었음
전형적인 유형이라 복습 필수
*/

