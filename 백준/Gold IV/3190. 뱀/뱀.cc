#include <iostream>
#include <vector>
#include <vector>
#include <fstream>

using namespace std;

int N, K, L;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

struct Action
{
	int iTime;
	string Action;
};

struct Snake
{
	int y;
	int x;
	int dir;
};

vector<vector<string>> Grid;
vector<Action> vAction;
vector<Snake> snake;

bool isFreeSpace(const int& y, const int& x)
{
	for (auto position : snake)
	{
		if (position.y == y && position.x == x)
		{
			return false;
		}
	}

	return true;
}

bool moveSnake(string Action = "")
{
	int iLastIdx = snake.size() - 1;
	int iTargetR = snake[iLastIdx].y + dy[snake[iLastIdx].dir % 4];
	int iTargetC = snake[iLastIdx].x + dx[snake[iLastIdx].dir % 4];

	if (iTargetR < 0 || iTargetR >= N || iTargetC < 0 || iTargetC >= N) return false;
	if (!isFreeSpace(iTargetR, iTargetC)) return false;

	int dir = snake[iLastIdx].dir;
	if (Action == "L") dir--;
	else if (Action == "D") dir++;
	snake.push_back({ iTargetR, iTargetC, dir });

	if (Grid[iTargetR][iTargetC] == "A")
	{
		Grid[iTargetR][iTargetC] = "";
	}
	else if (Grid[iTargetR][iTargetC] != "A")
	{
		snake.erase(snake.begin());
	}

    return true;
}

void printGrid(const int& iTime)
{
	vector<vector<string>> TempGrid = Grid;

	cout << "    " << iTime << "    " << endl;

	for (int idx = 0; idx < snake.size(); idx++)
	{
		if (idx == snake.size() - 1)
		{
			if (snake[idx].dir % 4 == 0) TempGrid[snake[idx].y][snake[idx].x] = "^";
			if (snake[idx].dir % 4 == 1) TempGrid[snake[idx].y][snake[idx].x] = ">";
			if (snake[idx].dir % 4 == 2) TempGrid[snake[idx].y][snake[idx].x] = "D";
			if (snake[idx].dir % 4 == 3) TempGrid[snake[idx].y][snake[idx].x] = "<";
		}
		else
		{
			TempGrid[snake[idx].y][snake[idx].x] = "X";
		}
	}

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (TempGrid[r][c] == "") cout << ". ";
			else cout << TempGrid[r][c] << " ";
		}

		cout << endl;
	}

	cout << "=====================" << endl;
}

int main()
{
	//fstream txt_input("input.txt");
	cin >> N;
	Grid = vector<vector<string>>(N, vector<string>(N));
	snake.push_back({ 0, 0, 40001 });

	cin >> K;
	for (int iAppleIdx = 0; iAppleIdx < K; iAppleIdx++)
	{
		int y, x;
		cin >> y >> x;
		Grid[y - 1][x - 1] = "A";
	}

	cin >> L;
	vAction = vector<Action>(L);
	for (int iActionIdx = 0; iActionIdx < L; iActionIdx++)
	{
		int iTime;
		string Action;
		cin >> iTime >> Action;
		vAction[iActionIdx] = { iTime, Action };
	}

	//printGrid(0);
	int iTime = 1;
	int idx = 0;
	while (true)
	{
		if (vAction[idx].iTime == iTime)
		{
			if (!moveSnake(vAction[idx].Action))
			{
				break;
			}
			if (idx < vAction.size() - 1) idx++;
		}
		else
		{
			if (!moveSnake())
			{
				break;
			}
		}

		//printGrid(iTime);
		iTime++;
	}
	
	cout << iTime;

	return 0;
}
