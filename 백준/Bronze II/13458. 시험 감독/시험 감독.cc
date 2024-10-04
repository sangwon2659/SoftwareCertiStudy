/*
[1시간]
int sum으로 선언을 해서 숫자를 막 넣으면 결과가 int의 한계를 넘어갈 수 있다.
그래서 long long으로 선언을 해야된다.
*/

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
