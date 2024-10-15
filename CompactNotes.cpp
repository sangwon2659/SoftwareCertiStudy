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

// 경우의 수
/*
1 1 1 1 
1 1 1 0 
1 1 0 1 
1 1 0 0 
1 0 1 1 
1 0 1 0 
1 0 0 1 
1 0 0 0 
0 1 1 1 
0 1 1 0 
0 1 0 1 
0 1 0 0 
0 0 1 1 
0 0 1 0 
0 0 0 1 
0 0 0 0
*/
void Combination(const int& iNowPos)
{
    if (iNowPos == Container.size())
    {
        for (int idx = 0; idx < Container.size(); idx++)
        {
            cout << Container[idx] << " ";
        }

        cout << endl;

        return;
    }

    Container[iNowPos] = true;
    Combination(iNowPos + 1);

    Container[iNowPos] = false;
    Combination(iNowPos + 1);
}

// 팀 만들기 Combination
/*
1 2 3 
1 2 4 
1 2 5 
1 3 4 
1 3 5 
1 4 5 
2 3 4 
2 3 5 
2 4 5 
3 4 5 
*/
vector<int> Container(8);
void Combination(const int& n, const int& r, const int& iNowPos, const int& iNowVal)
{
    if (iNowPos == r)
    {
        for (int idx = 0; idx < r; idx++)
        {
            cout << Container[idx] << " ";
        }
        cout << endl;
    }

    for (int idx = iNowVal; idx <= n; idx++)
    {
        Container[iNowPos] = idx;
        Combination(n, r, iNowPos + 1, idx + 1);
    }
}

// 팀 만들기 Permutation
/*
1 2 3 
1 2 4 
1 2 5 
1 3 2 
1 3 4 
1 3 5 
1 4 2 
1 4 3 
1 4 5 
1 5 2 
1 5 3 
1 5 4 
2 1 3 
2 1 4 
2 1 5 
2 3 1 
2 3 4 
2 3 5 
2 4 1 
2 4 3 
2 4 5 
2 5 1 
2 5 3 
2 5 4 
3 1 2 
3 1 4 
3 1 5 
3 2 1 
3 2 4 
3 2 5 
3 4 1 
3 4 2 
3 4 5 
3 5 1 
3 5 2 
3 5 4 
4 1 2 
4 1 3 
4 1 5 
4 2 1 
4 2 3 
4 2 5 
4 3 1 
4 3 2 
4 3 5 
4 5 1 
4 5 2 
4 5 3 
5 1 2 
5 1 3 
5 1 4 
5 2 1 
5 2 3 
5 2 4 
5 3 1 
5 3 2 
5 3 4 
5 4 1 
5 4 2 
5 4 3 
*/
vector<int> Container(8);
vector<bool> isUsed(8);
void Permutation(const int& n, const int& r, const int& iNowPos)
{
    if (iNowPos == r)
    {
        for (int idx = 0; idx < r; idx++)
        {
            cout << Container[idx] << " ";
        }
        cout << endl;
    }

    for (int idx = 1; idx <= n; idx++)
    {
        if (isUsed[idx]) continue;
        Container[iNowPos] = idx;
        isUsed[idx] = true;
        Permutation(n, r, iNowPos + 1);
        isUsed[idx] = false;
    }
}

void printCombinationMap(const int& iMaxActive, const int& iNowActive, const int& iNowR, int iNowC)
{
    if (iNowActive == iMaxActive)
    {
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                cout << Map_[r][c] << " ";
            }

            cout << endl;
        }

        cout << "======" << endl;
        return;
    }

    for (int r = iNowR; r < 3; r++)
    {
        //if (r != iNowR) iNowC = 0;
        for (int c = iNowC; c < 3; c++)
        {
            if (Map_[r][c]) continue;
            Map_[r][c] = 1;
            printCombinationMap(iMaxActive, iNowActive + 1, r, c);
            Map_[r][c] = 0;
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

    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (Grid[r][c] == 1) continue;
            Grid[r][c] = 1;
            permutationMap(iMaxNum, iNowNum + 1);
            Grid[r][c] = 0;
        }
    }
}

