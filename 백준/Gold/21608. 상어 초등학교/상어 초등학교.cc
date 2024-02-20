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