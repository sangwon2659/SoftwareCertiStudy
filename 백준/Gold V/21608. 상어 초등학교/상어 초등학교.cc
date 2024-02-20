#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int student[401][4];
int map[21][21]; // 전체 맵 크기
int N; // 입력받은 N 
int dx[] = {0,0,-1,1};
int dy[] = {-1,1,0,0};

// 정보를 모아둔 구조체
struct Info{
    int x;
    int y;
    int empty;
    int match;
};

// 정렬 규칙 만들어둔 함수
bool compare(Info a, Info b){
	// 매칭 수가 같다면
    if(a.match == b.match){
    	// 빈칸 수가 같다면
        if(a.empty == b.empty) {
        	// 행이 같다면
            if(a.x == b.x) return a.y < b.y;
            return a.x < b.x;
        }
        return a.empty > b.empty;
    }
    return a.match > b.match;
}

// key : 자리에 앉는 학생 번호, x: 행, y: 열
Info bfs(int key, int x, int y){
    Info tmp = {x,y,0,0};
    for(int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 1 || ny < 1 || nx > N || ny > N) continue;
        // 해당 자리가 비어있으면 빈칸+1
        if(map[nx][ny] == 0) {
            tmp.empty++;
            continue;
        }
        // 해당 자리에 좋아하는 학생이 앉아있다면 매칭+1
        for(int j = 0; j < 4; j++){
            if(student[key][j] == map[nx][ny]) tmp.match++;
        }
    }
    return tmp; // 갱신된 Info 반환
}

// 해당 학생 자리 선정 프로세스 시작(key : 학생 번호)
void matching(int key){
    vector<Info> list; // 해당 칸의 Info 정보를 담음
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(map[i][j] == 0) list.push_back(bfs(key,i,j));
        }
    }
    sort(list.begin(),list.end(),compare); // 정렬 규칙에 따라 정렬
    map[list[0].x][list[0].y] = key; // 최우선순위 자리에 앉힘
}

// 점수 계산
int getScore(){
    int sum = 0;
    // k : 학생 번호
    for(int k = 1; k <= N*N; k++){
        for(int i = 1; i <= N; i++){
            bool endFlag = false;
            for(int j = 1; j <= N; j++){
                if(map[i][j] == k){
                    Info tmp = bfs(k,i,j);
                    sum += pow(10,tmp.match-1);
                    endFlag = true;
                    break;
                }
            }
            if(endFlag) break;
        }
    }
    return sum;
}

int main(){
    scanf("%d",&N);
    vector<int> order; // 자리에 앉는 순서
    for(int i = 1; i<= N*N; i++){
        int key;
        scanf("%d",&key);
        order.push_back(key);
        for(int j = 0; j < 4; j++){
            int num;
            scanf("%d",&num);
            student[key][j] = num;
        }
    }
    // 순서대로 자리에 앉히기 시작
    for(int i = 0; i < order.size(); i++){
        matching(order[i]);
    }
    cout << getScore() << "\n";
}

/*
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Pos
{
	int y;
	int x;
	int numEmpty = 0;
};

int N;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int grid[20][20] = { 0 };
int table[400][5];

int CountLike(const int& num, const int& r, const int& c)
{
	int numLike = 0;

	for (int dir = 0; dir < 4; dir++)
	{
		int targetR = r + dy[dir];
		int targetC = c + dx[dir];

		if (targetR < 0 || targetR >= N || targetC < 0 || targetC >= N || grid[targetR][targetC] == 0) continue;

		for (int idx = 1; idx < 5; idx++)
		{
			if (grid[targetR][targetC] == table[num][idx])
			{
				numLike++;
				break;
			}
		}
	}

	return numLike;
}

int CountEmpty(const int& r, const int& c)
{
	int numEmpty = 0;

	for (int dir = 0; dir < 4; dir++)
	{
		int targetR = r + dy[dir];
		int targetC = c + dx[dir];

		if (targetR < 0 || targetR >= N || targetC < 0 || targetC >= N || grid[targetR][targetC] > 0) continue;

		numEmpty++;
	}

	return numEmpty;
}

int MapTable(const int& input)
{
	for (int i = 0; i < (N * N); i++)
	{
		if (table[i][0] == input)
		{
			return i;
		}
	}
}

int FindSatisfaction()
{
	int totalSatisfaction = 0;

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			int student = MapTable(grid[r][c]);
			int numLike = CountLike(student, r, c);

			if (numLike == 1) totalSatisfaction += 1;
			else if (numLike == 2) totalSatisfaction += 10;
			else if (numLike == 3) totalSatisfaction += 100;
			else if (numLike == 4) totalSatisfaction += 1000;
		}
	}

	return totalSatisfaction;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	ifstream txt_input("input.txt");
	txt_input >> N;

	for (int i = 0; i < (N * N); i++)
	{
		for (int j = 0; j < 5; j++)
		{
			txt_input >> table[i][j];
		}
	}

	for (int studentIdx = 0; studentIdx < (N * N); studentIdx++)
	{
		int studentNum = table[studentIdx][0];
		vector<Pos> candidate;

		int numLike = 0;
		for (int r = 0; r < N; r++)
		{
			for (int c = 0; c < N; c++)
			{
				if (grid[r][c] > 0) continue;

				int currNumLike = CountLike(studentIdx, r, c);
				if (currNumLike == numLike)
				{
					candidate.push_back({ r, c });
				}
				else if (currNumLike > numLike)
				{
					candidate.clear();
					candidate.push_back({ r, c });
					numLike = currNumLike;
				}
			}
		}

		if (candidate.size() > 1)
		{
			sort(candidate.begin(), candidate.end(), [](const Pos& P1, const Pos& P2)
				{
					return P1.x < P2.x;
				});
			sort(candidate.begin(), candidate.end(), [](const Pos& P1, const Pos& P2)
				{
					return P1.y < P2.y;
				});

			for (int idx = 0; idx < candidate.size(); idx++)
			{
				candidate[idx].numEmpty = CountEmpty(candidate[idx].y, candidate[idx].x);
			}

			sort(candidate.begin(), candidate.end(), [](const Pos& P1, const Pos& P2)
				{
					return P1.numEmpty > P2.numEmpty;
				});
		}

		grid[candidate[0].y][candidate[0].x] = studentNum;
	}

	cout << FindSatisfaction();

	return 0;
}
*/
