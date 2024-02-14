/*
[24년 이전에 푼 거]
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, K;
int sum_zero_durability = 0;

// Declare a struct that contains both robot and durability information
struct Container
{
	bool isRobot;
	int Durability;
};

void rotateConveyorLineOnce(vector<Container>&);
void moveRobotForward(vector<Container>&);
void placeRobotOnFirstContainer(vector<Container>&);

int main()
{
	// For debugging purposes
	/*
	// Read text file
	ifstream txt_input("input.txt");
	// Acquire the size of the C/V belt N and the max durability K
	txt_input >> N >> K;
	const int SIZE = 2 * N;
	vector<Container> conveyor_line(SIZE);
	int temp;
	for (int i = 0; i < 2 * N; i++)
	{
		txt_input >> temp;
		conveyor_line[i] = { false, temp };
	}
	*/

	// Acquire N, K and Durability information
	cin >> N >> K;

	const int SIZE = 2 * N;
	vector<Container> conveyor_line(SIZE);

	int temp;
	for (int i = 0; i < 2 * N; i++)
	{
		cin >> temp;
		conveyor_line[i] = { false, temp };
	}

	// Initialize cnt as 1 since the system starts with level 1
	int cnt = 1;

	while (true)
	{
		// Follow the instruction of having the C/V line rotated once, 
		// the robot moved by one container if possible 
		// and the new robot placed at container 1
		rotateConveyorLineOnce(conveyor_line);
		moveRobotForward(conveyor_line);
		placeRobotOnFirstContainer(conveyor_line);

		// Break and print cnt if sum_zero_durability exceeds K
		if (sum_zero_durability >= K)
		{
			cout << cnt;
			break;
		}

		// Increment cnt for every loop
		cnt++;
	}

	return 0;
}

// Rotate the C/V line once
void rotateConveyorLineOnce(vector<Container>& conveyor_line)
{
	// Reset the line from the very right with the very previous container
	// Pre-save the very last container and set it as the first one at the end
	Container temp = conveyor_line[2 * N - 1];
	for (int i = 2 * N - 1; i > 0; i--)
	{
		conveyor_line[i] = conveyor_line[i - 1];
	}
	conveyor_line[0] = temp;
	// Set the 'take_off' container as false
	conveyor_line[N - 1].isRobot = false;
}

// Move all robots by 1 container if possible
void moveRobotForward(vector<Container>& conveyor_line)
{
	for (int i = N - 1; i > 0; i--)
	{
		// If the one container after the robot position is empty and its durability is larger than 1, move the robot by one container
		if (conveyor_line[i].isRobot == false && conveyor_line[i - 1].isRobot == true && conveyor_line[i].Durability > 0)
		{
			conveyor_line[i].isRobot = true;
			conveyor_line[i - 1].isRobot = false;
			// Reduce the durability by one and increment sum_zero_durability if durability reaches 0
			conveyor_line[i].Durability--;
			if (conveyor_line[i].Durability == 0) sum_zero_durability++;
		}
	}
	// Set the 'take_off' container as false
	conveyor_line[N - 1].isRobot = false;
}

// Place a new robot on the very first container if the durability is larger than 1
void placeRobotOnFirstContainer(vector<Container>& conveyor_line)
{
	if (conveyor_line[0].Durability > 0)
	{
		conveyor_line[0].isRobot = true;
		// Reduce the durability by one and increment sum_zero_durability if durability reaches 0
		conveyor_line[0].Durability--;
		if (conveyor_line[0].Durability == 0) sum_zero_durability++;
	}
}
