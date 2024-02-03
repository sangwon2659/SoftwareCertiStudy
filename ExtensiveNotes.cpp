#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

void printVector(vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

struct Person
{
    string name;
    int age;
};

template<typename T1, typename T2>
void printTwo(T1 a, T2 b)
{
    cout << "T1: " << a << endl;
    cout << "T2: " << b << endl;
}

#define MAX_QUEUE 10
template<typename T>
class CircularQueue
{
    private:
        T* arr;
        int front_idx;
        int rear_idx;
        int count;
        int capacity;
    public:
        CircularQueue(int sz = MAX_QUEUE)
        {
            arr = new T[sz];
            capacity = sz;
            count = 0;
            front_idx = 0;
            //-1로 초기화 해야 첫 enqueue() 때 rear_idx ++ 해도 index 0에 접근함
            rear_idx = -1;
        }
        ~CircularQueue()
        {
            delete arr;
        }
        void enqueue(const T& e)
        {
            if (full())
            {
                cout << "Overflow Error!" << endl;
                return;
            }

            //계속 돌아갈 수 있도록 % capacity 넣기
            rear_idx = (rear_idx + 1) % capacity;
            arr[rear_idx] = e;
            //원소 개수 tracking
            count ++;
        }
        void dequeue()
        {
            if(empty())
            {
                cout << "Underflow Error!" << endl;
                return;
            }

            //계속 돌아갈 수 있도록 % capacity 넣기
            front_idx = (front_idx + 1) % capacity;
            //원소 개수 tracking
            count--;
        }
        const T& front() const { return arr[front_idx]; }
        bool empty() const { return count == 0; }
        int full() const { return count == capacity; }
        int size() const { return count; }
};

string reverse(const string& str)
{
    if (str.length() == 0)
        return "";
    else
        return reverse(str.substr(1)) + str[0];
}

class MaxHeap
{
private:
	vector<int> vec;

public:
	MaxHeap() : vec(1) {}

	void push(int value)
	{
		vec.push_back(value);
		heapify_up(vec.size() - 1);
	}
	void pop()
	{
		vec[1] = vec.back();
		vec.pop_back();
		heapify_down(1);
	}
	int top() const { return vec[1]; }
	void clear() { vec.clear(); vec.push_back(0); }
	int size() { return vec.size() - 1; }
	bool empty() { return vec.size() == 1; }
	void print()
	{
		for (auto n : vec)
			cout << n << ", ";
		cout << endl;
	}

private:
	int parent(int i) { return i / 2; }
	int left(int i) { return 2 * i; }
	int right(int i) { return 2 * i + 1; }
	void heapify_up(int i)
	{
		if (i > 1 && vec[i] > vec[parent(i)]) {
			swap(vec[i], vec[parent(i)]);
			heapify_up(parent(i));
		}
	}
	void heapify_down(int i)
	{
		int largest = i;

		if (left(i) < vec.size() && vec[left(i)] > vec[largest]) {
			largest = left(i);
		}

		if (right(i) < vec.size() && vec[right(i)] > vec[largest]) {
			largest = right(i);
		}

		if (largest != i) {
			swap(vec[i], vec[largest]);
			heapify_down(largest);
		}
	}
};

struct Person_pq
{
    string name;
    int age;
    bool operator < (const Person_pq& Person_pq_) const {
        return age < Person_pq_.age;
    }
};

const int N = 6;
bool gVisited[N] = {};
void dfs_recursion(const vector<vector<int>>& adj_list, int s)
{
	if (gVisited[s])
		return;

	gVisited[s] = true;
	cout << s << ", ";

	for (int v : adj_list[s])
		dfs_recursion(adj_list, v);
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
			continue; // 이미 방문했으면 스킵!

		visited[v] = true; // 정점 v를 방문
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
			continue; // 이미 방문했으면 스킵!

		visited[v] = true; // 정점 v를 방문
		visit_order.push_back(v);

		for (int a : adj_list[v]) {
			if (!visited[a])
				q.push(a);
		}
	}

	return visit_order;
}

vector<int> memo(50, -1);

int fibo_memoization(int n)
{
	if (n < 2)
		return n;

	if (memo[n] != -1)
		return memo[n];
	
	memo[n] = fibo_memoization(n - 2) + fibo_memoization(n - 1);
	return memo[n];
}

