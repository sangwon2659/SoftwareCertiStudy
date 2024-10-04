#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
int N, A, B, C;
vector<int> vClass;

long long iSum = 0;

int findMin(int Class)
{
	int iCount = 0;

	if (B >= Class)
	{
		iCount = 1;
	}
	else
	{
		Class -= B;
		iCount++;

		int Quotient = (int)(Class / C);
		Class -= Quotient * C;
		iCount += Quotient;

		if (Class > 0)
		{
			iCount++;
		}
	}

	return iCount;
}

int main()
{
	//fstream txt_input("input.txt");
	cin >> N;
	vClass = vector<int>(N);

	for (int iter = 0; iter < N; iter++)
	{
		cin >> vClass[iter];
	}

	cin >> B >> C;

	for (int iter = 0; iter < N; iter++)
	{
		iSum += findMin(vClass[iter]);
	}

	cout << iSum;


	return 0;
}