// On/Off가 아닌 팀 기반 Permutation Map
/*
1 2 0 
0 0 0 
0 0 0 
============
1 0 2 
0 0 0 
0 0 0 
============
1 0 0 
2 0 0 
0 0 0 
============
1 0 0 
0 2 0 
0 0 0 
============
1 0 0 
0 0 2 
0 0 0 
============
1 0 0 
0 0 0 
2 0 0 
============
1 0 0 
0 0 0 
0 2 0 
============
1 0 0 
0 0 0 
0 0 2 
============
2 1 0 
0 0 0 
0 0 0 
============
2 0 1 
0 0 0 
0 0 0 
============
2 0 0 
1 0 0 
0 0 0 
============
2 0 0 
0 1 0 
0 0 0 
============
2 0 0 
0 0 1 
0 0 0 
============
2 0 0 
0 0 0 
1 0 0 
============
2 0 0 
0 0 0 
0 1 0 
============
2 0 0 
0 0 0 
0 0 1 
============
0 1 2 
0 0 0 
0 0 0 
============
0 1 0 
2 0 0 
0 0 0 
============
0 1 0 
0 2 0 
0 0 0 
============
0 1 0 
0 0 2 
0 0 0 
============
0 1 0 
0 0 0 
2 0 0 
============
0 1 0 
0 0 0 
0 2 0 
============
0 1 0 
0 0 0 
0 0 2 
============
0 2 1 
0 0 0 
0 0 0 
============
0 2 0 
1 0 0 
0 0 0 
============
0 2 0 
0 1 0 
0 0 0 
============
0 2 0 
0 0 1 
0 0 0 
============
0 2 0 
0 0 0 
1 0 0 
============
0 2 0 
0 0 0 
0 1 0 
============
0 2 0 
0 0 0 
0 0 1 
============
0 0 1 
2 0 0 
0 0 0 
============
0 0 1 
0 2 0 
0 0 0 
============
0 0 1 
0 0 2 
0 0 0 
============
0 0 1 
0 0 0 
2 0 0 
============
0 0 1 
0 0 0 
0 2 0 
============
0 0 1 
0 0 0 
0 0 2 
============
0 0 2 
1 0 0 
0 0 0 
============
0 0 2 
0 1 0 
0 0 0 
============
0 0 2 
0 0 1 
0 0 0 
============
0 0 2 
0 0 0 
1 0 0 
============
0 0 2 
0 0 0 
0 1 0 
============
0 0 2 
0 0 0 
0 0 1 
============
0 0 0 
1 2 0 
0 0 0 
============
0 0 0 
1 0 2 
0 0 0 
============
0 0 0 
1 0 0 
2 0 0 
============
0 0 0 
1 0 0 
0 2 0 
============
0 0 0 
1 0 0 
0 0 2 
============
0 0 0 
2 1 0 
0 0 0 
============
0 0 0 
2 0 1 
0 0 0 
============
0 0 0 
2 0 0 
1 0 0 
============
0 0 0 
2 0 0 
0 1 0 
============
0 0 0 
2 0 0 
0 0 1 
============
0 0 0 
0 1 2 
0 0 0 
============
0 0 0 
0 1 0 
2 0 0 
============
0 0 0 
0 1 0 
0 2 0 
============
0 0 0 
0 1 0 
0 0 2 
============
0 0 0 
0 2 1 
0 0 0 
============
0 0 0 
0 2 0 
1 0 0 
============
0 0 0 
0 2 0 
0 1 0 
============
0 0 0 
0 2 0 
0 0 1 
============
0 0 0 
0 0 1 
2 0 0 
============
0 0 0 
0 0 1 
0 2 0 
============
0 0 0 
0 0 1 
0 0 2 
============
0 0 0 
0 0 2 
1 0 0 
============
0 0 0 
0 0 2 
0 1 0 
============
0 0 0 
0 0 2 
0 0 1 
============
0 0 0 
0 0 0 
1 2 0 
============
0 0 0 
0 0 0 
1 0 2 
============
0 0 0 
0 0 0 
2 1 0 
============
0 0 0 
0 0 0 
2 0 1 
============
0 0 0 
0 0 0 
0 1 2 
============
0 0 0 
0 0 0 
0 2 1 
============
*/
vector<vector<int>> GridContainer(3, vector<int>(3));
vector<bool> bIsUsed(4);
void CombinationMap(const int& n, const int& r_, const int& iNowR, int iNowC, const int& iNowVal, const int& iNowCount)
{
    if (iNowCount == r_)
    {
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                cout << GridContainer[r][c] << " ";
            }
            cout << endl;
        }
        cout << "============" << endl;
    }

    for (int r = iNowR; r < 3; r++)
    {
        if (r != iNowR) iNowC = 0;
        for (int c = iNowC; c < 3; c++)
        {
            for (int idx = 1; idx <= n; idx++)
            {
                if (bIsUsed[idx]) continue;
                GridContainer[r][c] = idx;
                bIsUsed[idx] = true;
                CombinationMap(n, r_, r, c + 1, idx + 1, iNowCount + 1);
                GridContainer[r][c] = 0;
                bIsUsed[idx] = false;
            }
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
	visited[s] = true;
	
	while (!stk.empty())
	{
		int v = stk.top();
		stk.pop();

		visit_order.push_back(v);

		for (int a : adj_list[v])
		{
			if (!visited[a])
			{
				visited[a] = true;
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
        visited[s] = true;

	while (!q.empty())
	{
		int v = q.front();
		q.pop();

		visit_order.push_back(v);

		for (int a : adj_list[v])
		{
			if (!visited[a])
			{
				visited[a] = true;
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

시험 감독
[1시간]
int sum으로 선언을 해서 숫자를 막 넣으면 결과가 int의 한계를 넘어갈 수 있다
그래서 long long으로 선언을 해야된다

[4시간]
BFS방식으로 1//2//3//4 -> 11//12//13//14 21//22//23//24 31//32//33//34 41//42//43//44 이렇게 해보려고 헀는데 안되었음
DFS 방식으로 1111111111//1111111112//1111111113 이렇게 밖에 안됨
보드를 Tilt하는 알고리즘을 구현하는 데 어려움이 좀 있었음
완전 Naive하게 구슬을 한칸 한칸씩 움직이는 걸로 구현함...
이게 시간 초과가 안뜬 게 신기한 정도

새로운 게임 2
[1시간 40분]
어떻게 말을 매번 순서대로 자유롭게 이렇게 붙였다 저렇게 붙였다 할지 고민해보고 시작하는 게 매우 중요했음
Grid에는 Stack을 사용하고 잠깐 뺏다가 다시 넣는 Temp Container 용도로는 Deque를 사용하는 게 좋은 아이디어였음
Turn이 끝날 때마다 보는 게 아니라 말을 움직일 때마다 4개 이상인 경우가 있는지를 보는 게 핵심이었음 <- 이것 때문에 디버깅 오래 걸림...
디버깅할 때 Grid의 크기를 6으로 줄여놨다가 제출을 해서 Error가 남... 이런 부분 조심해야할 듯

모노미노도미노 2
[3시간]
완전 빡구현 문제....
숫자를 조심하는 게 최선
Rotation을 할 때 특정 좌표의 Grid가 어떻게 바뀔지가 아니라 특정 좌표를 넣었을 때
Rotation되어서 좌표가 돌아오도록 하는 게 포인트였음

상어 중학교
[2시간 40분]
struct에 bool operator<(const [struct_name] input)const 이걸 사용하는 게 핵심
열하고 행을 반대로 사용해서 디버깅 오래 걸림
A가 똑같을 경우 B를 보라고 할 때 sort를 사용하면 무조건 후자부터 sort하면 된다
Grid문제의 경우 Print를 해보는 게 편할 수도 있다

퇴사
[22분]
Container에 bool을 쭉 담아놓고 다 탐색을 하면서
idx += vWork[idx].iDurtaion; <- 이렇게 Duration을 고려해주도록 구현함
부등호 문제 때문에 Test Case를 몇 번 놓쳤지만 별 문제 없이 잘 풀림

스타트와 링크
[2시간]
이상하게 집중이 잘 안돼서 오래 걸렸다
Combination으로 풀면 금방 풀리는 문제였다

연산자 끼워넣기
[2시간]
iMaxResult, iMinResult를 10억1이 아닌 1억1로 해놔서 한참 고생함...
그리고 코드를 좀 간결하게 짜면 디버깅 하기 쉬울 듯...
참고:
int의 범위 -2,147,483,648 ~ 2,147,483,647

치킨 배달
[1시간]
전형적인 Combination 써서 경우의 수 보는 문제
Max값을 1000으로 너무 낮게 줘서 Error 뜸
Min을 찾을 때의 초기 Max 값은 최대한 크게 주자

톱니바퀴
[1시간]
머리로 상상하기가 너무 힘들어서 Visualization하는 코드를 작성했는데 이게 시간이 오래 걸렸다
처음에 Input을 받을 때 띄어쓰기가 없어서 어떻게 하는지 찾아보니까 string으로 받아서 - '0'을 하면 된다
q.push({ v.idx - 1, iMode });에서 v.idx에 -1을 안해줘서 오류가 있었다

로봇 청소기
[1시간]
방향을 유지한 채로 BackStep을 한다는 걸 제대로 안읽어서 디버깅 함
%를 써서 방향 전환 알고리즘을 비교적 간결하게 짬

뱀
[1시간 30분]
크게 어려운 건 없었다
Visualization을 하는 데 시간이 좀 걸리긴 헀는데 이런 문제는 시간이 걸리더라도 구현하는 게 맞는 것 같다
방향이 계속 바뀌는 경우 큰 수를 넣어놓고 % 4 이런 식으로 하는 게 완전 치트키는 맞는 듯

테트로미노
[1시간]
마땅히 아이디어가 없어서 완전 노가다성으로 풀었다
중간에 Pink Rotation 하나를 실수해서 3%에서 계속 틀렸었다
이런 건 무조건 출력하면서 보는 게 최고인 듯
중간 중간 break를 줘서 속도를 높였다

숨바꼭질 2
[4시간]
BFS의 개념에 대해 다시 생각해보게 됨...
그냥 외워서 쓰지 말고 진짜 이해를 하려고 노력해보자
// 여기에 if(bIsVisited[v.iNowLocation]) continue;를 안넣는 것 매우 중요
// 5 -> 10 -> 11(K)
// 9 -> 10 -> 11(K)
// 위의 2 경우다 iCount에 포함시켜야 하기 때문

마법사 상어와 파이어스톰
[45분]
TempGrid[r + rBase][c + cBase] = Grid[Size - c - 1 + rBase][r + cBase]만 생각하면 매우 쉬운 문제.
다만 IceChunk의 크기를 계산할 때 InitPos의 Ice가 0일 때는 Count를 하지 않도록,
그리고 TempGrid[r][c] > 0인 경우에만 TempGrid[r][c]--;를 하는 등의 Detail이 필요했음

마법사 상어와 토네이도
[2시간]
Mac OS에서 cpp 돌리는 거 환경 편하게 만드는 것 때문에 한참 고생함
문제는 무난하게 풀림

게리맨더링
[1시간 30분]
문제를 이해하는 게 조금 어려웠음
5 를 채우는 로직을 아주 아주 Naive하게 구현했음... 창피할 정도로
Population을 기준으로 선거구 인구 차이를 구해야 하는데 이 부분 처음에 실수함 (문제 제대로 안읽음)

연구소 3
[12시간]
집중을 안하고 풀어서 계속 뭐가 꼬였다
막판에 memcpy로 string을 복사하는 것 때문에 invalid pointer 에러가 계속 났는데
이것 때문에 엄청 고생했다...;;

나무 제테크
[45분]
주어진 문제 그대로 풀었더니 금방 풀림
For문을 워낙 많이 써야돼서 처음부터 연산 복잡도를 신경쓰면서 풀었더니 시간초과가 뜨진 않았음

사다리 조작
[6시간]
Grid에 사다리를 채울 때 이미 채워본 케이스는 건너뛰어야 하는데 중복되게 채워서 시간초과가 나왔음
iNowR하고 iNowC를 쓰면서, iNowR과 같은 행일 때를 제외하고는 iNowC를 0으로 초기화 하는 방식으로 채워야 함

감시
[49분]
모든 경우의 수를 다 보는 방식으로 방향을 설정하고
각 조합 별로 최소의 사각지대를 연산하는 문제였음.
큰 문제 없이 바로 풂

경사로
[1시간]
차분하게 잘 생각하면서 푸니까 큰 문제는 없었다.
다만 부호가 헷갈리는 경우가 많았어서 집중이 필요했다.
한번에 통과해서 기뻤다

이차원 배열과 연산
[4시간]
문제가 어려웠다...
중간에 0이 채워지는 걸 어떻게 처리할지 한참을 고민함
계속 틀렸다고 나와서
sort(v.begin(), v.end(), [](const Info& P1, const Info& P2)
{
    return P1.iNum < P2.iNum;
});
sort(v.begin(), v.end(), [](const Info& P1, const Info& P2)
{
    return P1.iFreq < P2.iFreq;
});
를 다음과 같이 고치니까 통과가 되었다
sort(v.begin(), v.end(), [](const Info& P1, const Info& P2)
{
    if (P1.iFreq == P2.iFreq) return P1.iNum < P2.iNum;
    else return P1.iFreq < P2.iFreq;
});
질문게시판 고수님에 의하면
sort는 원소에 항상 앞에 있음을 보장하지 않아서
이런 경우에는 stable_sort를 써야 함...(?)
실제로 이렇게 하니까 맞았음...
그냥 무조건 if문으로 sort는 한번에 하자
*/