int fibo_tabulation(int n)
{
	vector<int> dp(n + 1, 0);
	dp[1] = 1;

	for (int i = 2; i <= n; i++)
		dp[i] = dp[i - 2] + dp[i - 1];

	return dp[n];
}


int main()
{
    //////////////////Vector//////////////////
    cout << "//////////////////Vector//////////////////" << endl;
    vector<int> v(5);
    v.push_back(10);
    v.push_back(2);
    v.push_back(4);
    sort(v.begin(), v.end());
    printVector(v);
    //4th index 자리에 insert
    v.insert(v.begin() + 4, 100);
    printVector(v);
    //4th and 5th index 자리 element erase
    v.erase(v.begin() + 3, v.begin() + 5);
    printVector(v);
    //front(), back(), pop_back(), empty() 등이 더 있음

    //2-dimensional vector
    const int SIZE = 4;
    vector<vector<int>> map_(SIZE, vector<int>(SIZE));

    for (int r = 0; r < SIZE; r++)
    {
        for (int c = 0; c < SIZE; c++)
        {
            cout << map_[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    //////////////////Lambda//////////////////
    cout << "//////////////////Lambda//////////////////" << endl;
    auto square = [](int a) {return a * a;};
    cout << "square of 2 is: " << square(2) << endl;

    vector<Person> students;
    students.push_back({"Kim", 24});
    students.push_back({"John", 26});
    students.push_back({"Alex", 25});
    //오름차순
    sort(students.begin(), students.end(), 
        [](const Person& p1, const Person& p2)
        {
            return p1.age < p2.age;
        });
    for (int i = 0; i < students.size(); i++)
    {
        cout << "Student name: " << students[i].name << " // ";
        cout << "Student age: " << students[i].age << endl;
    }
    cout << endl;

    //////////////////Template//////////////////
    cout << "//////////////////Template//////////////////" << endl;
    int a = 3;
    float b = 2.145;
    printTwo(a, b);
    //클래스 템플릿 만드는 방법은 CircularQueue 참고
    cout << endl;

    //////////////////Stack//////////////////
    cout << "//////////////////Stack//////////////////" << endl;
    stack<int> s;
    for (int i = 0; i < SIZE_; i++) s.push(i);
    cout << "Element on the top of the stack: " << s.top() << endl;
    cout << "Size of the stack: " << s.size() << endl;
    cout << "Elements in the stack: "
    ;
    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    cout << endl;

    //////////////////Queue//////////////////
    cout << "//////////////////Queue//////////////////" << endl;
    queue<int> q;
    for (int i = 0; i < SIZE_; i++) q.push(i);
    //queue는 top()이 아닌 front()
    //stack은 수직으로 있고 queue는 누워있는 거라고 생각하자
    cout << "Element on the front of the queue: " << q.front() << endl;
    cout << "Size of the queue: " << q.size() << endl;
    cout << "Elements in the queue: ";
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    cout << endl;

    //////////////////Circular Queue//////////////////
    cout << "//////////////////Circular Queue//////////////////" << endl;
    //default size of circular queue set to 10
    CircularQueue<int> cq(4);
    cq.enqueue(1);
    cq.enqueue(2);
    cq.enqueue(3);
    cq.enqueue(4);
    cq.dequeue();
    cout << cq.front() << endl;
    while (!cq.empty())
    {
        cout << cq.front() << " ";
        cq.dequeue();
    }
    cout << endl;
    //full(), size() 등도 있음
    cout << endl;

    /////////////////Deque//////////////////
    cout << "//////////////////Deque//////////////////" << endl;
    deque<int> dq;
    for (int i = 0; i < SIZE_; i++) dq.push_front(i);
    dq.push_back(20);
    cout << "Element on the front of the deque: " << dq.front() << endl;
    cout << "Element on the back of the deque: " << dq.back() << endl;
    dq.pop_front();
    cout << "Element on the front of the deque: " << dq.front() << endl;
    dq.pop_back();
    cout << "Element on the back of the deque: " << dq.back() << endl;
    cout << "Size of the deque: " << dq.size() << endl;
    cout << "Elements in the deque: ";
    while (!dq.empty())
    {
        cout << dq.front() << " ";
        dq.pop_front();
    }
    cout << endl;
    cout << endl;

    /////////////////Recursive//////////////////
    cout << "//////////////////Recursive//////////////////" << endl;
    cout << "Reversing the input string" << endl;
    cout << reverse("Hello") << endl;
    cout << endl;

    /////////////////Sorting & Search Algorithm//////////////////
    cout << "//////////////////Sorting & Search Algorithm//////////////////" << endl;
    //버블 정렬, 선택 정력, 삽입 정렬 (비효율)
    //버블: 정렬되지 않은 부분에서 인접한 두 원소의 크기를 비교하여 교환하는 작업 반복
    //선택: 정렬되지 않은 원소들 중에서 최소값 원소를 찾아 맨 왼쪽 원소과 교환
    //삽입: 정렬되지 않은 부분의 첫 번째 원소를 정렬된 부분의 알맞은 위치에 삽입하는 과정 반복 
    //병합 정렬, 퀵 정렬 (효율)
    //병합: 1.입력 배열을 두 개의 부분 배열로 분할  2.부분 배열은 재귀적으로 정렬 3.부분 배열 병합(이때 병합된 배열의 원소가 정렬순서에 부합되도록 순서 조정)
    //퀵: 1.특정 원소를 피벗으로 선택하고, 주어진 배열을 피벗보다 작은 부분과 큰 부분으로 분할 2.분할된 부분 배열에 대해 재귀적으로 퀵 정렬 분할 작업 반복
    //STL sort 사용법
    vector<int> v_;
    v = {5, 7, 10, 20, 15, 3, 6};
    for (int i : v) cout << i << " ";
    cout << endl;
    //내림차순
    sort(v.begin(), v.end(), greater<>());
    for (int j : v) cout << j << " ";
    cout << endl;
    v_ = {-6, -3, 0, 6, -2, 10, 12, -3};
    sort(v_.begin(), v_.end(), [](int a, int b) { return abs(a) < abs(b); });
    for (int k : v_) cout << k << " ";
    cout << endl;

    //탐색은 선형탐색 & 이진탐색
    vector<int> v__ = {10, 5, 20, 16, 40, 13, 76, 0, 31, 2};
    int target = 40;
    //이진탐색은 std::binary_search 존재 (bool type)
    //비교 함수 comp를 마지막 매개변수로 지정할 수도 있음
    //cout << binary_search(v__.begin(), v__.end(), target) << endl;
    cout << endl;

    //std::set
    //레드 블랙 트리 이용하여 구현됨
    //#include <set> 필요
    //set는 중복되는 데이터는 insert 불가 (중복되도 되는 상태로 하려면 std::multiset 사용해야 함)
    //std::set은 데이터를 자동으로 정렬해 주는데, 정렬되지 않은 상태로 저장하려면 std::unordered_set 사용해야 함
    //std::set는 comp 비교 함수 지원함
    cout << "Set" << endl;
    set<int> set1 = {1, 5, 10, -1, 6, 20};
    set1.insert(42);
    for (int i = 0; i < 10; i++) set1.insert(1);
    cout << "Elements in set: ";
    for (int j : set1) cout << j << " ";
    cout << endl;
    set<int, greater<>> set2 = {1, 5, 10, -1, 6, 20, 42};
    cout << "Elements in set when greater<> used: ";
    for (int k : set2) cout << k << " ";
    cout << endl;
    //set.find(원소)의 경우에는 해당 원소를 찾으면 그 원소의 위치에 대한 반복자를 반환하고 찾지 못 하면 set.end()에 해당하는 반복자 반환한다
    if (set1.find(5) != set1.end()) cout << "5 is in the set" << endl;
    cout << endl;

    cout << "Map" << endl;
    using psi = pair<string, int>;
    set<psi> managers {{"Amelia", 29}, {"Noah", 25}, {"Olivia", 31},
		{"Sophia", 40}};
	//pair 이렇게도 가능
    managers.insert(make_pair("George", 35));
    psi person1 = {"Noah", 25};
	if (managers.find(person1) != managers.end())
		cout << person1.first << " is a manager!" << endl;
	else
		cout << person1.first << " is not a manager!" << endl;
    managers.erase({"Sophia", 40});
	managers.erase({"Noah", 30});
    cout << "Managers in the set: ";
    for (const auto& m : managers)
		cout << m.first << "(" << m.second << ") ";
    cout << endl;
    //참고로 psi라는 데이터 타입은 첫번째 입력 데이터 타입에 대해 정렬을 자동으로 해주고
    //만약 동일한 게 있다면 두번째 데이터 타입을 기준으로 정렬함
    //begin(), size(), empty() 등도 있음

    //std::map
    //키만 저장하는 std::set와는 다르게 std::map은 키와 벨류 둘다 저장
    //레드 블랙 트리 이용하여 구현됨
    //#include <map> 필요
    //정렬은 키 값을 기준으로 정렬됨
    //std::multimap, std::unordered_map도 존재
    //comp 비교 함수 지원함
    //관련 멤버함수 std::set과 동일 BUT operator[] 추가적으로 존재
    //operator[]는 특정 키에 해당하는 원소의 값을 참조로 반환하는데
    //해당 키의 원소가 없으면 새로운 원소를 기본값으로 생성하여 참조를 반환함
    map<string, int> fruits;
	fruits.insert({"apple", 1000});
	fruits.insert({"banana", 1500});
	//이렇게 하면 0으로 초기화 해서 삽입
    fruits["orange"];
	cout << fruits["apple"] << endl;
    fruits["apple"] = 2000;
	fruits.erase("grape");
    cout << "Information in the map: " << endl;
	for (auto [name, price] : fruits)
		cout << name << " is " << price << " won." << endl;
    cout << endl;

    //////////////////Heap//////////////////
    cout << "//////////////////Heap//////////////////" << endl;
    //Heap은 완전 이진 트리의 한 형태로서 힙 속성을 만족하는 구조
    //(배열로 구현하는 게 편함)
    //1.최대 힙: 부모 노드의 키 값은 항상 자식 노드의 키 값보다 크거나 같다
    //2.최소 힙: 부모 노드의 키 값은 항상 자식 노드의 키 값보다 작거나 같다
    //힙은 1st index부터 원소 넣는다 (이래야 왼쪽 자식, 오른쪽 자식 그리고 부모 노드를 계산하기 쉬워짐)
    //노드 번호 m을 기준으로
    //왼쪽 자식의 번호: 2 * m
    //오른쪽 자식의 번호: 2 * m + 1
    //부모 노드의 번호: m // 2
    //삽입 -> 트리의 마지막 자리에 새로운 원소를 임시로 저장하고 부모 노드와 키 값을 비교하여 위로, 위로 이동
    //삭제는 최대 값을 삭제하는 것이기에 사실상 루트 노드를 삭제하는 것 
    //-> 트리 마지막 자리 노드를 임시로 루트 노드의 자리에 배치하고 자식 노드들과의 값 비교를 하여 아래로, 아래로 이동 
    //(내리는 건 더 큰 키 값을 가지는 자식 쪽으로)
    MaxHeap heap;
	heap.push(10);
	heap.push(5);
	heap.push(15);
	heap.push(7);
	heap.push(3);
	heap.push(9);
	heap.push(14);
	heap.push(8);
	heap.push(2);
	heap.push(4);
	heap.print();
	while (!heap.empty()) {
		cout << heap.top() << ", ";
		heap.pop();
	}
	cout << endl;
    //<algorithm>에 make_heap이라는 게 정의되어 있긴 함 (참고)
    cout << endl;

    //////////////////Priority Queue//////////////////
    cout << "//////////////////Priority Queue//////////////////" << endl;
    //#include <queue>를 넣어서 사용
    priority_queue<int> pq;
    pq.push(1);
    pq.push(54);
    pq.push(20);
    pq.push(-1);
    pq.push(-64);
    pq.push(100);
    cout << "Elements in the priority queue: ";
    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;

    //Struct을 사용하면 비교할 수 있는 comp 비교 함수를 지정해줘야함
    priority_queue<Person_pq> pq_;
    pq_.push({"Jack", 23});
    pq_.push({"Alex", 24});
    pq_.push({"John", 20});
    pq_.push({"James", 21});
    pq_.push({"Michael", 22});
    //comp 비교 함수에 따라 가장 값이 큰 애 출력
    cout << pq_.top().age << endl;
    cout << endl;

    //std::unordered_set
    //#include <unordered_set> 필요
    //unordered_set는 중복되는 데이터는 insert 불가 (중복되도 되는 상태로 하려면 std::unordered_multiset 사용해야 함)
	//car -> radio -> orange -> ear -> radio
    cout << "Unordered Set" << endl;
	unordered_set<string> words;
	words.insert("car");
	words.insert("radio");
	words.insert("orange");
	words.insert("ear");
	string word = "radio";
	if (words.find(word) != words.end())
		cout << word << " is used!" << endl;
	else
		cout << word << " is NOT used!" << endl;
	vector<int> numbers {1, 5, 3, 1, 5, 7, 4, 5, 6, 3, 2, 7, 3, 6, 2};
    //numbers라는 vector에 있는 원소들을 numbers.begin(), numbers.end()로 unordered_set<int> num_set__에 추가하면 반복되는 애들은 무시됨
	unordered_set<int> num_set__(numbers.begin(), numbers.end());
	cout << num_set__.size() << endl;
    cout << endl;

    //std::unordered_map
    //키만 저장하는 std::set와는 다르게 std::map은 키와 벨류 둘다 저장
    //#include <unordered_map> 필요
    //unordered_map는 중복되는 데이터는 insert 불가 (중복되도 되는 상태로 하려면 std::unordered_multimap 사용해야 함)
    cout << "Unordered Map" << endl;
    unordered_map<string, int> fruits_;
	fruits_.insert({"apple", 1000});
	fruits_.insert({"banana", 1500});
	fruits_["orange"] = 3000;
	fruits_["grape"] = 4000;
	fruits_["lemon"] = 5000;
	fruits_["apple"] = 2000;
	fruits_.erase("grape");
	for (auto [name, price] : fruits_)
		cout << name << " is " << price << " won." << endl;
    cout << endl;

    //////////////////Graph//////////////////
    cout << "//////////////////Graph//////////////////" << endl;
    //객체 간의 연결 관계를 표현할 수 있는 비선형 자료구조
    //G = (V, E) [V: 정점, Vertex, Node // E: 에지, 간선, Edge, Link]
    //그래프 관련 용어
    //가중치(Weight): Edge에 부여된 수치
    //차수(Degree): 정점에 연결된 다른 정점의 개수
    //경로(Path): 특정 정점에서 다른 정점으로 이동하는 방법을 인접 정점의 나열로 표현한 것
    //사이클(Cycle): 시작 정점과 마지막 정점이 같은 단순 경로 (트리는 사이클이 없는 그래프)

    //그래프 표현방법
    //1.인접행렬(Adjacency Matrix)
    //정점 개수가 N인 경우 NxN 행렬을 만들어서
    //adj[u][v]에 따라 간선이 있거나(무방향 그래프) 갈 수 있는지 없는지(방향 그래프) 1과 0을 통해 만들기
    vector<vector<int>> adj_matrix = {
        {0, 1, 0, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1}
    };
    //2.인접 리스트
    //각 정점에 인접한 정점들을 연결 리스트로 표현
    //노드에 따라 간선이 있거나(무방향 그래프) 갈 수 있는지 없는지(방향 그래프)를 기준으로 원소를 추가하는 방식으로 구성
    //실제로 연결 리스트를 쓰는 것보다는 그냥 vector를 사용하는 게 편해서 그렇게 구성함
	vector<vector<int>> adj_list = {
		{1, 3, 4},
		{0, 2, 4},
		{1, 5},
		{0, 4},
		{0, 1, 3},
		{2}
	};
    //3.에지 리스트
    //모든 에지를 배열로 표현
    vector<vector<int>> edge_list = {
        {0, 1}, {0, 3}, {0, 4},
        {1, 0}, {1, 2}, {1, 4},
        {2, 1},
        {3, 1}, {3, 4},
        {4, 1}, {4, 2}, {4, 3}
    };

    //그래프 순회
    //Depth First Search
    //현재 정점과 인접한 정점 중 하나를 선택하여 이동하는 과정을 반복하고,
    //더 이상 이동할 정점이 없을 경우 뒤쪽으로 백트래킹(backtracking)하여 다시 이동할 경로를 탐색
    //시작 정점으로부터 거리가 멀어지는(깊이가 깊어지는) 방식으로 탐색
    //보통 재귀 또는 스택을 이용하여 구현
	cout << "dfs_recursion: ";
	dfs_recursion(adj_list, 0);
	cout << endl;

	auto dfs_order = dfs(adj_list, 0);
	cout << "dfs_stack: ";
	for (auto n : dfs_order)
		cout << n << ", ";
	cout << endl;

    //Breadth First Search
    //현재 정점과 인접한 모든 정점을 방문한 후,
    //다시 이들 정점과 인접한 모든 정점을 찾아 방문하는 형식
    //시작 정점으로부터 가까운 정점을 먼저 방문하고, 멀리 있는 정점을 나중에 방문
    //보통 큐를 이용하여 구현
    auto bfs_order = bfs(adj_list, 0);
	cout << "bfs_queue: ";
	for (auto n : bfs_order)
		cout << n << ", ";
	cout << endl;
    cout << endl;

    //////////////////Dynamic Programming//////////////////
    cout << "//////////////////Dynamic Programming//////////////////" << endl;
    //복잡한 문제를 간단한 여러 개의 부분 문제(subproblem)로 나누고, 
    //부분 문제에 대한 해답을 활용하여 전체 문제를 해결하는 문제 해결 방식
    //분할 정복법(divide and conquer)에서는 분할된 부분 문제들이 서로 겹치지 않지만, 
    //동적 계획법에서는 중복되는 부분 문제가 발생한다는 점이 다름
    
    //동적계획법 필요 조건
    //1.중복되는 부분 문제(overlapping subproblems)
    //주어진 문제를 여러 개의 부분 문제로 분할할 경우, 
    //몇몇 부분 문제가 반복되어 나타나는 현상
    //부분 문제의 솔루션을 저장하여 같은 부분 문제를 중복해서 계산하지 않도록 설정
    //2.최적 부분 구조(optimal substructure)
    //부문 문제의 최적해(optimal solution)를 조합하여 전체 문제의 최적해를 구할 수 있는 경우를 지칭

    //동적 계획법 문제의 해결 방법
    //기저 조건(base case) 정의
    //상태 전환(state transition)을 나타내는 순환식 정의
    //순환식을 메모이제이션(memoization) 또는 타뷸레이션(tabulation) 방식으로 풀이

    //메모이제이션
    //재귀 호출이 많이 발생하므로, 함수 호출에 따른 오버헤드(overhead)가 있음
    //*오버헤드란 프로그램의 실행흐름 도중에 동떨어진 위치의 코드를 실행해야할 때, 추가적으로 시간,메모리,자원이 사용되는 현상
    //경우에 따라 모든 부분 문제를 풀지 않아도 문제에 대한 해답을 구할 수 있음
    //캐시로 사용하는 표의 일부만 필요에 따라 계산하여 채움

    //타뷸레이션
    //표(배열)에 저장된 값을 참조하는 방식이므로 빠르게 동작
    //상향식(bottom-up) 방식이기 때문에 모든 부분 문제에 대한 해답을 구해서 표에 저장
    //표의 맨 처음부터 끝까지 차례대로 계산하여 모두 채움

    int n = 5;
    cout << fibo_memoization(n) << endl;
    cout << fibo_tabulation(n) << endl;
    cout << endl;

    //////////////////Extra//////////////////
    cout << "//////////////////Extra//////////////////" << endl;
    //개념
    //Sequence Container (순차 컨테이너)
    //vector, array, deque, list, forward_list
    //Associative Container (연관 컨테이너)
    //set, multiset, map, multimap
    //Unordered Associative Container (순서없는 연관 컨테이너)
    //unordered_set, unordered_multiset, unordered_map, unordered_multimap
    //Container Adaptors (컨테이너 어댑터)
    //stack, queue, priority_queue

    //For inputs with spaces;
    //char input[100];
    //cin.getline(input, size(input));

    //Dividing string
    //str.substr(1) 이렇게 하면 str에 있는 element의 두번째 element ~ end 반환
    //#include <string> 필요

    //Swap elements
    //swap(a[1], a[2]) 이렇게 하면 둘을 swap

    //내림차순 정렬
    //sort(v.begin(), v.end(), greater<>());
    //#include <algorithm> 필요
    //sort(v_.begin(), v_.end(), [](int a, int b) { return abs(a) < abs(b); });
    //이런 식으로 원하는 비교 방법 지정도 가능
    //<로 하면 오름차순 >로 하면 내림차순

    return 0;
}

